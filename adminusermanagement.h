#ifndef ADMINUSERMANAGEMENT_H
#define ADMINUSERMANAGEMENT_H

#include "library.h"
#include <QFrame>

class AdminUserManagement : public QFrame {
public:
    explicit AdminUserManagement(Library* library,QWidget* parent = nullptr);
};

#endif // ADMINUSERMANAGEMENT_H
