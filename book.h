#ifndef BOOK_H
#define BOOK_H
#include "resource.h"
#include <QJsonObject>

class Book: public Resource
{
private:
    QString subject;
public:
    Book(const QString&,const QString&,const QString&,const QDate&,bool,const QString&);
    ~Book();
    Book* clone() const override {
        return new Book(*this);
    }
    QString get_subject() const;
    void set_subject(const QString&);
    QString resource_type() const override;
    QJsonObject toJson() const override;
    static Book* fromJson(const QJsonObject& obj);
};

#endif // BOOK_H
