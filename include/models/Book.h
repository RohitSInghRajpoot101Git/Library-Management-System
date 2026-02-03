#ifndef BOOK_H
#define BOOK_H

#include <QString>
#include <QJsonObject>

class Book {
public:
    Book();
    Book(const QString& id, const QString& title, const QString& author, const QString& isbn, const QString& publisher, int quantity);

    QString getId() const;
    QString getTitle() const;
    QString getAuthor() const;
    QString getIsbn() const;
    QString getPublisher() const;
    int getQuantity() const;
    int getAvailable() const;

    void setTitle(const QString& title);
    void setAuthor(const QString& author);
    void setIsbn(const QString& isbn);
    void setPublisher(const QString& publisher);
    void setQuantity(int quantity);
    
    // Decrement available count
    bool issueOne();
    // Increment available count
    void returnOne();

    QJsonObject toJson() const;
    static Book fromJson(const QJsonObject& json);

private:
    QString m_id;
    QString m_title;
    QString m_author;
    QString m_isbn;
    QString m_publisher;
    int m_quantity;
    int m_available;
};

#endif // BOOK_H
