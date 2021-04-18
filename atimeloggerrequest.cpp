#include "atimeloggerrequest.h"

AtimeloggerRequest::AtimeloggerRequest()
{

}

AtimeloggerRequest::AtimeloggerRequest(QString username, QString password)
{
    m_username = username;
    m_password = password;
    m_from = 0;
    m_to = 0;

    types_url = QUrl("https://app.atimelogger.com/api/v2/types");
    m_query = QUrlQuery();
    types_url.setQuery(m_query);
    setRawHeader("Authorization", getAuthorization());
    setUrl(types_url);
}

AtimeloggerRequest::AtimeloggerRequest(QString username, QString password, uint from, uint to)
{
    m_username = username;
    m_password = password;
    m_from = from;
    m_to = to;

    intervals_url = QUrl("https://app.atimelogger.com/api/v2/intervals");
    m_query = QUrlQuery();
    addQueryItems();
    intervals_url.setQuery(m_query);
    setRawHeader("Authorization", getAuthorization());
    setUrl(intervals_url);
}

AtimeloggerRequest::AtimeloggerRequest(QString username, QByteArray authorization, uint from, uint to)
{
    m_username = username;
    m_from = from;
    m_to = to;

    intervals_url = QUrl("https://app.atimelogger.com/api/v2/intervals");
    m_query = QUrlQuery();
    addQueryItems();
    intervals_url.setQuery(m_query);
    setRawHeader("Authorization", authorization);
    setUrl(intervals_url);
}

void AtimeloggerRequest::addQueryItems()
{
    m_query.addQueryItem("from", QString::number(m_from));
    m_query.addQueryItem("to", QString::number(m_to));
    m_query.addQueryItem("limit", "999");
}

QByteArray AtimeloggerRequest::getAuthorization()
{
    QString authorization_string = m_username + QString(":") + m_password;
    QByteArray Base64_authorization = authorization_string .toLocal8Bit().toBase64();
    return QString("Basic " + Base64_authorization ).toLocal8Bit();

}


