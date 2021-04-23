#ifndef RECORDREQUESTER_H
#define RECORDREQUESTER_H
#include "atimeloggerrequest.h"
#include "auth.h"
#include <QSqlDatabase>


class RecordRequester
{
public:
    RecordRequester();
    AtimeloggerRequest write(QSqlDatabase &db);
    AtimeloggerRequest repeat(uint last);
    uint getFrom() const;

    uint getTo() const;
    uint getLastRecordTime(QSqlDatabase &db);

private:
    QString username;
    QByteArray authorization;
    uint from;
    uint to;
    Auth auth;
};

#endif // RECORDREQUESTER_H
