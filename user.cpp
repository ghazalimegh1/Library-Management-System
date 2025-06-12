#include "user.h"
#include "student.h"
#include "admin.h"
#include <QMessageBox>

User::User(int id,const QString& username,const QString& email,const QString& password) {
    set_ID(id);
    set_Email(email);
    set_Username(username);
    set_Password(password);
}

User::User(const User* other)
    : ID(other->ID),
    username(other->username),
    email(other->email),
    password(other->password),
    borrowed_resources(other->borrowed_resources)
{
}


int User::get_ID() const {
    return ID;
}

QVector<Resource*> User::get_borrowed_resources() const{
    return borrowed_resources;
}

QString User::get_email() const{
    return email;
}

QString User::get_password() const{
    return password;
}

QString User::get_username() const {
    return username;
}

void User::set_ID(int id){
    if(id > 0){
        this->ID = id;
    }
}

void User::set_Username(const QString& username){
    this->username = username;
}

void User::set_Email(const QString& email){
    this->email = email;
}

void User::set_Password(const QString& password){
    this->password = password;
}



void User::borrow(Resource& res){
    if(!res.is_available()){
        QMessageBox::warning(nullptr,"failed borrow","This book is not available at this time, You can reserve it for another time");

    }
    else{
        borrowed_resources.append(&res);
        res.set_availability(false);
    }
}

void User::return_resource(const Resource& res){

}

void User::reserve(const Resource& res){
    if(!res.is_available()){

    }
}

QJsonObject User::toJson() const {
    QJsonObject obj;
    obj["id"] = ID;
    obj["name"] = username;
    obj["email"] = email;
    obj["password"] = password;
    obj["type"] = "User";
    return obj;
}

User* User::fromJson(const QJsonObject& obj) {
    QString type = obj["type"].toString();

    if (type == "Student") {

        return new Student(
            obj["id"].toInt(),
            obj["name"].toString(),
            obj["email"].toString(),
            obj["password"].toString(),
            obj["year"].toInt(),
            obj["group"].toInt()
            );
    }

    if (type == "Admin") {
        return new Admin(
            obj["id"].toInt(),
            obj["name"].toString(),
            obj["email"].toString(),
            obj["password"].toString()
            );
    }


}
