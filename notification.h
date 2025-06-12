#ifndef NOTIFICATION_H
#define NOTIFICATION_H
#include "user.h"
class Notification
{
    int notification_id;
    const User* user;
    QString notification_content;
    static int number_of_notification;

public:
    Notification(QString&, const User *);
    ~Notification();
    int get_notification_id() const;
    QString get_notification_content() const;
    const User *get_user() const;
    void set_notification_id(int);
    void set_notification_content(QString&);
    QJsonObject toJson() const;
    static Notification* fromJsonStatic(const QJsonObject& json);
    void resolvePointers(const QList<User*>& users);
};

#endif // NOTIFICATION_H
