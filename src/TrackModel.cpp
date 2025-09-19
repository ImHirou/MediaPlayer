#include "TrackModel.h"
#include "MediaPlayer.h"
#include "TrackInfo.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QString>
#include <QVariantMap>

TrackModel::TrackModel(const QString& name, MediaPlayer* mediaPlayer) 
    : QAbstractListModel(mediaPlayer->getApplication()) {
    mediaPlayer->getQmlEngine()->rootContext()->setContextProperty(name, this);
}

int TrackModel::rowCount(const QModelIndex& parent) const {
    if (parent.isValid()) return 0;
    return m_tracks.size();
}

QVariant TrackModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || index.row() < 0 || index.row() >= m_tracks.size())
        return QVariant();

    auto track = m_tracks.at(index.row());
    switch (role) {
    case NameRole: return track->name();
    case ArtistRole: return track->artist();
    case IconRole: return track->icon();
    case PathRole: return track->path();
    case IndexRole: return index.row();
    }
    return QVariant();
}

QHash<int, QByteArray> TrackModel::roleNames() const {
    return {
        { NameRole, "name" },
        { ArtistRole, "artist" },
        { IconRole, "icon" },
        { PathRole, "path" },
        { IndexRole, "trackIndex"}
    };
}

int TrackModel::count() const {
    return m_tracks.size();
}

TrackInfo* TrackModel::get(int row) const {
    if (row < 0 || row >= rowCount())
        return nullptr;
    return m_tracks.at(row);
}

void TrackModel::addTrack(TrackInfo* track) {
    beginInsertRows(QModelIndex(), m_tracks.size(), m_tracks.size());
    m_tracks.append(track);
    endInsertRows();

    // Подписываемся на сигнал TrackInfo → обновляем модель
    connect(track, &TrackInfo::dataChanged, this, [this, track]() {
        int row = m_tracks.indexOf(track);
        if (row >= 0) {
            QModelIndex idx = index(row);
            emit dataChanged(idx, idx);
        }
    });
}

void TrackModel::clear() {
   beginRemoveRows(QModelIndex(), 0, count() - 1);
   for (auto* track : m_tracks) {
       delete track;
   }
   m_tracks.clear();
   endRemoveRows();
}

