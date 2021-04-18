#ifndef AUTHORIZATION_DIALOG_H
#define AUTHORIZATION_DIALOG_H
#include <QDialog>
#include <QMessageBox>



namespace Ui {
class AuthorizationDialog;
}

class DOWNLOADMODEL_EXPORT AuthorizationDialog : public QDialog
{
    Q_OBJECT


public:
    explicit AuthorizationDialog(QWidget *parent = nullptr);
    ~AuthorizationDialog();
    QString get_account();  //OK
    QString get_password();  //OK
private:
    Ui::AuthorizationDialog *ui;
public slots:
    void accept() override;  //C++11新增关键字override,在派生类中标识虚函数被覆盖。

};

#endif // AUTHORIZATION_DIALOG_H
