#include "choosetimedialog.h"
#include "ui_choosetimedialog.h"

ChooseTimeDialog::ChooseTimeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseTimeDialog)
{
    ui->setupUi(this);
    QDateTime now = QDateTime::currentDateTime();
    ui->toDateTimeEdit->setDateTime(now);
    ui->fromDateTimeEdit->setDateTime(now);
}

ChooseTimeDialog::~ChooseTimeDialog()
{
    delete ui;
}

uint ChooseTimeDialog::from()
{
    return ui->fromDateTimeEdit->dateTime().toSecsSinceEpoch();
}

uint ChooseTimeDialog::to()
{
    return ui->toDateTimeEdit->dateTime().toSecsSinceEpoch();
}

void ChooseTimeDialog::setLastDateTime(uint last)
{
    QDateTime new_from;
    new_from.setSecsSinceEpoch(last);
    ui->fromDateTimeEdit->setDateTime(new_from);
}

void ChooseTimeDialog::accept()
{
    return QDialog::accept();
}



void ChooseTimeDialog::on_toDateTimeEdit_dateTimeChanged(const QDateTime &dateTime)
{
    ui->fromDateTimeEdit->setMaximumDateTime(dateTime);
}

void ChooseTimeDialog::on_fromDateTimeEdit_dateTimeChanged(const QDateTime &dateTime)
{
    ui->toDateTimeEdit->setMinimumDateTime(dateTime);
}
