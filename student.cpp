#include "student.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>


Student::Student(int id,const QString& username,const QString& email,const QString& password,int year,int group):User(id,username,email,password){
    set_year(year);
    set_group(group);
}

QString Student::what_is_role() const {
    return "Student";
}


int Student::get_year() const {
    return year;
}

int Student::get_group() const{
    return group;
}

void Student::set_group(int group){
    this->group = (group > 0 && group < 13) ? group : 1;
}

void Student::set_year(int year) {
    this->year = (year > 0 && year < 6) ? year : 0;
}

QJsonObject Student::toJson() const {
    QJsonObject obj = User::toJson();
    obj["type"] = "Student";
    obj["year"] = year;
    obj["group"] = group;
    return obj;
}



bool Student::saveToFile(const QString &filename) {
    QFile file(filename);
    QJsonObject root;

    // Read existing data
    if (file.open(QIODevice::ReadOnly)) {
        root = QJsonDocument::fromJson(file.readAll()).object();
        file.close();
    }

    QJsonArray students = root["students"].toArray();
    students.append(this->toJson());
    root["students"] = students;

    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(root).toJson());
        file.close();
        return true;
    }
    return false;
}

QList<Student> Student::loadAll(const QString &filename) {
    QList<Student> list;
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly)) return list;
    QJsonObject root = QJsonDocument::fromJson(file.readAll()).object();
    file.close();

    QJsonArray students = root["students"].toArray();
    for (const QJsonValue &val : students) {
        Student s(0, "", "", "", 0, 0);
        s.fromJson(val.toObject());
        list.append(s);
    }
    return list;
}
