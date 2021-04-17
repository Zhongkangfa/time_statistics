#include "loginscreendialog.h"
#include "ui_loginscreendialog.h"

LoginScreenDialog::LoginScreenDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginScreenDialog)
{
    ui->setupUi(this);
}

LoginScreenDialog::~LoginScreenDialog()
{
    delete ui;
}
