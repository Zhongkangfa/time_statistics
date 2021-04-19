#include "auth.h"
#include <QSqlQuery>
#include "ui/loginscreendialog.h"

Auth::Auth()
{

}

QString Auth::getUsername() const
{
    return username;
}

void Auth::createAuthorization(QString username, QString password)
{
    QString authorization_string = username + QString(":") + password;
    QByteArray Base64_authorization = authorization_string .toLocal8Bit().toBase64();
    authorization = QString("Basic " + Base64_authorization ).toLocal8Bit();
}


QByteArray Auth::getAuthorization(QSqlDatabase &db)
{
    if(db.open()){
        qDebug() << "数据库打开了！";
        qDebug() << db.tables();
        QSqlQuery query("SELECT * FROM authorization", db);
        query.first();

        //如果查询不是活动的，查询没有定位在有效的记录上，没有这样的字段，或者字段为空，返回true;
        if(query.isValid())
        {
            qDebug() << "我进来了？";
            if(query.value(0).toString() == "account")
            {
                username = query.value(1).toString();
                query.next();
                authorization = query.value(1).toByteArray();
            }else{
                authorization = query.value(1).toByteArray();
                query.next();
                username = query.value(1).toString();
            }
            qDebug() << username;
            qDebug() << authorization;
        }
        query.clear();
        db.close();  //关闭数据库连接，释放获得的任何资源，并使数据库中使用的任何现有QSqlQuery对象无效。
        if(authorization.isEmpty()){
            LoginScreenDialog dialog;
            if(dialog.exec()){
                //获取账号和密码
                createAuthorization(dialog.get_account(), dialog.get_password());
            }

        }
    }
    else
    {
        qDebug() << "数据库无法打开，数据获取失败。";
        username = "";
        authorization = QByteArray();
    }
    return authorization;
}

bool Auth::save(QSqlDatabase &db)
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
        qDebug() << "数据库没打开！";
        return false;
    }
}
