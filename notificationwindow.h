#ifndef NOTIFICATIONWINDOW_H
#define NOTIFICATIONWINDOW_H
#include "user.h"
#include "library.h"
#include <QFrame>

class NotificationWindow : public QFrame
{
private:
    User* user;
    Library* library;
public:
    NotificationWindow(User*,Library*);
};

#endif // NOTIFICATIONWINDOW_H
