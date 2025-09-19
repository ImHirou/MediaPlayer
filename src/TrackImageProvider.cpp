#include "TrackImageProvider.h"
#include "MediaPlayer.h"

#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QImage>
#include <QString>

TrackImageProvider::TrackImageProvider(const QString& name, MediaPlayer* mediaPlayer) :
    QQuickImageProvider(QQuickImageProvider::Image) {
    mediaPlayer->getQmlEngine()->addImageProvider(name, this);
}

QImage TrackImageProvider::requestImage(const QString& id, QSize *size, const QSize &requestedSize) {
    if (!m_images.contains(id)) return QImage();
    
    QImage image = m_images.value(id);
    if (size) *size = image.size();
    
    if (requestedSize.isValid())
        return image.scaled(requestedSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    return image;
}
