#include "thesis.h"
#include "library.h"
Thesis::Thesis(const QString& title,const QString& category,const QString& author,const QDate& date_of_publication,bool a,const QString& subject,const QString& university):Resource(title,category,author,date_of_publication,a),subject(subject),university(university) {}

Thesis::~Thesis(){}

QString Thesis::get_subject() const {
    return subject;
}

QString Thesis::get_university() const{
    return university;
}



void Thesis::set_subject(const QString& subject){
    this->subject = subject;
}

void Thesis::set_university(const QString& university){
    this->university = university;
}

QString Thesis::resource_type() const{
    return "Thesis";
}

QJsonObject Thesis::toJson() const {
    QJsonObject obj = Resource::toJson();
    obj["subject"] = subject;
    obj["university"] = university;
    obj["resource_type"] = resource_type();
    return obj;
}

Thesis* Thesis::fromJson(const QJsonObject& obj) {
    if (!obj.contains("title") || !obj.contains("category") || !obj.contains("author") ||
        !obj.contains("date_of_publication") || !obj.contains("subject") || !obj.contains("university") ||
        !obj.contains("availability"))
    {
        qDebug() << "[Thesis::fromJson] Missing required fields.";
        return nullptr;
    }

    int res_id = obj["res_id"].toInt();
    QString title = obj["title"].toString();
    QString category = obj["category"].toString();
    QString author = obj["author"].toString();
    QString subject = obj["subject"].toString();
    QString university = obj["university"].toString();
    bool availability = obj["availability"].toBool();

    QDate date_of_publication = QDate::fromString(obj["date_of_publication"].toString(), Qt::ISODate);
    if (!date_of_publication.isValid()) {
        qDebug() << "[Thesis::fromJson] Invalid date format:" << obj["date_of_publication"].toString();
        return nullptr;
    }

    Thesis* th = new Thesis(title, category, author, date_of_publication, availability, subject, university);
    th->set_res_id(res_id);



    if (obj.contains("user_reserved") && obj["user_reserved"].isArray()) {
        QJsonArray reservingArray = obj["user_reserved"].toArray();
        for (const QJsonValue& val : reservingArray) {
            int userId = val.toInt();
            User* user = loadUserByIdFromComplexFile(
                "C:/Users/HP/Documents/LBMS/build/Desktop_Qt_6_9_1_MinGW_64_bit-Debug/data.json", userId);

            if (user) {
                th->add_reserving_user(user);
            } else {
                qDebug() << "[Thesis::fromJson] Warning: Could not load user with ID:" << userId;
            }
        }
    }

    return th;
}

