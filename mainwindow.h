#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QNetworkAccessManager>
#include "atimeloggerrequest.h"
#include "recordrequester.h"
#include "QNetworkReply"
#include "QProgressDialog"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
//    超级重要的基础
    QNetworkAccessManager networkManager;
    QSqlDatabase db;
    QString username;
    QString password;
    QByteArray authorization;
    RecordRequester requester;
    QNetworkReply * reply;
    QProgressDialog pd;
    uint times;
    QByteArray m_ba;

private slots:
    void sync();
    void on_downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void on_finished();
    //core
private:
    void dealWhithReply(QNetworkReply *reply);
    void dealWhithIntervals(QJsonArray intervals);
    void dealWhithDownloadError(QNetworkReply::NetworkError downloadError, int httpCode);
    void insertInterval(QJsonArray intervalArray);


};
#endif // MAINWINDOW_H
