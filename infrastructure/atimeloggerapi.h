#ifndef ATIMELOGGERAPI_H
#define ATIMELOGGERAPI_H

#include <QObject>

//about network
#include <QUrl>
#include <QNetworkAccessManager>
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QProgressDialog>


class AtimeloggerAPI:public QObject
{
    Q_OBJECT
public:
    AtimeloggerAPI();
    void work(uint from, uint to);

public slots:
    void on_finished();


private:
    const QUrl m_interval_url;
    const QUrl m_type_url;
    QNetworkAccessManager networkManager;
    QNetworkReply *reply;
    uint lastRecordOfTime;
    uint aim;
    QByteArray download_byte;
    QProgressDialog *progress_dialog;
    uint ExecutionTimes;

private:
    void visit(uint from, uint to);
    void download(uint from, uint to);
    QByteArray getAuthorization();
    void addQueryItems(QUrlQuery &intervalQuery,uint from, uint to);
    QUrl getIntervalUrlWithQuery(uint from, uint to);




};

#endif // ATIMELOGGERAPI_H
