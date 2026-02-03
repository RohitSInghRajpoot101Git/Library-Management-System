#include "core/LibraryController.h"
#include <QDebug>

LibraryController::LibraryController(QObject *parent) 
    : QObject(parent), m_dailyFine(10.0), m_defaultIssueDays(14)
{
}

bool LibraryController::login(const QString& username, const QString& password) {
    // Hardcoded for simplicity as per requirements
    // In real app, hash password and check against file/DB
    return (username == "admin" && password == "admin");
}

// --- Book ---
void LibraryController::addBook(const QString& title, const QString& author, const QString& isbn, const QString& publisher, int quantity) {
    Book b("", title, author, isbn, publisher, quantity);
    m_dataManager.addBook(b);
}

void LibraryController::updateBook(const QString& id, const QString& title, const QString& author, const QString& isbn, const QString& publisher, int quantity) {
    Book b(id, title, author, isbn, publisher, quantity);
    m_dataManager.updateBook(b);
}

void LibraryController::deleteBook(const QString& id) {
    m_dataManager.deleteBook(id);
}

QList<Book> LibraryController::searchBooks(const QString& query) {
    if (query.isEmpty()) return m_dataManager.getAllBooks();
    
    QList<Book> results;
    for (const auto& b : m_dataManager.getAllBooks()) {
        if (b.getTitle().contains(query, Qt::CaseInsensitive) || 
            b.getAuthor().contains(query, Qt::CaseInsensitive) ||
            b.getIsbn().contains(query, Qt::CaseInsensitive)) {
            results.append(b);
        }
    }
    return results;
}

QList<Book> LibraryController::getAllBooks() {
    return m_dataManager.getAllBooks();
}

// --- Member ---
void LibraryController::addMember(const QString& name, const QString& email, const QString& phone) {
    Member m("", name, email, phone);
    m_dataManager.addMember(m);
}

void LibraryController::updateMember(const QString& id, const QString& name, const QString& email, const QString& phone) {
    Member m(id, name, email, phone);
    m_dataManager.updateMember(m);
}

void LibraryController::deleteMember(const QString& id) {
    m_dataManager.deleteMember(id);
}

QList<Member> LibraryController::getAllMembers() {
    return m_dataManager.getAllMembers();
}

// --- Circulation ---
bool LibraryController::issueBook(const QString& bookId, const QString& memberId) {
    Book book = m_dataManager.getBook(bookId);
    if (book.getId().isEmpty()) return false; // Book not found
    if (book.getAvailable() <= 0) return false; // Not available
    
    // Check if member exists
    Member member = m_dataManager.getMember(memberId);
    if (member.getId().isEmpty()) return false;

    // Issue
    if (book.issueOne()) {
        m_dataManager.updateBook(book); // Update quantity
        
        Transaction t("", bookId, memberId, QDate::currentDate(), m_defaultIssueDays);
        m_dataManager.addTransaction(t);
        return true;
    }
    return false;
}

bool LibraryController::returnBook(const QString& bookId, const QString& memberId) {
    // Find active transaction for this book and member
    // In a real app we might return by transaction ID, but here we assume book instance return
    // Simple logic: Find latest non-returned transaction for this book & member
    
    QList<Transaction> transactions = m_dataManager.getAllTransactions();
    QString transactionId;
    Transaction targetTransaction;
    bool found = false;

    // Iterate to find matching active transaction
    for (const auto& t : transactions) {
        if (t.getBookId() == bookId && t.getMemberId() == memberId && !t.isReturned()) {
            targetTransaction = t;
            found = true;
            break; 
        }
    }

    if (!found) return false;

    // Return book
    Book book = m_dataManager.getBook(bookId);
    book.returnOne();
    m_dataManager.updateBook(book);

    // Update transaction
    targetTransaction.returnBook(QDate::currentDate(), m_dailyFine);
    m_dataManager.updateTransaction(targetTransaction);
    
    return true;
}

QList<Transaction> LibraryController::getAllTransactions() {
    return m_dataManager.getAllTransactions();
}
