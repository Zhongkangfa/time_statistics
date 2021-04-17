#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui/choosetimedialog.h"



#include <QProgressDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , atimelogger(new AtimeloggerAPI)
{
    ui->setupUi(this);
    connect(ui->actionSycn, &QAction::triggered, this, &MainWindow::sync);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sync()
{
    //    选择需要同步的时间段
    ChooseTimeDialog choosetimedialog;
    if(choosetimedialog.exec())
    {
        atimelogger->work(choosetimedialog.from(), choosetimedialog.to());
    }

}


