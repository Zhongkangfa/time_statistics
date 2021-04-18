#include "authorization_dialog.h"
#include "ui_authorization_dialog.h"

AuthorizationDialog::AuthorizationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthorizationDialog)
{
    ui->setupUi(this);
}

AuthorizationDialog::~AuthorizationDialog()
{
    delete ui;
}


QString AuthorizationDialog::get_account()
{
    return ui->account_lineEdit->text();
}

QString AuthorizationDialog::get_password()
{
    return ui->password_lineEdit->text();
}

void AuthorizationDialog::accept()
{
    if(get_account().isEmpty())
    {
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


