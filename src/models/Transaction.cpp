#include "models/Transaction.h"
#include <QUuid>

Transaction::Transaction() : m_fineAmount(0.0), m_isReturned(false) {}

Transaction::Transaction(const QString& id, const QString& bookId, const QString& memberId, const QDate& issueDate, int daysToReturn)
    : m_id(id.isEmpty() ? QUuid::createUuid().toString(QUuid::Id128) : id),
      m_bookId(bookId), m_memberId(memberId), m_issueDate(issueDate), m_fineAmount(0.0), m_isReturned(false)
{
    m_dueDate = m_issueDate.addDays(daysToReturn);
}

QString Transaction::getId() const { return m_id; }
QString Transaction::getBookId() const { return m_bookId; }
QString Transaction::getMemberId() const { return m_memberId; }
QDate Transaction::getIssueDate() const { return m_issueDate; }
QDate Transaction::getDueDate() const { return m_dueDate; }
QDate Transaction::getReturnDate() const { return m_returnDate; }
double Transaction::getFineAmount() const { return m_fineAmount; }
bool Transaction::isReturned() const { return m_isReturned; }

void Transaction::returnBook(const QDate& returnDate, double finePerDay) {
    if (m_isReturned) return;
    
    m_returnDate = returnDate;
    m_isReturned = true;

    int overdueDays = m_dueDate.daysTo(m_returnDate);
    if (overdueDays > 0) {
        m_fineAmount = overdueDays * finePerDay;
    } else {
        m_fineAmount = 0.0;
    }
}

QJsonObject Transaction::toJson() const {
    QJsonObject json;
    json["id"] = m_id;
    json["bookId"] = m_bookId;
    json["memberId"] = m_memberId;
    json["issueDate"] = m_issueDate.toString(Qt::ISODate);
    json["dueDate"] = m_dueDate.toString(Qt::ISODate);
    if (m_isReturned) {
        json["returnDate"] = m_returnDate.toString(Qt::ISODate);
    }
    json["fineAmount"] = m_fineAmount;
    json["isReturned"] = m_isReturned;
    return json;
}

Transaction Transaction::fromJson(const QJsonObject& json) {
    Transaction t;
    t.m_id = json["id"].toString();
    t.m_bookId = json["bookId"].toString();
    t.m_memberId = json["memberId"].toString();
    t.m_issueDate = QDate::fromString(json["issueDate"].toString(), Qt::ISODate);
    t.m_dueDate = QDate::fromString(json["dueDate"].toString(), Qt::ISODate);
    if (json.contains("returnDate")) {
        t.m_returnDate = QDate::fromString(json["returnDate"].toString(), Qt::ISODate);
    }
    t.m_fineAmount = json["fineAmount"].toDouble();
    t.m_isReturned = json["isReturned"].toBool();
    return t;
}
