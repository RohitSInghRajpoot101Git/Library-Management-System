#include "models/Book.h"
#include <QUuid>

Book::Book() : m_quantity(0), m_available(0) {}

Book::Book(const QString& id, const QString& title, const QString& author, const QString& isbn, const QString& publisher, int quantity)
    : m_id(id.isEmpty() ? QUuid::createUuid().toString(QUuid::Id128) : id),
      m_title(title), m_author(author), m_isbn(isbn), m_publisher(publisher), m_quantity(quantity), m_available(quantity)
{
}

QString Book::getId() const { return m_id; }
QString Book::getTitle() const { return m_title; }
QString Book::getAuthor() const { return m_author; }
QString Book::getIsbn() const { return m_isbn; }
QString Book::getPublisher() const { return m_publisher; }
int Book::getQuantity() const { return m_quantity; }
int Book::getAvailable() const { return m_available; }

void Book::setTitle(const QString& title) { m_title = title; }
void Book::setAuthor(const QString& author) { m_author = author; }
void Book::setIsbn(const QString& isbn) { m_isbn = isbn; }
void Book::setPublisher(const QString& publisher) { m_publisher = publisher; }
void Book::setQuantity(int quantity) {
    int diff = quantity - m_quantity;
    m_quantity = quantity;
    m_available += diff;
    if (m_available < 0) m_available = 0; // Safety clamp
}

bool Book::issueOne() {
    if (m_available > 0) {
        m_available--;
        return true;
    }
    return false;
}

void Book::returnOne() {
    if (m_available < m_quantity) {
        m_available++;
    }
}

QJsonObject Book::toJson() const {
    QJsonObject json;
    json["id"] = m_id;
    json["title"] = m_title;
    json["author"] = m_author;
    json["isbn"] = m_isbn;
    json["publisher"] = m_publisher;
    json["quantity"] = m_quantity;
    json["available"] = m_available;
    return json;
}

Book Book::fromJson(const QJsonObject& json) {
    Book book;
    book.m_id = json["id"].toString();
    book.m_title = json["title"].toString();
    book.m_author = json["author"].toString();
    book.m_isbn = json["isbn"].toString();
    book.m_publisher = json["publisher"].toString();
    book.m_quantity = json["quantity"].toInt();
    book.m_available = json["available"].toInt();
    return book;
}
