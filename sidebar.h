#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QFrame>

class Sidebar : public QFrame {
    Q_OBJECT
public:
    explicit Sidebar(QStringList&,QWidget* parent = nullptr);
signals:
    void showDashboard();
    void showSearchResources();
    void showMyLoans();
    void showMyReservations();
    void showMyNotifications();
    void showMyUsers();
    void logout();
};

#endif // SIDEBAR_H
