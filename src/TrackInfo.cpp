#include "TrackInfo.h"
#include "TrackImageProvider.h"
#include "TrackModel.h"

#include <QTimer>
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QUrl>
#include <QFileInfo>
#include <QRandomGenerator>

TrackInfo::TrackInfo(const QString& path, TrackImageProvider* provider, QObject* parent) :
    QObject(parent), m_provider(provider), m_path(path) {
    TrackModel* model = dynamic_cast<TrackModel*>(parent);
    if (model) {
        m_index = model->rowCount();
        emit dataChanged();
    }
    m_tempPlayer = new QMediaPlayer(this);
    m_tempPlayer->setSource(QUrl::fromLocalFile(path));
    connect(m_tempPlayer, &QMediaPlayer::metaDataChanged, this, &TrackInfo::onMetaDataChanged);
}

void TrackInfo::onMetaDataChanged() {
    auto metaData = m_tempPlayer->metaData();
    m_metadataLoaded = true;

    qDebug() << "Metadata loaded for:" << m_path;
    qDebug() << "Has cover art:" << metaData.keys().contains(QMediaMetaData::CoverArtImage);
    qDebug() << "Has thumbnail image:" << metaData.keys().contains(QMediaMetaData::ThumbnailImage);
    
    QImage image;
    
    if (metaData.keys().contains(QMediaMetaData::CoverArtImage))
        image = metaData.value(QMediaMetaData::CoverArtImage).value<QImage>();  
    else if (metaData.keys().contains(QMediaMetaData::ThumbnailImage))
        image = metaData.value(QMediaMetaData::ThumbnailImage).value<QImage>();
    if (!image.isNull() && m_provider) {
        QString id = QString::number(QRandomGenerator::global()->generate());
        m_provider->m_images[id] = image;
        m_icon = QUrl::fromUserInput("image://tracks/" + id);
        emit dataChanged();
    }

    if (metaData.keys().contains(QMediaMetaData::Title)) {
            m_name = metaData.stringValue(QMediaMetaData::Title);
            emit dataChanged();
        }
        else {
            m_name = QFileInfo(m_path).baseName();
            emit dataChanged();
        }

    if (metaData.keys().contains(QMediaMetaData::ContributingArtist)) {
        m_artist = metaData.stringValue(QMediaMetaData::ContributingArtist); 
        emit dataChanged();
    }

}

QString TrackInfo::name() const {
    return m_name;
}

QString TrackInfo::artist() const {
    return m_artist;
}

QUrl TrackInfo::icon() const {
    return m_icon;
}

QString TrackInfo::path() const {
    return m_path;
}

int TrackInfo::index() const {
    return m_index;
}

bool TrackInfo::isMetadataLoaded() const {
    return m_metadataLoaded;
}
