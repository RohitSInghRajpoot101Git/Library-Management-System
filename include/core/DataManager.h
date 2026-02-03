#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QString>
#include <QList>
#include <QMap>
#include "models/Book.h"
#include "models/Member.h"
#include "models/Transaction.h"

class DataManager {
public:
    DataManager(const QString& dataDir = ".");

    bool loadData();
    bool saveData();

    // Books
    QList<Book> getAllBooks() const;
    void addBook(const Book& book);
    void updateBook(const Book& book);
    void deleteBook(const QString& id);
    Book getBook(const QString& id) const;

    // Members
    QList<Member> getAllMembers() const;
    void addMember(const Member& member);
    void updateMember(const Member& member);
    void deleteMember(const QString& id);
    Member getMember(const QString& id) const;

    // Transactions
    QList<Transaction> getAllTransactions() const;
    void addTransaction(const Transaction& transaction);
    void updateTransaction(const Transaction& transaction);

private:
    QString m_dataDir;
    QMap<QString, Book> m_books;
    QMap<QString, Member> m_members;
    QMap<QString, Transaction> m_transactions;

    bool loadBooks();
    bool saveBooks();
    bool loadMembers();
    bool saveMembers();
    bool loadTransactions();
    bool saveTransactions();
};

#endif // DATAMANAGER_H
