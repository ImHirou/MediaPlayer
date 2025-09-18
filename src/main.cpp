#include "MediaPlayer.h"

#include <iostream>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char* argv[]) {
    MediaPlayer* mediaPlayer = new MediaPlayer(argc, argv);
    return mediaPlayer->exec();
}
