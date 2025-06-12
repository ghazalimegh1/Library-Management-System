#ifndef MAINCONTENT_H
#define MAINCONTENT_H
#include "student.h"
#include "library.h"
#include <QFrame>
class MainContent : public QFrame
{
public:
    explicit MainContent(Student* student,Library* library,QWidget* parent = nullptr);
};

#endif // MAINCONTENT_H
