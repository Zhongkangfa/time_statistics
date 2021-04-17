#ifndef LOGINSCREENDIALOG_H
#define LOGINSCREENDIALOG_H

#include <QDialog>

namespace Ui {
class LoginScreenDialog;
}

class LoginScreenDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginScreenDialog(QWidget *parent = nullptr);
    ~LoginScreenDialog();

private:
    Ui::LoginScreenDialog *ui;
};

#endif // LOGINSCREENDIALOG_H
