#include "MediaPlayer.h"
#include "TrackImageProvider.h"
#include "TrackInfo.h"
#include "TrackModel.h"
#include "Config.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QObject>
#include <QPushButton>

#include <QDir>
#include <QString>

MediaPlayer::MediaPlayer(int argc, char* argv[]) {
    m_application = new QGuiApplication(argc, argv);

    m_engine = new QQmlApplicationEngine();
    
    m_trackImageProvider = new TrackImageProvider("tracks", this);

    m_trackList = new TrackModel("trackModel", this);
    
    m_config = new Config("./config.json", this, m_application);

    m_config->reload();
    m_engine->rootContext()->setContextProperty("config", m_config);
    m_config->setup();

    m_engine->loadFromModule("app", "Main");
    if (m_engine->rootObjects().isEmpty())
        qDebug() << "No rootObjects"; 
}

int MediaPlayer::exec() {
    return m_application->exec();
}

void MediaPlayer::addTrack(TrackInfo* trackInfo) {
    m_trackList->addTrack(trackInfo);
}

void MediaPlayer::clearTracks() {
    m_trackList->clear();
}

QGuiApplication* MediaPlayer::getApplication() {
    return m_application;
}

QQmlApplicationEngine* MediaPlayer::getQmlEngine() {
    return m_engine;
}

TrackImageProvider* MediaPlayer::getTrackImageProvider() {
    return m_trackImageProvider;
}

TrackModel* MediaPlayer::getTrackList() {
    return m_trackList;
}

Config* MediaPlayer::getConfig() {
    return m_config;
}
