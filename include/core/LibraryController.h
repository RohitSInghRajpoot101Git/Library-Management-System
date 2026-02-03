#ifndef LIBRARYCONTROLLER_H
#define LIBRARYCONTROLLER_H

#include <QObject>
#include "core/DataManager.h"

class LibraryController : public QObject {
    Q_OBJECT
public:
    explicit LibraryController(QObject *parent = nullptr);

    // Auth
    bool login(const QString& username, const QString& password);

    // Book Management
    void addBook(const QString& title, const QString& author, const QString& isbn, const QString& publisher, int quantity);
    void updateBook(const QString& id, const QString& title, const QString& author, const QString& isbn, const QString& publisher, int quantity);
    void deleteBook(const QString& id);
    QList<Book> searchBooks(const QString& query);
    QList<Book> getAllBooks();

    // Member Management
    void addMember(const QString& name, const QString& email, const QString& phone);
    void updateMember(const QString& id, const QString& name, const QString& email, const QString& phone);
    void deleteMember(const QString& id);
    QList<Member> getAllMembers();

    // Circulation
    bool issueBook(const QString& bookId, const QString& memberId);
    bool returnBook(const QString& bookId, const QString& memberId);
    QList<Transaction> getAllTransactions();

private:
    DataManager m_dataManager;
    double m_dailyFine; // e.g. 5.0 units per day
    int m_defaultIssueDays; // e.g. 14 days
};

#endif // LIBRARYCONTROLLER_H
