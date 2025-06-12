#include "digital_content.h"
#include "library.h"
Digital_Content::Digital_Content(const QString& title,const QString& category,const QString& author,const QDate& date_of_publication,bool a,const QString& subject):Resource(title,category,author,date_of_publication,a),subject(subject) {}

Digital_Content::~Digital_Content(){}

QString Digital_Content::get_subject() const {
    return subject;
}

void Digital_Content::set_subject(const QString & subject){
    this->subject = subject;
}

QString Digital_Content::resource_type() const{
    return "Digital Content";
}

QJsonObject Digital_Content::toJson() const {
    QJsonObject obj = Resource::toJson();
    obj["subject"] = subject;
    obj["resource_type"] = resource_type();
    return obj;
}

Digital_Content* Digital_Content::fromJson(const QJsonObject& obj) {
    int res_id = obj["res_id"].toInt();
    QString title = obj["title"].toString();
    QString category = obj["category"].toString();
    QString author = obj["author"].toString();
    QDate date_of_publication = QDate::fromString(obj["date_of_publication"].toString(), Qt::ISODate);
    QString subject = obj["subject"].toString();
    bool availability = obj["availability"].toBool();

    Digital_Content *dc = new Digital_Content( title, category, author, date_of_publication,availability , subject);

    dc->set_res_id(res_id);
        QJsonArray reservingArray = obj["user_reserved"].toArray();
    for (const QJsonValue& val : reservingArray) {
        int userId = val.toInt();
        dc->add_reserving_user(loadUserByIdFromComplexFile("C:/Users/HP/Documents/LBMS/build/Desktop_Qt_6_9_1_MinGW_64_bit-Debug/data.json",userId));
    }

    return dc;


}
