#include "core/DataManager.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>

DataManager::DataManager(const QString& dataDir) : m_dataDir(dataDir) {
    loadData();
}

bool DataManager::loadData() {
    bool b = loadBooks();
    bool m = loadMembers();
    bool t = loadTransactions();
    return b && m && t;
}

bool DataManager::saveData() {
    bool b = saveBooks();
    bool m = saveMembers();
    bool t = saveTransactions();
    return b && m && t;
}

// --- Books ---
QList<Book> DataManager::getAllBooks() const {
    return m_books.values();
}

void DataManager::addBook(const Book& book) {
    m_books.insert(book.getId(), book);
    saveBooks();
}

void DataManager::updateBook(const Book& book) {
    if (m_books.contains(book.getId())) {
        m_books[book.getId()] = book;
        saveBooks();
    }
}

void DataManager::deleteBook(const QString& id) {
    if (m_books.remove(id) > 0) {
        saveBooks();
    }
}

Book DataManager::getBook(const QString& id) const {
    return m_books.value(id);
}

// --- Members ---
QList<Member> DataManager::getAllMembers() const {
    return m_members.values();
}

void DataManager::addMember(const Member& member) {
    m_members.insert(member.getId(), member);
    saveMembers();
}

void DataManager::updateMember(const Member& member) {
    if (m_members.contains(member.getId())) {
        m_members[member.getId()] = member;
        saveMembers();
    }
}

void DataManager::deleteMember(const QString& id) {
    if (m_members.remove(id) > 0) {
        saveMembers();
    }
}

Member DataManager::getMember(const QString& id) const {
    return m_members.value(id);
}

// --- Transactions ---
QList<Transaction> DataManager::getAllTransactions() const {
    return m_transactions.values();
}

void DataManager::addTransaction(const Transaction& transaction) {
    m_transactions.insert(transaction.getId(), transaction);
    saveTransactions();
}

void DataManager::updateTransaction(const Transaction& transaction) {
    if (m_transactions.contains(transaction.getId())) {
        m_transactions[transaction.getId()] = transaction;
        saveTransactions();
    }
}

// --- Persistence Helpers ---

bool DataManager::loadBooks() {
    QFile file(m_dataDir + "/books.json");
    if (!file.open(QIODevice::ReadOnly)) return false;
    
    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray array = doc.array();

    m_books.clear();
    for (const auto& val : array) {
        Book b = Book::fromJson(val.toObject());
        m_books.insert(b.getId(), b);
    }
    return true;
}

bool DataManager::saveBooks() {
    QFile file(m_dataDir + "/books.json");
    if (!file.open(QIODevice::WriteOnly)) return false;

    QJsonArray array;
    for (const auto& b : m_books) {
        array.append(b.toJson());
    }

    QJsonDocument doc(array);
    file.write(doc.toJson());
    return true;
}

bool DataManager::loadMembers() {
    QFile file(m_dataDir + "/members.json");
    if (!file.open(QIODevice::ReadOnly)) return false;
    
    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray array = doc.array();

    m_members.clear();
    for (const auto& val : array) {
        Member m = Member::fromJson(val.toObject());
        m_members.insert(m.getId(), m);
    }
    return true;
}

bool DataManager::saveMembers() {
    QFile file(m_dataDir + "/members.json");
    if (!file.open(QIODevice::WriteOnly)) return false;

    QJsonArray array;
    for (const auto& m : m_members) {
        array.append(m.toJson());
    }

    QJsonDocument doc(array);
    file.write(doc.toJson());
    return true;
}

bool DataManager::loadTransactions() {
    QFile file(m_dataDir + "/transactions.json");
    if (!file.open(QIODevice::ReadOnly)) return false;
    
    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray array = doc.array();

    m_transactions.clear();
    for (const auto& val : array) {
        Transaction t = Transaction::fromJson(val.toObject());
        m_transactions.insert(t.getId(), t);
    }
    return true;
}

bool DataManager::saveTransactions() {
    QFile file(m_dataDir + "/transactions.json");
    if (!file.open(QIODevice::WriteOnly)) return false;

    QJsonArray array;
    for (const auto& t : m_transactions) {
        array.append(t.toJson());
    }

    QJsonDocument doc(array);
    file.write(doc.toJson());
    return true;
}
