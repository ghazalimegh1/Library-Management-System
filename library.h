#ifndef LIBRARY_H
#define LIBRARY_H

#include "student.h"
#include "admin.h"
#include "book.h"
#include "thesis.h"
#include "article.h"
#include "digital_content.h"
#include "loan.h"
#include "reservation.h"
#include "notification.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QVector>
#include <QString>
#include "notificationwindow.h"
#include "myreservationwindow.h"

class Loan;
class Reservation;

class Library {
private:
    QVector<User*> users;
    QVector<Resource*> resources;
    QVector<Loan*> loans;
    QVector<Reservation*> reservations;
    QVector<Notification*> notifications;

public:
    Library();
    ~Library();
    friend class Notification;
    // Load & Save
    bool loadFromJson(const QString& filename);
    bool saveToJson(const QString& filename) const;
    void clear();
    const QVector<User*>& getUsers() const;
    const QVector<Resource*>& getResources() const;
    const QVector<Loan*>& getLoans() const;
    const QVector<Reservation*>& getReservations() const;
    const QVector<Notification*>& getNotifications() const;
    User* findUserByCredentialAndPassword(const QString&, const QString&) const;
    void addNotification(Notification*);
    void addLoan(Loan*);
    void addResource(Resource*);
    void addUser(User*);
    void removeUser(User*);
    void removeReservation(Reservation*);
    void removeLoan(Loan*);
    void removeResource(Resource*);
    friend class NotificationWindow;
};

Resource* loadResourceByIdFromComplexFile(const QString& filename, int target_res_id);
User* loadUserByIdFromComplexFile(const QString& filename, int target_user_id);
#endif // LIBRARY_H
