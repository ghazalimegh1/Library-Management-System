#include "library.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>



Library::Library() {}

Library::~Library() {
    clear();
}

void Library::clear() {
    for (User* user : users) delete user;
    for (Resource* res : resources) delete res;
    for (Loan* loan : loans) delete loan;
    for (Reservation* resv : reservations) delete resv;
    for(Notification* notif: notifications) delete notif;

    users.clear();
    resources.clear();
    loans.clear();
    reservations.clear();
    notifications.clear();
}

bool Library::saveToJson(const QString& filename) const {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) return false;

    QJsonObject root;

    QJsonArray usersArray;
    for (const User* user : users)
        usersArray.append(user->toJson());
    root["users"] = usersArray;

    QJsonArray resourcesArray;
    for (const Resource* res : resources)
        resourcesArray.append(res->toJson());
    root["resources"] = resourcesArray;

    QJsonArray loansArray;
    for (const Loan* loan : loans)
        loansArray.append(loan->toJson());
    root["loans"] = loansArray;

    QJsonArray reservationsArray;
    for (const Reservation* resv : reservations)
        reservationsArray.append(resv->toJson());
    root["reservations"] = reservationsArray;

    QJsonArray notificationArray;
    for (const Notification* notif : notifications)
        notificationArray.append(notif->toJson());
    root["notifications"] = notificationArray;

    QJsonDocument doc(root);
    file.write(doc.toJson());
    file.close();
    return true;
}

bool Library::loadFromJson(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "❌ Cannot open file:" << filename;
        return false;
    }

    QByteArray data = file.readAll();
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(data, &error);

    if (error.error != QJsonParseError::NoError || !doc.isObject()) {
        qDebug() << "❌ JSON parse error:" << error.errorString();
        return false;
    }

    clear();
    QJsonObject root = doc.object();

    QJsonArray usersArray = root["users"].toArray();


    for (const QJsonValue& val : usersArray) {
        QJsonObject userObj = val.toObject();

        User* user = User::fromJson(userObj);
        if (user) {
            users.append(user);

        } else {
            qDebug() << "error appending user";
        }
    }



    QJsonArray resourcesArray = root["resources"].toArray();

    for (const QJsonValue& val : resourcesArray){
        QJsonObject resObj = val.toObject();


        Resource* res = Resource::fromJson(resObj);

        if(res){
            resources.append(res);

        } else {
            qDebug() << "error appending resource";
        }



    }



    QJsonArray reservationsArray = root["reservations"].toArray();
    for (const QJsonValue& val : reservationsArray) {
        Reservation* resv = Reservation::fromJsonStatic(val.toObject());
        if (resv) {

            resv->resolvePointers(resources, users);
            reservations.append(resv);


        } else {
            qDebug() << "Failed to load a reservation.";
        }
    }

    QJsonArray loansArray = root["loans"].toArray();
    for (const QJsonValue& val : loansArray) {

        Loan* loan = Loan::fromJsonStatic(val.toObject());
        if (loan) {
            loan->resolvePointers(resources, users);
            loans.append(loan);

        } else {
            qDebug() << "⚠️ Failed to load a loan.";
        }
    }

    QJsonArray notificationsArray = root["notifications"].toArray();
    for (const QJsonValue& val : notificationsArray) {
        Notification* notif = Notification::fromJsonStatic(val.toObject());
        if (notif) {

            notif->resolvePointers(users);
            notifications.append(notif);
        } else {
            qDebug() << "Failed to load a notification.";
        }
    }

    return true;
}



const QVector<User*>& Library::getUsers() const {
    return users;
}

const QVector<Resource*>& Library::getResources() const {
    return resources;
}

const QVector<Loan*>& Library::getLoans() const {
    return loans;
}

const QVector<Reservation*>& Library::getReservations() const {
    return reservations;
}

const QVector<Notification*>& Library::getNotifications() const{
    return notifications;
}
Resource* loadResourceByIdFromComplexFile(const QString& filename, int target_res_id) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Could not open JSON file: %s", qUtf8Printable(filename));
        return nullptr;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);
    if (parseError.error != QJsonParseError::NoError || !doc.isObject()) {
        qWarning("Failed to parse JSON: %s", qUtf8Printable(parseError.errorString()));
        return nullptr;
    }

    QJsonObject rootObj = doc.object();

    if (!rootObj.contains("resources") || !rootObj["resources"].isArray()) {
        qWarning("No 'resources' array found in JSON");
        return nullptr;
    }

    QJsonArray resourcesArray = rootObj["resources"].toArray();

    for (const QJsonValue& val : resourcesArray) {
        if (!val.isObject()) continue;

        QJsonObject resObj = val.toObject();
        int res_id = resObj["res_id"].toInt(-1);

        if (res_id == target_res_id) {

            Resource* resource = Resource::fromJson(resObj);

            if (!resource) {
                qWarning("Failed to deserialize resource with id %d", target_res_id);
            }

            return resource;  // caller takes ownership
        }
    }

    qWarning("Resource with id %d not found in file: %s", target_res_id, qUtf8Printable(filename));
    return nullptr;
}


User* loadUserByIdFromComplexFile(const QString& filename, int target_user_id) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Could not open JSON file:" << filename;
        return nullptr;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isObject()) {
        qWarning() << "JSON root is not an object in file:" << filename;
        return nullptr;
    }

    QJsonObject rootObj = doc.object();

    if (!rootObj.contains("users") || !rootObj["users"].isArray()) {
        qWarning() << "No 'users' array found in JSON file:" << filename;
        return nullptr;
    }

    QJsonArray usersArray = rootObj["users"].toArray();

    for (const QJsonValue& val : usersArray) {
        if (!val.isObject()) continue;

        QJsonObject userObj = val.toObject();

        if (!userObj.contains("id")) {
            qWarning() << "User entry missing 'id' field, skipping.";
            continue;
        }

        int id = userObj["id"].toInt(-1);
        if (id == target_user_id) {

            User* user = User::fromJson(userObj);
            if (!user) {
                qWarning() << "User::fromJson returned nullptr for user ID:" << id;
            }
            return user;
        }
    }

    qWarning() << "User with ID" << target_user_id << "not found in file:" << filename;
    return nullptr;
}

User* Library::findUserByCredentialAndPassword(const QString& credential, const QString& password) const{
    for(User* user: users){
        if(user->get_password() ==password && (user->get_email() == credential || user->get_username()==credential || user->get_ID()==credential.toInt())){
            return user;
        }
    }
    return nullptr;
}


void Library::addNotification(Notification* n) {
    notifications.append(n);
}

void Library::addLoan(Loan* loan){
    loans.append(loan);
}


void Library::removeReservation(Reservation * reservation){
    this->reservations.erase(
        std::remove(this->reservations.begin(), this->reservations.end(), reservation),
        this->reservations.end()
        );
}

void Library::removeLoan(Loan* loan){
    this->loans.erase(std::remove(this->loans.begin(),this->loans.end(),loan),this->loans.end());
}

void Library::removeResource(Resource * res){
    this->resources.erase(std::remove(this->resources.begin(),this->resources.end(),res),this->resources.end());
}

void Library::addResource(Resource * res){
    resources.append(res);
}

void Library::addUser(User* user){
    users.append(user);
}

void Library::removeUser(User * user){
    this->users.erase(std::remove(this->users.begin(),this->users.end(),user),this->users.end());
}
