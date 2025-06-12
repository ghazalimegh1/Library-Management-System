#include "admininterfaces.h"
#include "sidebar.h"
#include "admindashboard.h"
#include <QHBoxLayout>
#include <QLabel>
#include "adminsearchresources.h"
#include "adminloans.h"
#include "adminreservations.h"
#include "newloginform.h"
#include "notificationwindow.h"
#include "adminusermanagement.h"

Admin_Interface::Admin_Interface(Admin* admin, Library* library, QWidget *parent)
    : QMainWindow(parent), admin(admin), library(library) {

    QWidget* central = new QWidget(this);
    QHBoxLayout* layout = new QHBoxLayout(central);
    QStringList buttons =  {
        "🏠 Dashboard",
        "🔍 Resources",
        "📚 Loans",
        "📋 Reservations",
        "🔔 Notifications",
        "👤 Users",
        "🚪 Logout"
    };
    sidebar = new Sidebar(buttons);
    mainStack = new QStackedWidget();


    AdminDashboard* dashboard = new AdminDashboard(admin,library);
    AdminSearchResources* searchPage = new AdminSearchResources(library);
    AdminLoansWindow* loansPage = new AdminLoansWindow(library);
    AdminReservationsWindow* reservationsPage = new AdminReservationsWindow(library);
    NotificationWindow* notificationPage = new NotificationWindow(admin,library);
    AdminUserManagement* usermanagementPage = new AdminUserManagement(library);


    mainStack->addWidget(dashboard);
    mainStack->addWidget(searchPage);
    mainStack->addWidget(loansPage);
    mainStack->addWidget(reservationsPage);
    mainStack->addWidget(notificationPage);
    mainStack->addWidget(usermanagementPage);


    layout->addWidget(sidebar);
    layout->addWidget(mainStack);

    connect(sidebar, &Sidebar::showDashboard, this, &Admin_Interface::switchToDashboard);
    connect(sidebar, &Sidebar::showSearchResources, this, &Admin_Interface::switchToSearchResources);
    connect(sidebar, &Sidebar::showMyLoans, this, &Admin_Interface::switchToMyLoans);
    connect(sidebar, &Sidebar::showMyReservations, this, &Admin_Interface::switchToMyReservations);
    connect(sidebar, &Sidebar::showMyNotifications, this, &Admin_Interface::switchToMyNotifications);
    connect(sidebar, &Sidebar::showMyUsers, this, &Admin_Interface::switchToMyUsers);
    connect(sidebar, &Sidebar::logout, this, &Admin_Interface::switchToLogout);

    setCentralWidget(central);
    setWindowTitle("Admin Interface");
    resize(900, 600);
}

void Admin_Interface::switchToDashboard(){
    mainStack->setCurrentIndex(0);
}

void Admin_Interface::switchToSearchResources() {
    mainStack->setCurrentIndex(1);
}

void Admin_Interface::switchToMyLoans() {
    mainStack->setCurrentIndex(2);
}

void Admin_Interface::switchToMyReservations() {
    mainStack->setCurrentIndex(3);
}

void Admin_Interface::switchToMyNotifications(){
    mainStack->setCurrentIndex(4);
}

void Admin_Interface::switchToMyUsers(){
    mainStack->setCurrentIndex(5);
}
void Admin_Interface::switchToLogout(){
    exit(1);
}



