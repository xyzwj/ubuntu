
#include <QObject>
#include <QString>
#include <QList>
#include <QDebug>

#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QMediaPlayer>
#include <QJsonDocument>

#include "shuffler.h"


Shuffler::Shuffler(QObject *parent): QObject(parent) {
    nam = new QNetworkAccessManager(this);
    QObject::connect(nam, SIGNAL(finished(QNetworkReply*)),
             this, SLOT(finishedSlot(QNetworkReply*)));

    player = new QMediaPlayer(this);
}

void Shuffler::channel(const QString &key) const {

    qDebug() << "Shuffler::channel: " << key;
    QUrl url(QString("http://api.shuffler.fm/v1/channels/") + key + QString("?api-key=api-test-key"));
    QNetworkReply* reply = nam->get(QNetworkRequest(url));
    // NOTE: Store QNetworkReply pointer (maybe into caller).
    // When this HTTP request is finished you will receive this same
    // QNetworkReply as response parameter.
    // By the QNetworkReply pointer you can identify request and response.
}

void Shuffler::play(const QString &url) const {
    qDebug() << "Shuffler::play: " << url;

    player->stop();
    player->setMedia(QUrl(url));
    player->setVolume(50);
    player->play();
}

void Shuffler::finishedSlot(QNetworkReply* reply)
{
    qDebug() << "Shuffler::finishedSlotl {";
    // Reading attributes of the reply
    // e.g. the HTTP status code
    QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    // Or the target URL if it was a redirect:
    QVariant redirectionTargetUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    // see CS001432 on how to handle this

    // no error received?
    if (reply->error() == QNetworkReply::NoError)
    {
        qDebug() << "Shuffler::finishedSlotl: GOOD";
        // read data from QNetworkReply here

        // Reading bytes form the reply
        QByteArray bytes = reply->readAll();  // bytes
        QString string(bytes); // string

        // transform in a hash like a boss
        /*
        QString hacked = QString("\"response\": {") + string + QString("}");

        bool ok = true;

        qDebug() << "RESPONSO: " << hacked;

        // https://github.com/ereilin/qt-json
        QVariantMap tracks = QtJson::parse(hacked, ok).toMap();
        */

        QJsonDocument d = QJsonDocument::fromJson(string.toUtf8());
        QVariantList tracks = d.toVariant().toList();

        // fire the event to the qml side of the force
        qDebug() << "going to call onChannelReady(tracks);";
        emit channelReady(tracks);

    }
    // Some http error received
    else
    {
        // handle errors here
        qDebug() << "Shuffler::finishedSlotl: ERRRRRRRRRRROOOOOORRRRR";
    }

    // We receive ownership of the reply object
    // and therefore need to handle deletion.
    delete reply;
}
