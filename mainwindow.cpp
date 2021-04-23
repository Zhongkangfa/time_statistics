#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("atimelogger.db");
    downloader = new Sync(db);
    connect(ui->actionSycn, &QAction::triggered, downloader, &Sync::start);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete downloader;
}




