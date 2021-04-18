#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui/choosetimedialog.h"
#include "ui/loginscreendialog.h"
#include "auth.h"




#include <QProgressDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    requester.write(db);
//    networkManager.get();
}


