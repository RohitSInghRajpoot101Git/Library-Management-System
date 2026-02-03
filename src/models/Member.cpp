#include "models/Member.h"
#include <QUuid>

Member::Member() {}

Member::Member(const QString& id, const QString& name, const QString& email, const QString& phone)
    : m_id(id.isEmpty() ? QUuid::createUuid().toString(QUuid::Id128) : id),
      m_name(name), m_email(email), m_phone(phone), m_membershipDate(QDate::currentDate())
{
}

QString Member::getId() const { return m_id; }
QString Member::getName() const { return m_name; }
QString Member::getEmail() const { return m_email; }
QString Member::getPhone() const { return m_phone; }
QDate Member::getMembershipDate() const { return m_membershipDate; }

void Member::setName(const QString& name) { m_name = name; }
void Member::setEmail(const QString& email) { m_email = email; }
void Member::setPhone(const QString& phone) { m_phone = phone; }

QJsonObject Member::toJson() const {
    QJsonObject json;
    json["id"] = m_id;
    json["name"] = m_name;
    json["email"] = m_email;
    json["phone"] = m_phone;
    json["membershipDate"] = m_membershipDate.toString(Qt::ISODate);
    return json;
}

Member Member::fromJson(const QJsonObject& json) {
    Member member;
    member.m_id = json["id"].toString();
    member.m_name = json["name"].toString();
    member.m_email = json["email"].toString();
    member.m_phone = json["phone"].toString();
    member.m_membershipDate = QDate::fromString(json["membershipDate"].toString(), Qt::ISODate);
    return member;
}
