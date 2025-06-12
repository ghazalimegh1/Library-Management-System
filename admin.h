#ifndef ADMIN_H
#define ADMIN_H
#include "user.h"
#include <QJsonObject>
#include <QString>
#include <QList>

class Admin: public User
{
public:
    Admin(int,const QString&,const QString&,const QString&);
    QString what_is_role() const override;
    void addResource();
    void removeResource();
    void editResource();
    QJsonObject toJson() const override;
    bool saveToFile(const QString &filename);
    static QList<Admin> loadAll(const QString &filename);
    Admin* clone() const override {
        return new Admin(*this);
    }
};

#endif // ADMIN_H
