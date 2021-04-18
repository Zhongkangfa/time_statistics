#ifndef RECORDREQUESTER_H
#define RECORDREQUESTER_H
#include "atimeloggerrequest.h"
#include <QSqlDatabase>


class RecordRequester
{
public:
    RecordRequester();
    AtimeloggerRequest write(QSqlDatabase &db);
    AtimeloggerRequest repeat(uint last);
    bool hasAuthorizationAndUsername();
    bool askUsernameAndPassword();
    bool verify();
    void getAuthorizationAndUsername(QSqlDatabase &db);
    void ChooseLength();
private:
    QString username;
    QString password;
    QByteArray authorization;
    uint from;
    uint to;
};

#endif // RECORDREQUESTER_H
