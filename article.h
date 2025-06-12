#ifndef ARTICLE_H
#define ARTICLE_H
#include "resource.h"
#include <QJsonObject>

class Article: public Resource
{
private:
    QString subject;
    QString journal;
public:
    Article(const QString&,const QString&,const QString&,const QDate&,bool,const QString&,const QString&);
    ~Article();
    Article* clone() const override {
        return new Article(*this);
    }
    QString get_subject() const;
    QString get_journal() const;
    void set_subject(const QString&);
    void set_journal(const QString&);
    QString resource_type() const override;
    QJsonObject toJson() const override;
    static Article* fromJson(const QJsonObject& obj);
};

#endif // ARTICLE_H
