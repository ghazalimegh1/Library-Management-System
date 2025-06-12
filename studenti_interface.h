#ifndef STUDENTI_INTERFACE_H
#define STUDENTI_INTERFACE_H

#include <QMainWindow>
#include "student.h"
#include "library.h"
#include "sidebar.h"
#include <QStackedWidget>
QT_BEGIN_NAMESPACE
namespace Ui {
class StudentI_Interface;
}
QT_END_NAMESPACE

class StudentI_Interface : public QMainWindow
{
    Q_OBJECT

public:
    explicit StudentI_Interface(Student* student,Library* library,QWidget *parent = nullptr);


private:
    Ui::StudentI_Interface *ui;
    QStackedWidget* mainStack;
    Sidebar* sidebar;
    Student* student;
    Library* library;
private slots:
    void switchToSearchResources();
    void switchToMyLoans();
    void switchToMyReservations();
    void switchToMyNotifications();
    void switchToLogout();
    void switchToDashboard();
};

#endif // STUDENTI_INTERFACE_H
