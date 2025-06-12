#ifndef THESIS_H
#define THESIS_H
#include "resource.h"
#include <QJsonObject>

class Thesis: public Resource
{
private:
    QString subject;
    QString university;
public:
     Thesis(const QString&, const QString&, const QString&, const QDate&, bool, const QString&, const QString&);
    ~Thesis();
    Thesis* clone() const override {
        return new Thesis(*this);
    }
    QString get_subject() const;
    QString get_university() const;
    void set_subject(const QString&);
    void set_university(const QString&);
    QString resource_type() const override;
    QJsonObject toJson() const override;
    static Thesis* fromJson(const QJsonObject& obj);
};

#endif // THESIS_H
