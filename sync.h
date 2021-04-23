#ifndef SYNC_H
#define SYNC_H

#include <QObject>
#include <QSqlDatabase>
#include <QNetworkAccessManager>
#include "atimeloggerrequest.h"
#include "recordrequester.h"
#include "QNetworkReply"
#include "QProgressDialog"

class Sync : public QObject
{
    Q_OBJECT
public:
    explicit Sync(QSqlDatabase &db, QObject *parent = nullptr);
public slots:
    void start();
    void on_downloadProgress(qint64 bytesReceived);
    void on_finished();
    void on_readyRead();
private:
    QNetworkAccessManager networkManager;
    QSqlDatabase db;
    RecordRequester requester;
    QNetworkReply * reply;
    QProgressDialog pd;
    QByteArray m_ba;
    qint64 bytesTotal;

private:
    void download(QString type = "intervals");
    void dealWhithReply(QNetworkReply *reply);
    void dealWhithIntervals(QJsonArray intervals);
    void dealWhithTypes(QJsonArray types);
    void saveTypes(QJsonArray types);
    void dealWhithDownloadError(QNetworkReply::NetworkError downloadError, int httpCode);
    void insertInterval(QJsonArray intervalArray);

signals:

};

#endif // SYNC_H
