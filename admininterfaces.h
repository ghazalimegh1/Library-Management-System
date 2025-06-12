#ifndef ADMIN_INTERFACE_H
#define ADMIN_INTERFACE_H

#include <QMainWindow>
#include "admin.h"
#include "library.h"
#include "sidebar.h"
#include <QStackedWidget>
QT_BEGIN_NAMESPACE
namespace Ui {
class Admin_Interface;
}
QT_END_NAMESPACE

class Admin_Interface : public QMainWindow
{
    Q_OBJECT

public:
    explicit Admin_Interface(Admin* admin,Library* library,QWidget *parent = nullptr);


private:
    Ui::Admin_Interface *ui;
    QStackedWidget* mainStack;
    Sidebar* sidebar;
    Admin* admin;
    Library* library;
private slots:
    void switchToSearchResources();
    void switchToMyLoans();
    void switchToMyReservations();
    void switchToMyNotifications();
    void switchToLogout();
    void switchToDashboard();
    void switchToMyUsers();
};

#endif // ADMIN_INTERFACE_H
