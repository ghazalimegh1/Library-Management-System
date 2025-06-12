#include "studenti_interface.h"
#include "ui_studenti_interface.h"
#include "sidebar.h"
#include "maincontent.h"
#include <QHBoxLayout>
#include <QLabel>
#include "searchresources.h"
#include "myloanswindow.h"
#include "myreservationwindow.h"
#include "newloginform.h"
#include "notificationwindow.h"

StudentI_Interface::StudentI_Interface(Student* student, Library* library, QWidget *parent)
    : QMainWindow(parent), student(student), library(library) {

    QWidget* central = new QWidget(this);
    QHBoxLayout* layout = new QHBoxLayout(central);
    QStringList buttons =  {
        "🏠 Dashboard",
        "🔍 Search Resources",
        "📚 My Loans",
        "📋 My Reservations",
        "🔔 Notifications",
        "🚪 Logout"
    };
    sidebar = new Sidebar(buttons);
    mainStack = new QStackedWidget();


    MainContent* dashboard = new MainContent(student,library);
    SearchResources* searchPage = new SearchResources(library,student);
    MyLoansWindow* loansPage = new MyLoansWindow(student, library);
    MyReservationWindow* reservationsPage = new MyReservationWindow(student, library);
    NotificationWindow* notificationPage = new NotificationWindow(student,library);

    mainStack->addWidget(dashboard);
    mainStack->addWidget(searchPage);
    mainStack->addWidget(loansPage);
    mainStack->addWidget(reservationsPage);
    mainStack->addWidget(notificationPage);


    layout->addWidget(sidebar);
    layout->addWidget(mainStack);

    connect(sidebar, &Sidebar::showDashboard, this, &StudentI_Interface::switchToDashboard);
    connect(sidebar, &Sidebar::showSearchResources, this, &StudentI_Interface::switchToSearchResources);
    connect(sidebar, &Sidebar::showMyLoans, this, &StudentI_Interface::switchToMyLoans);
    connect(sidebar, &Sidebar::showMyReservations, this, &StudentI_Interface::switchToMyReservations);
    connect(sidebar, &Sidebar::showMyNotifications, this, &StudentI_Interface::switchToMyNotifications);
    connect(sidebar, &Sidebar::logout, this, &StudentI_Interface::switchToLogout);

    setCentralWidget(central);
    setWindowTitle("Student Interface");
    resize(900, 600);


}

void StudentI_Interface::switchToDashboard(){
    mainStack->setCurrentIndex(0);
}

void StudentI_Interface::switchToSearchResources() {
    mainStack->setCurrentIndex(1);
}

void StudentI_Interface::switchToMyLoans() {
    mainStack->setCurrentIndex(2);
}

void StudentI_Interface::switchToMyReservations() {
    mainStack->setCurrentIndex(3);
}

void StudentI_Interface::switchToMyNotifications(){
    mainStack->setCurrentIndex(4);
}

void StudentI_Interface::switchToLogout(){
    exit(1);
}



