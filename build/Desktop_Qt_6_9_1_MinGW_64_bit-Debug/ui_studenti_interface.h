/********************************************************************************
** Form generated from reading UI file 'studenti_interface.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STUDENTI_INTERFACE_H
#define UI_STUDENTI_INTERFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StudentI_Interface
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *StudentI_Interface)
    {
        if (StudentI_Interface->objectName().isEmpty())
            StudentI_Interface->setObjectName("StudentI_Interface");
        StudentI_Interface->resize(578, 370);
        StudentI_Interface->setStyleSheet(QString::fromUtf8("background-color:white;\n"
"raduis: 20px;"));
        centralwidget = new QWidget(StudentI_Interface);
        centralwidget->setObjectName("centralwidget");
        StudentI_Interface->setCentralWidget(centralwidget);
        menubar = new QMenuBar(StudentI_Interface);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 578, 18));
        StudentI_Interface->setMenuBar(menubar);
        statusbar = new QStatusBar(StudentI_Interface);
        statusbar->setObjectName("statusbar");
        StudentI_Interface->setStatusBar(statusbar);

        retranslateUi(StudentI_Interface);

        QMetaObject::connectSlotsByName(StudentI_Interface);
    } // setupUi

    void retranslateUi(QMainWindow *StudentI_Interface)
    {
        StudentI_Interface->setWindowTitle(QCoreApplication::translate("StudentI_Interface", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StudentI_Interface: public Ui_StudentI_Interface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STUDENTI_INTERFACE_H
