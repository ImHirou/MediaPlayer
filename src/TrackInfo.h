#ifndef TRACK_INFO_H
#define TRACK_INFO_H

#include <QObject>
#include <QUrl>
class QMediaPlayer;
class TrackImageProvider;
class QString;

class TrackInfo : public QObject {
Q_OBJECT
Q_PROPERTY(QString  name    READ name   NOTIFY dataChanged)
Q_PROPERTY(QString  artist  READ artist NOTIFY dataChanged)
Q_PROPERTY(QUrl     icon    READ icon   NOTIFY dataChanged)
Q_PROPERTY(int      index   READ index  NOTIFY dataChanged)
Q_PROPERTY(QString  path    READ path   CONSTANT)
private:
    QString                 m_name;
    QString                 m_artist;
    QUrl                    m_icon;
    QString                 m_path;
    int                     m_index;
    TrackImageProvider*     m_provider;
    QMediaPlayer*           m_tempPlayer;
    bool                    m_metadataLoaded = false;
public:
    explicit TrackInfo(     const QString& path, 
                            TrackImageProvider* provider, 
                            QObject* parent = nullptr); 

    QString                 name() const;
    QString                 artist() const;
    QUrl                    icon() const;
    QString                 path() const;
    int                     index() const;
    bool                    isMetadataLoaded() const;

    void                    onMetaDataChanged();
signals:
    void                    dataChanged();
};

#endif //TRACK_INFO_H
