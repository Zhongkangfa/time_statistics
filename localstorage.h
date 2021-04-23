#ifndef LOCALSTORAGE_H
#define LOCALSTORAGE_H

#include <QObject>

#include <QSqlDatabase>
#include <QSqlQuery>

class LocalStorage : public QObject
{
    Q_OBJECT
public:
    explicit LocalStorage(QSqlDatabase &db, QObject *parent = nullptr);
public slots:
    uint totalByInterval(QString guid, uint start, uint end);

signals:

private:
    QSqlDatabase db;

};

#endif // LOCALSTORAGE_H
