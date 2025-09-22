#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>

#include <QList>
#include <QJsonObject>
#include <QColor>

#include <QDir>
class QString;

class MediaPlayer;

class Config : public QObject {
Q_OBJECT
Q_PROPERTY(QColor backgroundColor1      READ backgroundColor1   NOTIFY dataChanged)
Q_PROPERTY(QColor backgroundColor2      READ backgroundColor2   NOTIFY dataChanged)
Q_PROPERTY(QColor backgroundColor3      READ backgroundColor3   NOTIFY dataChanged)
Q_PROPERTY(QColor borderColor           READ borderColor        NOTIFY dataChanged)
Q_PROPERTY(QColor mainTextColor         READ mainTextColor      NOTIFY dataChanged)
Q_PROPERTY(QColor secondaryTextColor    READ secondaryTextColor NOTIFY dataChanged)
Q_PROPERTY(QColor primaryColor          READ primaryColor       NOTIFY dataChanged)
Q_PROPERTY(QColor primaryHoverColor     READ primaryHoverColor  NOTIFY dataChanged)
Q_PROPERTY(qreal  volume                READ volume             WRITE volume NOTIFY dataChanged)
private:
    MediaPlayer*    m_mediaPlayer;
    QString         m_path;
    QJsonObject     m_json;
    QList<QDir>     m_musicDirs;
    QColor          m_backgroundColor1;
    QColor          m_backgroundColor2;
    QColor          m_backgroundColor3;
    QColor          m_borderColor;
    QColor          m_mainTextColor;
    QColor          m_secondaryTextColor;
    QColor          m_primaryColor;
    QColor          m_primaryHoverColor;
    qreal           m_volume;
public:
    Config(const QString& path, MediaPlayer* mediaPlayer, QObject* parent = nullptr);
   
    void readFile();
    void reload();
    void setup();

    QColor backgroundColor1() const;
    QColor backgroundColor2() const;
    QColor backgroundColor3() const;
    QColor borderColor() const;
    QColor mainTextColor() const;
    QColor secondaryTextColor() const;
    QColor primaryColor() const;
    QColor primaryHoverColor() const;
    qreal  volume() const;
    
    void volume(qreal value);

    Q_INVOKABLE void writeFile(bool overwriteJson = false);
    Q_INVOKABLE void reloadConfig();
signals:
    void dataChanged();
};

#endif //CONFIG_H
