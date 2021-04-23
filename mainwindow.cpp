#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui/choosetimedialog.h"
#include "ui/loginscreendialog.h"
#include "auth.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QSqlQuery>
#include <QJsonValue>
#include <QJsonObject>
#include <QMessageBox>





#include <QProgressDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pd.reset();
    pd.setWindowTitle("下载");
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/QtMyProject/data/atimelogger.db");
    connect(ui->actionSycn, &QAction::triggered, this, &MainWindow::sync);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sync()
{

    AtimeloggerRequest request = requester.write(db);
    if(request.isEmpty()){
        return;
    }
    reply = networkManager.get(request);

    pd.open();
    pd.setMinimum(0);
    pd.setMaximum(0);

    dealWhithReply(reply);
}

void MainWindow::on_downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    pd.setLabelText(QString::number(bytesReceived/1024) + " KB");
}

void MainWindow::on_finished()
{
    //清除掉上次留下的数据
    m_ba.clear();

    //如果任何错误,就不要readAll reply了,因为会出错.

    if (reply->isReadable())
    {
        m_ba = reply->readAll();  //为什么不放到下面的判断中?因为我的reply需要提前删除掉.
    }


    int httpCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).value<int>();
    QNetworkReply::NetworkError downloadError = reply->error();

    //为什么要提删除掉？因为我后面需要递归。
    reply->deleteLater();
    reply = Q_NULLPTR;


    if (downloadError == QNetworkReply::NoError)
    {
        QJsonArray intervalArray = QJsonDocument::fromJson(m_ba)["intervals"].toArray();
        dealWhithIntervals(intervalArray);
    }
    else{
        dealWhithDownloadError(downloadError, httpCode);
    }
}

void MainWindow::dealWhithReply(QNetworkReply *reply)
{
    connect(&pd, &QProgressDialog::canceled, reply, &QNetworkReply::abort);
    connect(reply, &QNetworkReply::finished, this, &MainWindow::on_finished);
    connect(reply, &QNetworkReply::downloadProgress, this, &MainWindow::on_downloadProgress);
}

void MainWindow::dealWhithIntervals(QJsonArray intervals)
{
    if(!intervals.isEmpty())
    {
        //保存时间间隔
        insertInterval(intervals);
        //如果不为空,说明还能前进一步
        uint a = intervals.first()["to"].toDouble();
        uint b = intervals.last()["to"].toDouble();
        uint last_from = a >= b?a:b;

        if(requester.getFrom() < last_from && last_from < requester.getTo())
        {
            reply = networkManager.get(requester.repeat(last_from));
            dealWhithReply(reply);
            return;
        }
        pd.reset();
        return;
    }
    else if(intervals.isEmpty())
    {
        pd.reset();
    }


}
void MainWindow::insertInterval(QJsonArray intervalArray)
{
    if(db.open())
    {
        QSqlQuery query(db);
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


void MainWindow::dealWhithDownloadError(QNetworkReply::NetworkError downloadError,int httpCode)
{
    if(downloadError == QNetworkReply::AuthenticationRequiredError)
    {
        //qDebug() << reply->error();
        QMessageBox::warning(this, "温馨提示", "密码有误");
        authorization.clear();
        pd.reset();
        //        getLastRecordTime();
    }
    else if (downloadError == QNetworkReply::OperationCanceledError)
    {
        QMessageBox::about(&pd, "about","已成功取消下载");  //如何销毁?
    }
    else
    {

        QMessageBox::warning(&pd, "about",QString::number(httpCode) + "错误!");
    }

}



