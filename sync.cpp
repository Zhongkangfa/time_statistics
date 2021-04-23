#include "sync.h"
#include "ui/choosetimedialog.h"
#include "ui/loginscreendialog.h"
#include "auth.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QSqlQuery>
#include <QJsonValue>
#include <QJsonObject>
#include <QMessageBox>
Sync::Sync(QSqlDatabase &db, QObject *parent) : QObject(parent)
  ,reply(nullptr)
{
    pd.reset();
    pd.setWindowTitle("下载");
    this->db = db;
    bytesTotal = 0;
}

Sync::~Sync()
{
    requester.saveAuthorization(db);
}

void Sync::start()
{
    download();
}

void Sync::download(QString type)
{
    //进行对话
    AtimeloggerRequest request = requester.write(db, type);
    if(!request.isEmpty()){
        //完成对话，开始下载
        pd.open();
        pd.setMinimum(0);
        pd.setMaximum(0);
        m_ba.clear();
        reply = networkManager.get(request);
        dealWhithReply(reply);
    }
    return;
}


void Sync::on_downloadProgress(qint64 bytesReceived)
{
    this->bytesTotal = this->bytesTotal + bytesReceived/1024;
    pd.setLabelText(QString::number(this->bytesTotal) + " KB");
}

void Sync::on_finished()
{
    int httpCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).value<int>();
    QNetworkReply::NetworkError downloadError = reply->error();

    reply->deleteLater();
    reply = Q_NULLPTR;

    if (downloadError == QNetworkReply::NoError)
    {
        if(m_ba.contains("intervals")){
            QJsonArray intervalArray = QJsonDocument::fromJson(m_ba)["intervals"].toArray();
            //清除掉上次留下的数据
            m_ba.clear();
            dealWhithIntervals(intervalArray);
        }
        else if(m_ba.contains("types")){
            QJsonArray types = QJsonDocument::fromJson(m_ba)["types"].toArray();
            //清除掉上次留下的数据
            m_ba.clear();
            dealWhithTypes(types);
        }
    }
    else{
        dealWhithDownloadError(downloadError, httpCode);
    }

}

void Sync::on_readyRead()
{
    m_ba.append(reply->readAll());
}

void Sync::dealWhithReply(QNetworkReply *reply)
{
    connect(&pd, &QProgressDialog::canceled, reply, &QNetworkReply::abort);
    connect(reply, &QNetworkReply::readyRead, this, &Sync::on_readyRead);
    connect(reply, &QNetworkReply::finished, this, &Sync::on_finished);
    connect(reply, &QNetworkReply::downloadProgress, this, &Sync::on_downloadProgress);
}

void Sync::dealWhithIntervals(QJsonArray intervals)
{
    if(!intervals.isEmpty())
    {
        //保存时间间隔
        insertInterval(intervals);
        //如果不为空,说明还能前进一步
        uint a = intervals.first()["from"].toDouble();
        uint b = intervals.last()["from"].toDouble();
        uint last_from = a <= b?a:b;

        if(requester.getFrom() < last_from && last_from < requester.getTo() && intervals.size() == 999)
        {
            reply = networkManager.get(requester.repeat(last_from));
            dealWhithReply(reply);
            return;
        }
    }
    pd.reset();
    bytesTotal = 0;
    download("types");
    return;

}

void Sync::dealWhithTypes(QJsonArray types)
{
    if(!types.isEmpty())
    {

        saveTypes(types);
    }
    pd.reset();
    bytesTotal = 0;
    return;
}

void Sync::saveTypes(QJsonArray types)
{
    //    qDebug() << types;
    if(db.open())
    {
        QSqlQuery query(db);
        if(!db.tables().contains("types")){
            query.exec(
                        "CREATE TABLE 'types' "
                            "("
                                "`type_guid`	TEXT NOT NULL UNIQUE,"
                                "`parent_guid`	TEXT,"
                                "`name`	TEXT NOT NULL,"
                                "`order`	INTEGER,"
                                "`revision`	INTEGER,"
                                "`group_`	BLOB,"
                                "`deleted`	BLOB,"
                                "`company`	BLOB,"
                                "PRIMARY KEY(type_guid)"
                            ")"
                        );
        }

        query.exec("DELETE FROM types");
        for (auto iter = types.begin(); iter != types.end(); iter++)
        {
            //
            QJsonObject type = iter->toObject();
            query.prepare("INSERT INTO [types] "
                    "([type_guid], [parent_guid], [order], [revision], [group_],[deleted],[company],[name]) "
                    "VALUES (?,?,?,?,?,?,?,?)");
            query.bindValue(0, type["guid"].toString());
            query.bindValue(1, type["parent"].toString());
            query.bindValue(2, type["order"].toInt());
            query.bindValue(3, type["revision"].toInt());
            query.bindValue(4, type["group_"].toBool());
            query.bindValue(5, type["deleted"].toBool());
            query.bindValue(6, type["company"].toBool());
            query.bindValue(7, type["name"].toString());
            query.exec();
        }
        db.close();

    }
}

void Sync::dealWhithDownloadError(QNetworkReply::NetworkError downloadError, int httpCode)
{
    if(downloadError == QNetworkReply::AuthenticationRequiredError)
    {
        //qDebug() << reply->error();
        QMessageBox::warning(nullptr, "温馨提示", "密码有误");
        requester.init();

    }
    else if (downloadError == QNetworkReply::OperationCanceledError)
    {
        QMessageBox::about(nullptr, "about","已成功取消下载");  //如何销毁?
    }
    else
    {
        QMessageBox::warning(nullptr, "about",QString::number(httpCode) + "错误!");
    }
    pd.reset();

}

void Sync::insertInterval(QJsonArray intervalArray)
{
    if(db.open())
    {
        QSqlQuery query(db);
        if(!db.tables().contains("interval")){
            query.exec(
                        "CREATE TABLE 'interval' "
                            "("
                                "`guid`	TEXT NOT NULL UNIQUE,"
                                "`type_guid`	TEXT NOT NULL,"
                                "`from`	INTEGER NOT NULL,"
                                "`to`	INTEGER NOT NULL,"
                                "`comment`	TEXT,"
                                "PRIMARY KEY(guid)"
                            ")"
            );
        }
        for (auto iter = intervalArray.begin(); iter != intervalArray.end(); iter++)
        {
            QJsonObject interval = iter->toObject();
            query.prepare("INSERT OR IGNORE INTO interval "
                          "([guid], [type_guid], [from], [to], [comment]) "
                          "VALUES (?,?,?,?,?)");
            query.bindValue(0, interval["guid"].toString());
            query.bindValue(1, interval["type"].toObject()["guid"].toString());
            query.bindValue(2, interval["from"].toDouble());
            query.bindValue(3, interval["to"].toDouble());
            query.bindValue(4, interval["comment"].toString());
            query.exec();
        }
        db.close();
    }
}



