/********************************************************************************
** Form generated from reading UI file 'lbms.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LBMS_H
#define UI_LBMS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_lbms
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *lbms)
    {
        if (lbms->objectName().isEmpty())
            lbms->setObjectName("lbms");
        lbms->resize(800, 600);
        centralwidget = new QWidget(lbms);
        centralwidget->setObjectName("centralwidget");
        lbms->setCentralWidget(centralwidget);
        menubar = new QMenuBar(lbms);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 18));
        lbms->setMenuBar(menubar);
        statusbar = new QStatusBar(lbms);
        statusbar->setObjectName("statusbar");
        lbms->setStatusBar(statusbar);

        retranslateUi(lbms);

        QMetaObject::connectSlotsByName(lbms);
    } // setupUi

    void retranslateUi(QMainWindow *lbms)
    {
        lbms->setWindowTitle(QCoreApplication::translate("lbms", "lbms", nullptr));
    } // retranslateUi

};

namespace Ui {
    class lbms: public Ui_lbms {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LBMS_H
