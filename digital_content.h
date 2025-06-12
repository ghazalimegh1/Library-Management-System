#ifndef DIGITAL_CONTENT_H
#define DIGITAL_CONTENT_H
#include "resource.h"
#include <QJsonObject>

class Digital_Content: public Resource
{
private:
    QString subject;
public:
    Digital_Content(const QString&,const QString&,const QString&,const QDate&,bool,const QString&);
    ~Digital_Content();
    Digital_Content* clone() const override {
        return new Digital_Content(*this);
    }
    QString get_subject() const;
    void set_subject(const QString&);
    QString resource_type() const override;
    QJsonObject toJson() const override;
    static Digital_Content* fromJson(const QJsonObject& obj);
};

#endif // DIGITAL_CONTENT_H
