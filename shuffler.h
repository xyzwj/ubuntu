#ifndef SHUFFLER_H
#define SHUFFLER_H

#include <QObject>
#include <QString>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QMediaPlayer>


class Shuffler: public QObject {
    Q_OBJECT

private:
    QNetworkAccessManager* nam;
    QMediaPlayer* player;

public:
    Shuffler(QObject *parent = 0);
    Q_INVOKABLE void channel(const QString &key) const;
    Q_INVOKABLE void play(const QString &url) const;

public slots:
    void finishedSlot(QNetworkReply* reply);

signals:
    void channelReady(const QVariantList& tracks);
};

#endif // SHUFFLER_H
