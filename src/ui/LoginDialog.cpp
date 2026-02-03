#include "ui/LoginDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("LMS Login");
    setModal(true);
    setFixedSize(300, 150);

    QVBoxLayout *layout = new QVBoxLayout(this);

    // Username
    QHBoxLayout *userLayout = new QHBoxLayout();
    userLayout->addWidget(new QLabel("Username:"));
    m_usernameEdit = new QLineEdit();
    userLayout->addWidget(m_usernameEdit);
    layout->addLayout(userLayout);

    // Password
    QHBoxLayout *passLayout = new QHBoxLayout();
    passLayout->addWidget(new QLabel("Password:"));
    m_passwordEdit = new QLineEdit();
    m_passwordEdit->setEchoMode(QLineEdit::Password);
    passLayout->addWidget(m_passwordEdit);
    layout->addLayout(passLayout);

    // Buttons
    QHBoxLayout *btnLayout = new QHBoxLayout();
    QPushButton *loginBtn = new QPushButton("Login");
    QPushButton *cancelBtn = new QPushButton("Cancel");
    btnLayout->addWidget(loginBtn);
    btnLayout->addWidget(cancelBtn);
    layout->addLayout(btnLayout);

    connect(loginBtn, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelBtn, &QPushButton::clicked, this, &QDialog::reject);
}

QString LoginDialog::getUsername() const {
    return m_usernameEdit->text();
}

QString LoginDialog::getPassword() const {
    return m_passwordEdit->text();
}
