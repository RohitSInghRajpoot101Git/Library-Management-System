#include "ui/MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QHeaderView>
#include <QInputDialog>
#include <QMessageBox>
#include <QDate>
#include <QFormLayout>

MainWindow::MainWindow(LibraryController *controller, QWidget *parent)
    : QMainWindow(parent), m_controller(controller)
{
    setupUi();
    refreshBooks();
    refreshMembers();
    refreshTransactions();
}

void MainWindow::setupUi() {
    setWindowTitle("Library Management System");
    resize(1000, 700);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

    // Sidebar
    QVBoxLayout *sidebarLayout = new QVBoxLayout();
    QPushButton *btnDashboard = new QPushButton("Dashboard");
    QPushButton *btnBooks = new QPushButton("Books");
    QPushButton *btnMembers = new QPushButton("Members");
    QPushButton *btnCirculation = new QPushButton("Circulation");
    
    sidebarLayout->addWidget(btnDashboard);
    sidebarLayout->addWidget(btnBooks);
    sidebarLayout->addWidget(btnMembers);
    sidebarLayout->addWidget(btnCirculation);
    sidebarLayout->addStretch();
    
    // Sidebar Styling
    btnDashboard->setMinimumHeight(40);
    btnBooks->setMinimumHeight(40);
    btnMembers->setMinimumHeight(40);
    btnCirculation->setMinimumHeight(40);

    // Stacked Widget
    m_stackedWidget = new QStackedWidget();
    m_stackedWidget->addWidget(createDashboardPage());   // 0
    m_stackedWidget->addWidget(createBookPage());        // 1
    m_stackedWidget->addWidget(createMemberPage());      // 2
    m_stackedWidget->addWidget(createCirculationPage()); // 3

    mainLayout->addLayout(sidebarLayout, 1);
    mainLayout->addWidget(m_stackedWidget, 4);

    // Connect interactions
    connect(btnDashboard, &QPushButton::clicked, [this](){ switchView(0); });
    connect(btnBooks, &QPushButton::clicked, [this](){ switchView(1); });
    connect(btnMembers, &QPushButton::clicked, [this](){ switchView(2); });
    connect(btnCirculation, &QPushButton::clicked, [this](){ switchView(3); });
}

void MainWindow::switchView(int index) {
    m_stackedWidget->setCurrentIndex(index);
    if (index == 1) refreshBooks();
    if (index == 2) refreshMembers();
    if (index == 3) refreshTransactions();
}

QWidget* MainWindow::createDashboardPage() {
    QWidget *page = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(page);
    QLabel *label = new QLabel("Welcome to the Library Management System");
    label->setAlignment(Qt::AlignCenter);
    QFont font = label->font();
    font.setPointSize(20);
    label->setFont(font);
    layout->addWidget(label);
    return page;
}

QWidget* MainWindow::createBookPage() {
    QWidget *page = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(page);
    
    QHBoxLayout *topLayout = new QHBoxLayout();
    QPushButton *addBtn = new QPushButton("Add Book");
    QPushButton *delBtn = new QPushButton("Delete Selected");
    topLayout->addWidget(addBtn);
    topLayout->addWidget(delBtn);
    topLayout->addStretch();

    m_bookModel = new QStandardItemModel(0, 6, this);
    m_bookModel->setHorizontalHeaderLabels({"ID", "Title", "Author", "ISBN", "Publisher", "Qty", "Avail"});
    
    m_bookTable = new QTableView();
    m_bookTable->setModel(m_bookModel);
    m_bookTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_bookTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    layout->addLayout(topLayout);
    layout->addWidget(m_bookTable);

    connect(addBtn, &QPushButton::clicked, this, &MainWindow::onAddBook);
    connect(delBtn, &QPushButton::clicked, this, &MainWindow::onDeleteBook);

    return page;
}

QWidget* MainWindow::createMemberPage() {
    QWidget *page = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(page);

    QHBoxLayout *topLayout = new QHBoxLayout();
    QPushButton *addBtn = new QPushButton("Add Member");
    QPushButton *delBtn = new QPushButton("Delete Selected");
    topLayout->addWidget(addBtn);
    topLayout->addWidget(delBtn);
    topLayout->addStretch();

    m_memberModel = new QStandardItemModel(0, 5, this);
    m_memberModel->setHorizontalHeaderLabels({"ID", "Name", "Email", "Phone", "Joined"});

    m_memberTable = new QTableView();
    m_memberTable->setModel(m_memberModel);
    m_memberTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_memberTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    layout->addLayout(topLayout);
    layout->addWidget(m_memberTable);

    connect(addBtn, &QPushButton::clicked, this, &MainWindow::onAddMember);
    connect(delBtn, &QPushButton::clicked, this, &MainWindow::onDeleteMember);

    return page;
}

QWidget* MainWindow::createCirculationPage() {
    QWidget *page = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(page);

    QHBoxLayout *topLayout = new QHBoxLayout();
    QPushButton *issueBtn = new QPushButton("Issue Book");
    QPushButton *returnBtn = new QPushButton("Return Book");
    topLayout->addWidget(issueBtn);
    topLayout->addWidget(returnBtn);
    topLayout->addStretch();

    m_transactionModel = new QStandardItemModel(0, 8, this);
    m_transactionModel->setHorizontalHeaderLabels({"ID", "Book ID", "Member ID", "Issue Date", "Due Date", "Return Date", "Fine", "Returned?"});

    m_transactionTable = new QTableView();
    m_transactionTable->setModel(m_transactionModel);
    m_transactionTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    
    layout->addLayout(topLayout);
    layout->addWidget(m_transactionTable);

    connect(issueBtn, &QPushButton::clicked, this, &MainWindow::onIssueBook);
    connect(returnBtn, &QPushButton::clicked, this, &MainWindow::onReturnBook);

    return page;
}

void MainWindow::refreshBooks() {
    m_bookModel->removeRows(0, m_bookModel->rowCount());
    auto books = m_controller->getAllBooks();
    for (const auto &b : books) {
        QList<QStandardItem*> row;
        row << new QStandardItem(b.getId());
        row << new QStandardItem(b.getTitle());
        row << new QStandardItem(b.getAuthor());
        row << new QStandardItem(b.getIsbn());
        row << new QStandardItem(b.getPublisher());
        row << new QStandardItem(QString::number(b.getQuantity()));
        row << new QStandardItem(QString::number(b.getAvailable()));
        m_bookModel->appendRow(row);
    }
}

void MainWindow::refreshMembers() {
    m_memberModel->removeRows(0, m_memberModel->rowCount());
    auto members = m_controller->getAllMembers();
    for (const auto &m : members) {
        QList<QStandardItem*> row;
        row << new QStandardItem(m.getId());
        row << new QStandardItem(m.getName());
        row << new QStandardItem(m.getEmail());
        row << new QStandardItem(m.getPhone());
        row << new QStandardItem(m.getMembershipDate().toString(Qt::ISODate));
        m_memberModel->appendRow(row);
    }
}

void MainWindow::refreshTransactions() {
    m_transactionModel->removeRows(0, m_transactionModel->rowCount());
    auto transactions = m_controller->getAllTransactions();
    for (const auto &t : transactions) {
        QList<QStandardItem*> row;
        row << new QStandardItem(t.getId());
        row << new QStandardItem(t.getBookId());
        row << new QStandardItem(t.getMemberId());
        row << new QStandardItem(t.getIssueDate().toString(Qt::ISODate));
        row << new QStandardItem(t.getDueDate().toString(Qt::ISODate));
        row << new QStandardItem(t.getReturnDate().isValid() ? t.getReturnDate().toString(Qt::ISODate) : "-");
        row << new QStandardItem(QString::number(t.getFineAmount()));
        row << new QStandardItem(t.isReturned() ? "Yes" : "No");
        m_transactionModel->appendRow(row);
    }
}

void MainWindow::onAddBook() {
    // Simple Input Dialogs for now (In real app, use a custom Form Dialog)
    QString title = QInputDialog::getText(this, "Add Book", "Title:");
    if (title.isEmpty()) return;
    QString author = QInputDialog::getText(this, "Add Book", "Author:");
    QString isbn = QInputDialog::getText(this, "Add Book", "ISBN:");
    QString publisher = QInputDialog::getText(this, "Add Book", "Publisher:");
    int qty = QInputDialog::getInt(this, "Add Book", "Quantity:", 1);

    m_controller->addBook(title, author, isbn, publisher, qty);
    refreshBooks();
}

void MainWindow::onDeleteBook() {
    QModelIndexList selection = m_bookTable->selectionModel()->selectedRows();
    if (selection.isEmpty()) return;
    QString id = m_bookModel->item(selection.first().row(), 0)->text();
    m_controller->deleteBook(id);
    refreshBooks();
}

void MainWindow::onAddMember() {
    QString name = QInputDialog::getText(this, "Add Member", "Name:");
    if (name.isEmpty()) return;
    QString email = QInputDialog::getText(this, "Add Member", "Email:");
    QString phone = QInputDialog::getText(this, "Add Member", "Phone:");
    
    m_controller->addMember(name, email, phone);
    refreshMembers();
}

void MainWindow::onDeleteMember() {
    QModelIndexList selection = m_memberTable->selectionModel()->selectedRows();
    if (selection.isEmpty()) return;
    QString id = m_memberModel->item(selection.first().row(), 0)->text();
    m_controller->deleteMember(id);
    refreshMembers();
}

void MainWindow::onIssueBook() {
    QString bookId = QInputDialog::getText(this, "Issue Book", "Book ID:");
    if (bookId.isEmpty()) return;
    QString memberId = QInputDialog::getText(this, "Issue Book", "Member ID:");
    if (memberId.isEmpty()) return;

    if (m_controller->issueBook(bookId, memberId)) {
        QMessageBox::information(this, "Success", "Book Issued Successfully!");
        refreshTransactions();
    } else {
        QMessageBox::critical(this, "Failed", "Could not issue book. Check availability or IDs.");
    }
}

void MainWindow::onReturnBook() {
    QString bookId = QInputDialog::getText(this, "Return Book", "Book ID:");
    if (bookId.isEmpty()) return;
    QString memberId = QInputDialog::getText(this, "Return Book", "Member ID:");
    if (memberId.isEmpty()) return;

    if (m_controller->returnBook(bookId, memberId)) {
        QMessageBox::information(this, "Success", "Book Returned Successfully!");
        refreshTransactions();
        refreshBooks(); // Update availability
    } else {
        QMessageBox::critical(this, "Failed", "Could not return book. Check Transaction.");
    }
}
