#include "auth.h"
#include <QSqlQuery>

Auth::Auth()
{

}

QString Auth::getUsername() const
{
    return m_username;
}


QByteArray Auth::getAuthorization(QSqlDatabase &db)
{
    if(db.open()){
        QSqlQuery authorizationQuery("SELECT [value] FROM authorization WHERE type='authorization'", db);
        QSqlQuery accountQuery("SELECT [value] FROM authorization WHERE type='account'", db);
        bool ok = authorizationQuery.isNull(0) || accountQuery.isNull(0);
        if(!ok)
        {
            authorizationQuery.first();
            accountQuery.first();
            m_username = accountQuery.value(0).toString();
            m_authorization = authorizationQuery.value(0).toByteArray();
        }
        authorizationQuery.clear();
        accountQuery.clear();
        db.close();  //关闭数据库连接，释放获得的任何资源，并使数据库中使用的任何现有QSqlQuery对象无效。
    }
    else
    {
        qDebug() << "数据库无法打开，数据获取失败。";
        m_username = "";
        m_authorization = QByteArray();
    }
    return m_authorization;
}

bool Auth::save(QString &username, QByteArray &authorization, QSqlDatabase &db)
{
    if(db.open())
    {
        QSqlQuery query(db);
        query.prepare("UPDATE authorization SET value = ? WHERE type = 'authorization'" );
        query.bindValue(0, authorization);
        query.exec();

        query.clear();

        query.prepare("UPDATE authorization SET value = ? WHERE type = 'account'" );
        query.bindValue(0, username);
        query.exec();
        db.close();
        return true;
    }else{
        return false;
    }
}
