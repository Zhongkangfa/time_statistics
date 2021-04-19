#ifndef AUTH_H
#define AUTH_H
#include <QString>
#include <QSqlDatabase>
#include <QByteArray>

class Auth
{
public:
    Auth();

    QString username;
    QByteArray authorization;

    QByteArray getAuthorization(QSqlDatabase &db);
    bool save(QSqlDatabase &db);
    QString getUsername() const;
    void createAuthorization(QString username, QString password);
};

#endif // AUTH_H
