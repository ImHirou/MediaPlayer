#ifndef TRACK_MODEL_H
#define TRACK_MODEL_H

#include <QAbstractListModel>
#include <QVector>

class TrackInfo;

class TrackModel : public QAbstractListModel {
Q_OBJECT

public:
    enum TrackRoles {
        NameRole = Qt::UserRole + 1,
        ArtistRole,
        IconRole,
        PathRole,
        IndexRole
    };

    explicit TrackModel(    QObject* parent = nullptr);

    int                     rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant                data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray>  roleNames() const override;

    void                    addTrack(TrackInfo* track);
    void                    clear();
    Q_INVOKABLE int         count() const;
    Q_INVOKABLE TrackInfo*  get(int row) const;
private:
    QVector<TrackInfo*>     m_tracks;
};

#endif // TRACK_MODEL_H

