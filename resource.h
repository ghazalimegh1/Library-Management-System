#ifndef RESOURCE_H
#define RESOURCE_H
#include <QDate>
#include <QVector>
#include <QJsonObject>
#include "user.h"


class User;

class Resource
{
private:
    int res_id;
    QString title;
    bool availability;
    QString category;
    QString author;
    QDate date_of_publication;
    QVector<User*> user_reserved;
    const int max_users_reserved = 5;
    static int id;

public:
    Resource(const QString&,const QString&,const QString&,const QDate&,bool);
    Resource(const Resource* other);
    virtual Resource* clone() const = 0;
    virtual ~Resource() =  default;
    virtual QString resource_type() const = 0;
    int get_res_id() const;
    QString get_title() const;
    QString get_category() const;
    bool is_available() const;
    QString get_author() const;
    const QDate& get_date_of_publication() const;
    const QVector<User*>& get_user_reserved() const;
    void set_res_id(int);
    void set_title(const QString&);
    void set_author(const QString&);
    void set_date_of_publication(const QDate&);
    void set_category(const QString&);
    void set_availability(bool);
    void add_reserving_user(User*);
    void remove_reserving_user(User*);
    virtual QJsonObject toJson() const;
    static Resource* fromJson(const QJsonObject& obj);
    User* next_borrower();
    static Resource* createFromJson(const QJsonObject&);
};

#endif // RESOURCE_H
