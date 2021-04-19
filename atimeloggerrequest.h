#ifndef ATIMELOGGERREQUEST_H
#define ATIMELOGGERREQUEST_H
#include <QNetworkRequest>
#include <QUrlQuery>

class AtimeloggerRequest: public QNetworkRequest
{
public:
    AtimeloggerRequest();
    AtimeloggerRequest(QString username, QByteArray authorization, uint from=0, uint to=0);
private:
    QString username;
    QString password;
    uint from;
    uint to;
    QUrlQuery query;
    QByteArray authorization;
    void addQueryItems();
};

#endif // ATIMELOGGERREQUEST_H
