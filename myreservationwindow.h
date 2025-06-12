#ifndef MYRESERVATIONSWINDOW_H
#define MYRESERVATIONSWINDOW_H
#include "student.h"
#include "library.h"
#include <QFrame>


class MyReservationWindow : public QFrame {
public:
    explicit MyReservationWindow(Student* student,Library* library,QWidget* parent = nullptr);
};

#endif // MYRESERVATIONWINDOW_H
