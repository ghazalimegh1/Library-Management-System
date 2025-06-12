#include "book.h"
#include "library.h"

Book::Book(const QString& title,const QString& author,const QString& category,const QDate& date_of_publication,bool a,const QString& subject):Resource(title,category,author,date_of_publication,a),subject(subject) {}

Book::~Book(){}

QString Book::get_subject() const {
    return subject;
}

void Book::set_subject(const QString & subject){
    this->subject = subject;
}

QString Book::resource_type() const{
    return "Book";
}

QJsonObject Book::toJson() const {
    QJsonObject obj = Resource::toJson();
    obj["subject"] = subject;
    obj["resource_type"] = resource_type();
    return obj;
}

Book* Book::fromJson(const QJsonObject& obj) {
    int res_id = obj["res_id"].toInt();
    QString title = obj["title"].toString();
    QString category = obj["category"].toString();
    QString author = obj["author"].toString();
    QDate date_of_publication = QDate::fromString(obj["date_of_publication"].toString(), Qt::ISODate);
    QString subject = obj["subject"].toString();
    bool availability = obj["availability"].toBool();

    Book *b = new Book(title, category, author, date_of_publication,availability , subject);
    b->set_res_id(res_id);
    QJsonArray reservingArray = obj["user_reserved"].toArray();
    for (const QJsonValue& val : reservingArray) {
        int userId = val.toInt();
        b->add_reserving_user(loadUserByIdFromComplexFile("C:/Users/HP/Documents/LBMS/build/Desktop_Qt_6_9_1_MinGW_64_bit-Debug/data.json",userId));
    }

    return b;
}



