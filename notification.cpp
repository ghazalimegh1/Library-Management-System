#include "notification.h"
#include "library.h"

int Notification::number_of_notification = 0;

Notification::Notification(QString& c,const User* user):notification_content(c),user(user){
    set_notification_id(++number_of_notification);
}
Notification::~Notification(){}

int Notification::get_notification_id() const{
    return notification_id;
}
QString Notification::get_notification_content() const{
    return notification_content;
}


const User* Notification::get_user() const{
    return user;
}

void Notification::set_notification_id(int id){
    this->notification_id = id > 0 ? id : 0;
}
void Notification::set_notification_content(QString& c){
    this->notification_content = c;
}

QJsonObject Notification::toJson() const{
    QJsonObject obj;
    obj["notif_id"] = notification_id;
    obj["content"] = notification_content;
    obj["user_id"] = user ? user->get_ID() : -1;
    return obj;
}


Notification* Notification::fromJsonStatic(const QJsonObject& json){
    int id = json["notif_id"].toInt();
    int userId = json["user_id"].toInt();
    QString content = json["content"].toString();


    User* user = loadUserByIdFromComplexFile("C:/Users/HP/Documents/LBMS/build/Desktop_Qt_6_9_1_MinGW_64_bit-Debug/data.json", userId);


    if (!user) {
        qDebug() << "Failed to load Reservation: user not found.";
        return nullptr;
    }

    Notification* notification = new Notification(content,user);
    notification->set_notification_id(id);

    return notification;

}


void Notification::resolvePointers(const QList<User*>& users){
    int target_user_id = user ? user->get_ID() : -1;

    user = nullptr;
    for (User* u : users) {
        if (u && u->get_ID() == target_user_id) {
            user = u;
            break;
        }
    }

}
