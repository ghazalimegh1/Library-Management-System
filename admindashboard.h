#ifndef ADMINDASHBOARD_H
#define ADMINDASHBOARD_H
#include "admin.h"
#include "library.h"
#include <QFrame>
class AdminDashboard : public QFrame
{
public:
    explicit AdminDashboard(Admin* admin,Library* library,QWidget* parent = nullptr);
};

#endif // ADMINDASHBOARD_H
