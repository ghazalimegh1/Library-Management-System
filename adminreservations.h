#ifndef ADMINRESERVATIONSWINDOW_H
#define ADMINRESERVATIONSWINDOW_H
#include "library.h"
#include <QFrame>

class AdminReservationsWindow : public QFrame {
public:
    explicit AdminReservationsWindow(Library* library,QWidget* parent = nullptr);
};

#endif // ADMINRESERVATIONSWINDOW_H
