#ifndef TRACK_IMAGE_PROVIDER_H
#define TRACK_IMAGE_PROVIDER_H

#include <QQuickImageProvider>
#include <QMap>
class QImage;
class QString;

class TrackImageProvider : public QQuickImageProvider {
public:
    TrackImageProvider();
    QMap<QString, QImage> m_images;

    virtual QImage requestImage(const QString& id, QSize *size, const QSize &requestedSize) override;
};

#endif //TRACK_IMAGE_PROVIDER_H
