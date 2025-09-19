#ifndef MEDIA_PLAYER_H
#define MEDIA_PLAYER_H

class QGuiApplication;
class QQmlApplicationEngine;
class QString;

class TrackImageProvider;
class TrackInfo;
class TrackModel;

class Config;

class MediaPlayer {
private:
    QGuiApplication*        m_application;
    QQmlApplicationEngine*  m_engine;

    TrackImageProvider*     m_trackImageProvider;
    TrackModel*             m_trackList;

    Config*                 m_config;
public:
    MediaPlayer(            int argc, 
                            char* agrv[]);

    int                     exec();
    
    void                    addTrack(TrackInfo* trackInfo);
    void                    clearTracks();

    QGuiApplication*        getApplication();
    QQmlApplicationEngine*  getQmlEngine();
    
    TrackImageProvider*     getTrackImageProvider();
    TrackModel*             getTrackList();

    Config*                 getConfig();
};

#endif //MEDIA_PLAYER_H
