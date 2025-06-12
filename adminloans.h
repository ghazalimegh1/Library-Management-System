#ifndef ADMINLOANSWINDOW_H
#define ADMINLOANSWINDOW_H
#include "library.h"
#include <QFrame>

class AdminLoansWindow : public QFrame {
public:
    explicit AdminLoansWindow(Library* library,QWidget* parent = nullptr);
};

#endif // ADMINLOANSWINDOW_H
