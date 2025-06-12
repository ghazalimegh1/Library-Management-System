#include "reservation.h"
#include "library.h"
#include "notification.h"

int Reservation::number_of_reservations = 0;

Reservation::Reservation(Resource* resource, User* user, const QDate& date,Library* library)
    : reservation_id(++number_of_reservations),
    resource(resource),
    user(user)
{
    set_reservation_date(date);
    notify_user(library);
}

Reservation::~Reservation() {
    --number_of_reservations;
}

int Reservation::get_reservation_id() const {
    return reservation_id;
}

const QDate& Reservation::get_reservation_date() const {
    return reservation_date;
}

Resource* Reservation::get_resource() const {
    return resource;
}

User* Reservation::get_user() const {
    return user;
}

void Reservation::set_reservation_date(const QDate& reservation_date) {
    this->reservation_date = (reservation_date >= QDate::currentDate()) ? reservation_date : QDate::currentDate();
}

void Reservation::notify_user(Library * library) {
    if(library == nullptr) return;
    if (resource->is_available()) {
        QString content = "Warning: Your  resource  " + resource->get_title() + " is available.";
        Notification* notification = new Notification(content,this->get_user());
        library->addNotification(notification);

    }

}

bool Reservation::is_expired(int expiration_days) const {
    int days_passed = reservation_date.daysTo(QDate::currentDate());
    return days_passed > expiration_days;
}

int Reservation::get_total_reservations() {
    return number_of_reservations;
}

void Reservation::cancel() {

}

QJsonObject Reservation::toJson() const {
    QJsonObject obj;
    obj["reservation_id"] = reservation_id;
    obj["resource_id"] = resource ? resource->get_res_id() : -1;
    obj["user_id"] = user ? user->get_ID() : -1;
    obj["reservation_date"] = reservation_date.toString(Qt::ISODate);
    return obj;
}

void Reservation::fromJson(const QJsonObject& obj) {
    reservation_id = obj["reservation_id"].toInt();
    resource->set_res_id(obj["resource_id"].toInt());
    user->set_ID(obj["user_id"].toInt());
    reservation_date = QDate::fromString(obj["reservation_date"].toString(), Qt::ISODate);
}

void Reservation::resolvePointers(const QList<Resource*>& resources, const QList<User*>& users) {
    int targetResId = resource ? resource->get_res_id() : -1;
    int targetUserId = user ? user->get_ID() : -1;

    resource = nullptr;
    for (Resource* r : resources) {
        if (r && r->get_res_id() == targetResId) {
            resource = r;
            break;
        }
    }

    user = nullptr;
    for (User* u : users) {
        if (u && u->get_ID() == targetUserId) {
            user = u;
            break;
        }
    }
}


void Reservation::set_reservation_id(int id) {
    reservation_id = id;
    if (id > number_of_reservations) {
        number_of_reservations = id;
    }
}

Reservation* Reservation::fromJsonStatic(const QJsonObject& json) {
    int id = json["reservation_id"].toInt();
    int resourceId = json["resource_id"].toInt();
    int userId = json["user_id"].toInt();
    QString dateStr = json["reservation_date"].toString();
    QDate reservationDate = QDate::fromString(dateStr, Qt::ISODate);

    User* user = loadUserByIdFromComplexFile("C:/Users/HP/Documents/LBMS/build/Desktop_Qt_6_9_1_MinGW_64_bit-Debug/data.json", userId);
    Resource* resource = loadResourceByIdFromComplexFile("C:/Users/HP/Documents/LBMS/build/Desktop_Qt_6_9_1_MinGW_64_bit-Debug/data.json", resourceId);

    if (!user || !resource) {
        qDebug() << "Failed to load Reservation: user or resource not found.";
        return nullptr;
    }

    Reservation* reservation = new Reservation(resource, user, reservationDate);
    reservation->set_reservation_id(id);

    return reservation;
}
