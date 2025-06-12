#ifndef ADMINSEARCHRESOURCES_H
#define ADMINSEARCHRESOURCES_H

#include "library.h"
#include <QFrame>

class AdminSearchResources : public QFrame {
public:
    explicit AdminSearchResources(Library* library,QWidget* parent = nullptr);
};

#endif // ADMINSEARCHRESOURCES_H
