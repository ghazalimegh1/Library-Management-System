#ifndef SEARCHRESOURCES_H
#define SEARCHRESOURCES_H
#include "student.h"
#include "library.h"
#include <QFrame>

class SearchResources : public QFrame {
public:
    explicit SearchResources(Library* library, Student* student, QWidget* parent = nullptr);
};

#endif // SEARCHRESOURCES_H
