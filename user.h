#ifndef USER_H
#define USER_H
#include <QString>
#include <QVector>
#include "resource.h"
#include <QJsonObject>
class Resource;
class User
{
private:
    int ID;
    QString username;
    QString email;
    QString password;
    QVector<Resource*> borrowed_resources;

public:
    User(int,const QString&,const QString&,const QString&);
    User(const User* other);
    virtual User* clone() const = 0;
    virtual ~User() = default;
    int get_ID() const;
    QString get_email() const;
    QString get_username() const;
    QString get_password() const;
    void set_ID(int);
    void set_Email(const QString&);
    void set_Password(const QString&);
    void set_Username(const QString&);
    virtual QString what_is_role() const  = 0;
    void borrow(Resource&);
    void return_resource(const Resource&);
    void reserve(const Resource&);
    virtual QJsonObject toJson() const;
    static User* fromJson(const QJsonObject& obj);
    QVector<Resource*> get_borrowed_resources() const;
};

#endif // USER_H
