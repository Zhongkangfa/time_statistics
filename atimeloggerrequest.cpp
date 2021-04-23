#include "atimeloggerrequest.h"

AtimeloggerRequest::AtimeloggerRequest()
{

}

AtimeloggerRequest::AtimeloggerRequest(QString username, QByteArray authorization, uint from, uint to)
{
    this->username = username;
    this->authorization = authorization;
    this->from = from;
    this->to = to;
    QUrl url;

    if(from == 0 || to ==0){
        url = QUrl("https://app.atimelogger.com/api/v2/types");

    }else{
        url = QUrl("https://app.atimelogger.com/api/v2/intervals");
        query = QUrlQuery();
        addQueryItems();
        url.setQuery(query);
    }
    setRawHeader("Authorization", this->authorization);
    setUrl(url);
}

bool AtimeloggerRequest::isEmpty()
{
    return this->authorization.isEmpty();
}

void AtimeloggerRequest::addQueryItems()
{
    query.addQueryItem("from", QString::number(from));
    query.addQueryItem("to", QString::number(to));
    query.addQueryItem("limit", "999");
}
