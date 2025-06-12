#ifndef MYLOANSWINDOW_H
#define MYLOANSWINDOW_H
#include "student.h"
#include "library.h"
#include <QFrame>

class MyLoansWindow : public QFrame {
public:
    explicit MyLoansWindow(Student* student,Library* library,QWidget* parent = nullptr);
};

#endif // MYLOANSWINDOW_H
