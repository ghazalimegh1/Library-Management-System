#ifndef RESERVATION_H
#define RESERVATION_H

#include "resource.h"
#include "user.h"
#include <QDate>
#include <QJsonObject>
#include <QList>
#include "library.h"

class Library;

class Reservation {
private:
    int reservation_id;
    Resource* resource;
    User* user;
    QDate reservation_date;
    static int number_of_reservations;

public:
    Reservation(Resource*, User*, const QDate& date = QDate::currentDate(),Library* = nullptr);
    ~Reservation();
    int get_reservation_id() const;
    const QDate& get_reservation_date() const;
    Resource* get_resource() const;
    User* get_user() const;
    void set_reservation_id(int);
    void set_reservation_date(const QDate&);
    void notify_user(Library* = nullptr);
    bool is_expired(int expiration_days = 7) const;
    static int get_total_reservations();
    void cancel();
    QJsonObject toJson() const;
    void fromJson(const QJsonObject& obj);
    void resolvePointers(const QList<Resource*>& resources, const QList<User*>& users);
    static Reservation* fromJsonStatic(const QJsonObject& json);
};

#endif // RESERVATION_H
