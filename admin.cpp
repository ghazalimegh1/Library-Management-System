#include "admin.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>


Admin::Admin(int id,const QString& username,const QString& email,const QString& password):User(id,username,email,password) {}

QString Admin::what_is_role() const {
    return "Admin";
}

void Admin::addResource(){}

void Admin::editResource(){}

void Admin::removeResource(){}

QJsonObject Admin::toJson() const {
    QJsonObject obj = User::toJson();
    obj["type"] = "Admin";
    return obj;
}



bool Admin::saveToFile(const QString &filename) {
    QFile file(filename);
    QJsonObject root;

    // Load current data
    if (file.open(QIODevice::ReadOnly)) {
        root = QJsonDocument::fromJson(file.readAll()).object();
        file.close();
    }

    QJsonArray admins = root["admins"].toArray();
    admins.append(this->toJson());
    root["admins"] = admins;

    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(root).toJson());
        file.close();
        return true;
    }
    return false;
}

QList<Admin> Admin::loadAll(const QString &filename) {
    QList<Admin> list;
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly)) return list;

    QJsonObject root = QJsonDocument::fromJson(file.readAll()).object();
    file.close();

    QJsonArray admins = root["admins"].toArray();
    for (const QJsonValue &val : admins) {
        Admin a(0, "", "", "");
        a.fromJson(val.toObject());
        list.append(a);
    }
    return list;
}
