#ifndef AUTH_H
#define AUTH_H
#include <QString>
#include <QSqlDatabase>
#include <QByteArray>

class Auth
{
public:
    Auth();

    QString m_username;
    QByteArray m_authorization;

    QByteArray getAuthorization(QSqlDatabase &db);
    bool save(QString &username, QByteArray &authorization, QSqlDatabase &db);
    QString getUsername() const;
};

#endif // AUTH_H
