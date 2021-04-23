#include "localstorage.h"

LocalStorage::LocalStorage(QSqlDatabase &db, QObject *parent) : QObject(parent)
{
    this->db = db;
}

uint LocalStorage::totalByInterval(QString guid, uint start, uint end)
{
    Q_ASSERT_X(start < end, "注意！", "开始时间必须小于结束时间！");
    uint sum = 0;

    if(db.open())
    {
        //---获取数据---
        QString sql = "SELECT * "
                    "FROM interval "
                    "WHERE type_guid = :guid "
                    "AND [to] > :start "
                    "AND [from] < :end ";
        qDebug() << sql;
        QSqlQuery query(db);
        query.prepare(sql);
        query.bindValue(":guid", guid);
        query.bindValue(":start", start);
        query.bindValue(":end", end);
        query.exec();
        if(query.first())
        {
            sum = query.value(0).toUInt();
        }
        db.close();
    }
    return sum;
}
