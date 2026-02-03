#include <QApplication>
#include "core/LibraryController.h"
#include "ui/LoginDialog.h"
#include "ui/MainWindow.h"
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Initialize Controller (Business Logic)
    LibraryController controller;

    // Show Login Dialog
    LoginDialog loginDialog;
    if (loginDialog.exec() == QDialog::Accepted) {
        if (controller.login(loginDialog.getUsername(), loginDialog.getPassword())) {
            // Login Success
            MainWindow w(&controller);
            w.show();
            return app.exec();
        } else {
            QMessageBox::critical(nullptr, "Error", "Invalid Username or Password");
            return 1;
        }
    }

    return 0; // User cancelled login
}
