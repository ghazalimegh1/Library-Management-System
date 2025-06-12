#ifndef STUDENT_H
#define STUDENT_H
#include "user.h"

class Student: public User
{
private:
    int year;
    int group;
public:
    Student(int,const QString&,const QString&,const QString&,int,int);
    int get_year() const;
    int get_group() const;
    void set_year(int);
    void set_group(int);
    QString what_is_role() const override;
    QJsonObject toJson() const override;
    bool saveToFile(const QString &filename);
    static QList<Student> loadAll(const QString &filename);
    Student* clone() const override {
        return new Student(*this);
    }
};

#endif // STUDENT_H
