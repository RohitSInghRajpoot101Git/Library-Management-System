#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QTableView>
#include <QStandardItemModel>
#include "core/LibraryController.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(LibraryController *controller, QWidget *parent = nullptr);

private slots:
    void switchView(int index);
    void refreshBooks();
    void refreshMembers();
    void refreshTransactions();
    
    // Actions
    void onAddBook();
    void onDeleteBook();
    void onAddMember();
    void onDeleteMember();
    void onIssueBook();
    void onReturnBook();

private:
    void setupUi();
    QWidget* createDashboardPage();
    QWidget* createBookPage();
    QWidget* createMemberPage();
    QWidget* createCirculationPage();

    LibraryController *m_controller;
    QStackedWidget *m_stackedWidget;
    
    // Book View
    QTableView *m_bookTable;
    QStandardItemModel *m_bookModel;

    // Member View
    QTableView *m_memberTable;
    QStandardItemModel *m_memberModel;

    // Circulation View
    QTableView *m_transactionTable;
    QStandardItemModel *m_transactionModel;
};

#endif // MAINWINDOW_H
