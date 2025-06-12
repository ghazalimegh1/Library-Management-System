#include "resource.h"
#include "book.h"
#include "article.h"
#include "digital_content.h"
#include "thesis.h"
#include <QJsonArray>
int Resource::id = 500;
Resource::Resource(const QString& title, const QString& author,const QString& category,const QDate& date_of_publication, bool a):availability(a),date_of_publication(date_of_publication),title(title),category(category),author(author),res_id(++id) {

}

Resource::Resource(const Resource* other)
    : res_id(other->res_id),
    title(other->title),
    availability(other->availability),
    category(other->category),
    author(other->author),
    date_of_publication(other->date_of_publication),
    user_reserved(other->user_reserved)
{

}



int Resource::get_res_id() const{
    return res_id;
}


QString Resource::get_title() const{
    return title;
}

QString Resource::get_category() const{
    return category;
}

bool Resource::is_available() const{
    return availability;
}

QString Resource::get_author() const{
    return author;
}

const QDate& Resource::get_date_of_publication() const{
    return date_of_publication;
}

const QVector<User*>& Resource::get_user_reserved() const{
    return user_reserved;
}

void Resource::set_res_id(int res_id){
    this->res_id = res_id > 0 ? res_id : 0;
}

void Resource::set_title(const QString& title){
    this->title = title;
}

void Resource::set_author(const QString& author){
    this->author = author;
}

void Resource::set_date_of_publication(const QDate& date_of_publication){
    this->date_of_publication = date_of_publication;
}

void Resource::set_availability(bool availability){
    this->availability = availability;
}

void Resource::add_reserving_user(User *user){
    user_reserved.append(user);

}

void Resource::remove_reserving_user(User* user){
    user_reserved.erase(std::remove(user_reserved.begin(),user_reserved.end(),user),user_reserved.end());
}

QJsonObject Resource::toJson() const {
    QJsonObject obj;
    obj["res_id"] = res_id;
    obj["title"] = title;
    obj["availability"] = availability;
    obj["category"] = category;
    obj["author"] = author;
    obj["date_of_publication"] = date_of_publication.toString(Qt::ISODate);

    QJsonArray reservedUserIds;
    for (const User* user : user_reserved) {
        if (user)
            reservedUserIds.append(user->get_ID());
    }
    obj["user_reserved"] = reservedUserIds;


    return obj;
}





Resource* Resource::fromJson(const QJsonObject& obj) {
    if (!obj.contains("resource_type") || !obj["resource_type"].isString())
        return nullptr;

    QString type = obj["resource_type"].toString();

    if (type == "Book")
        return Book::fromJson(obj);
    else if (type == "Digital Content")
        return Digital_Content::fromJson(obj);
    else if (type == "Thesis")

        return Thesis::fromJson(obj);
    else if (type == "Article")
        return Article::fromJson(obj);
    else
        return nullptr;
}

User* Resource::next_borrower(){
    User* user = this->user_reserved.first();
    this->user_reserved.removeFirst();

    return user;
}

void Resource::set_category(const QString& c){
    category = c;
}

