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

signals:
     void submited(uint from, uint to);


     // QDialog interface
public slots:
     void accept() override;


private:
    Ui::ChooseTimeDialog *ui;


};

#endif // CHOOSETIMEDIALOG_H
