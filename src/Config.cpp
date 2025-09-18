#include "Config.h"
#include "MediaPlayer.h"
#include "TrackInfo.h"

#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QDir>
#include <QFile>

#include <QByteArray>
#include <QString>

#include <QColor>

#include <QDebug>


Config::Config(const QString& path, MediaPlayer* mediaPlayer, QObject* parent) : 
    QObject(parent), m_mediaPlayer(mediaPlayer) {
    m_path = path;
    readFile(m_path);
}

void Config::readFile(const QString& path) {
    QFileInfo fi(path);
    if (!fi.exists()) {
        qWarning() << "Config file doesn't exist:" << path;
        return;
    }
    QFile configFile(path);
    if (!configFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Can't open config file:" << path
                   << ", error:" << configFile.errorString();
        return;
    }
    
    QByteArray data = configFile.readAll();
    configFile.close();
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "Config parse error:" << parseError.errorString()
                   << ", offset:" << parseError.offset;
        return;
    }

    m_json = doc.object();
}
void Config::reload() {
    m_musicDirs.clear();

    QJsonArray trackDirsArray = m_json["trackDirs"].toArray();
    for (int i = 0; i < trackDirsArray.size(); ++i) {
        QDir directory = QDir(trackDirsArray[i].toString());
        if (!directory.exists()) {
            qWarning() << "No directory: " << trackDirsArray[i].toString();
        }
        m_musicDirs.push_back(directory);
    }

    m_backgroundColor1      = QColor(m_json["backgroundColor1"].toString());
    m_backgroundColor2      = QColor(m_json["backgroundColor2"].toString());
    m_backgroundColor3      = QColor(m_json["backgroundColor3"].toString());

    m_borderColor           = QColor(m_json["borderColor"].toString());

    m_mainTextColor         = QColor(m_json["mainTextColor"].toString());
    m_secondaryTextColor    = QColor(m_json["secondaryTextColor"].toString());

    m_primaryColor          = QColor(m_json["primaryColor"].toString());
    m_primaryHoverColor     = QColor(m_json["primaryHoverColor"].toString());
    emit dataChanged();
}

void Config::setup() {
    m_mediaPlayer->clearTracks();
    for (const QDir& directory : m_musicDirs) {
        QDir dir = directory;
        dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
        QFileInfoList list = dir.entryInfoList();
        for (int i=0; i<list.size(); i++) {
            QFileInfo fileInfo = list.at(i);
            TrackInfo* trackInfo = new TrackInfo(   fileInfo.absoluteFilePath(),
                                                    m_mediaPlayer->getTrackImageProvider());
            m_mediaPlayer->addTrack(trackInfo);
        }
    }
}

QColor Config::backgroundColor1() const {
    return m_backgroundColor1;
}

QColor Config::backgroundColor2() const {
    return m_backgroundColor2;
}

QColor Config::backgroundColor3() const {
    return m_backgroundColor3;
}

QColor Config::borderColor() const {
    return m_borderColor;
}

QColor Config::mainTextColor() const {
    return m_mainTextColor;
}

QColor Config::secondaryTextColor() const {
    return m_secondaryTextColor;
}

QColor Config::primaryColor() const {
    return m_primaryColor;
}

QColor Config::primaryHoverColor() const {
    return m_primaryHoverColor;
}

void Config::reloadConfig() {
    readFile(m_path);
    reload();
    setup();
}
