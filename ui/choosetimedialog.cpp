#include "choosetimedialog.h"
#include "ui_choosetimedialog.h"

ChooseTimeDialog::ChooseTimeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseTimeDialog)
{
    ui->setupUi(this);
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

void ChooseTimeDialog::accept()
{
    //hide();
    emit submited(from(), to());
    return QDialog::accept();
}


