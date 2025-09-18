#include "TrackImageProvider.h"
#include <QImage>
#include <QString>

TrackImageProvider::TrackImageProvider() :
    QQuickImageProvider(QQuickImageProvider::Image) {}

QImage TrackImageProvider::requestImage(const QString& id, QSize *size, const QSize &requestedSize) {
    if (!m_images.contains(id)) return QImage();
    
    QImage image = m_images.value(id);
    if (size) *size = image.size();
    
    if (requestedSize.isValid())
        return image.scaled(requestedSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    return image;
}
