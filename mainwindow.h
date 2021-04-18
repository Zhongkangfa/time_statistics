#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QNetworkAccessManager>
#include "atimeloggerrequest.h"
#include "recordrequester.h"

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

private:
    void sync();
    //core
private:

};
#endif // MAINWINDOW_H
