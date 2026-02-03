#ifndef MEMBER_H
#define MEMBER_H

#include <QString>
#include <QJsonObject>
#include <QDate>

class Member {
public:
    Member();
    Member(const QString& id, const QString& name, const QString& email, const QString& phone);

    QString getId() const;
    QString getName() const;
    QString getEmail() const;
    QString getPhone() const;
    QDate getMembershipDate() const;

    void setName(const QString& name);
    void setEmail(const QString& email);
    void setPhone(const QString& phone);

    QJsonObject toJson() const;
    static Member fromJson(const QJsonObject& json);

private:
    QString m_id;
    QString m_name;
    QString m_email;
    QString m_phone;
    QDate m_membershipDate;
};

#endif // MEMBER_H
