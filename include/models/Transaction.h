#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QString>
#include <QJsonObject>
#include <QDate>

class Transaction {
public:
    Transaction();
    Transaction(const QString& id, const QString& bookId, const QString& memberId, const QDate& issueDate, int daysToReturn);

    QString getId() const;
    QString getBookId() const;
    QString getMemberId() const;
    QDate getIssueDate() const;
    QDate getDueDate() const;
    QDate getReturnDate() const;
    double getFineAmount() const;
    bool isReturned() const;

    void returnBook(const QDate& returnDate, double finePerDay);

    QJsonObject toJson() const;
    static Transaction fromJson(const QJsonObject& json);

private:
    QString m_id;
    QString m_bookId;
    QString m_memberId;
    QDate m_issueDate;
    QDate m_dueDate;
    QDate m_returnDate;
    double m_fineAmount;
    bool m_isReturned;
};

#endif // TRANSACTION_H
