#include "loginscreendialog.h"
#include "ui_loginscreendialog.h"
#include <QMessageBox>
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

QString LoginScreenDialog::get_account()
{
    return ui->accountLineEdit->text();
}

QString LoginScreenDialog::get_password()
{
    return ui->passwordLlineEdit->text();
}

void LoginScreenDialog::accept()
{
    if(get_account().isEmpty()){
        QMessageBox::warning(this, "错误", "请输入您的atimelogger账号。\n通常是您的邮箱。");
        return;

    }
    if (get_password().isEmpty())
    {
        QMessageBox::warning(this, "错误", "请输入您的密码。");
        return;
    }
    else
    {
        //因为是继承关系，调用的是父类的accept函数是正常操作。
        return QDialog::accept();
    }
}
