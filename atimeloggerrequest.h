#ifndef ATIMELOGGERREQUEST_H
#define ATIMELOGGERREQUEST_H
#include <QNetworkRequest>
#include <QUrlQuery>

class AtimeloggerRequest: public QNetworkRequest
{
public:
    AtimeloggerRequest();
    AtimeloggerRequest(QString username, QString password);
    AtimeloggerRequest(QString username, QString password, uint from, uint to);
    AtimeloggerRequest(QString username, QByteArray authorization, uint from, uint to);
private:
    QString m_username;
    QString m_password;
    uint m_from;
    uint m_to;
    QUrlQuery m_query;
    QUrl types_url;
    QUrl intervals_url;
    void addQueryItems();
    QByteArray getAuthorization();
};

#endif // ATIMELOGGERREQUEST_H
