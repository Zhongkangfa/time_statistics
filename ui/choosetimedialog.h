#ifndef CHOOSETIMEDIALOG_H
#define CHOOSETIMEDIALOG_H

#include <QDialog>

namespace Ui {
class ChooseTimeDialog;
}

class ChooseTimeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseTimeDialog(QWidget *parent = nullptr);
    ~ChooseTimeDialog();
    uint from();
    uint to();
    void setLastDateTime(uint last);

signals:
     void submited(uint from, uint to);


     // QDialog interface
public slots:
     void accept() override;


private slots:
     void on_toDateTimeEdit_dateTimeChanged(const QDateTime &dateTime);
     void on_fromDateTimeEdit_dateTimeChanged(const QDateTime &dateTime);

private:
    Ui::ChooseTimeDialog *ui;
};

#endif // CHOOSETIMEDIALOG_H
