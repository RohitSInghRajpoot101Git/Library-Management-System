#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QLineEdit>

class LoginDialog : public QDialog {
    Q_OBJECT
public:
    explicit LoginDialog(QWidget *parent = nullptr);
    QString getUsername() const;
    QString getPassword() const;

private:
    QLineEdit *m_usernameEdit;
    QLineEdit *m_passwordEdit;
};

#endif // LOGINDIALOG_H
