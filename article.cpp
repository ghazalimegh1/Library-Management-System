#include "article.h"
#include "library.h"

Article::Article(const QString& title,const QString& category,const QString& author,const QDate& date_of_publication,bool a,const QString& subject,const QString& journal):Resource(title,category,author,date_of_publication,a),subject(subject),journal(journal) {}

Article::~Article(){}

QString Article::get_subject() const {
    return subject;
}

QString Article::get_journal() const{
    return journal;
}



void Article::set_subject(const QString& subject){
    this->subject = subject;
}

void Article::set_journal(const QString& journal){
    this->journal = journal;
}

QString Article::resource_type() const{
    return "Article";
}

QJsonObject Article::toJson() const {
    QJsonObject obj = Resource::toJson();
    obj["subject"] = subject;
    obj["journal"] = journal;
    obj["resource_type"] = resource_type();
    return obj;
}

Article* Article::fromJson(const QJsonObject& obj) {
    int res_id = obj["res_id"].toInt();
    QString title = obj["title"].toString();
    QString category = obj["category"].toString();
    QString author = obj["author"].toString();
    QDate date_of_publication = QDate::fromString(obj["date_of_publication"].toString(), Qt::ISODate);
    QString subject = obj["subject"].toString();
    QString journal = obj["journal"].toString();
    bool availability = obj["availability"].toBool();

    Article *a = new Article(title, category, author, date_of_publication,availability , subject,journal);
    a->set_res_id(res_id);
    QJsonArray reservingArray = obj["reserving_users"].toArray();
    for (const QJsonValue& val : reservingArray) {
        int userId = val.toInt();
        a->add_reserving_user(loadUserByIdFromComplexFile("C:/Users/HP/Documents/LBMS/build/Desktop_Qt_6_9_1_MinGW_64_bit-Debug/data.json",userId));
    }

    return a;

}
