/********************************************************************************
** Form generated from reading UI file 'loginform.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINFORM_H
#define UI_LOGINFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginForm
{
public:
    QPushButton *ExitButton;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *ID;
    QLabel *password;
    QLineEdit *IdInput;
    QLineEdit *PasswordInput;
    QPushButton *LoginButton;

    void setupUi(QDialog *LoginForm)
    {
        if (LoginForm->objectName().isEmpty())
            LoginForm->setObjectName("LoginForm");
        LoginForm->resize(400, 300);
        ExitButton = new QPushButton(LoginForm);
        ExitButton->setObjectName("ExitButton");
        ExitButton->setGeometry(QRect(220, 200, 56, 18));
        formLayoutWidget = new QWidget(LoginForm);
        formLayoutWidget->setObjectName("formLayoutWidget");
        formLayoutWidget->setGeometry(QRect(130, 80, 160, 80));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName("formLayout");
        formLayout->setContentsMargins(0, 0, 0, 0);
        ID = new QLabel(formLayoutWidget);
        ID->setObjectName("ID");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, ID);

        password = new QLabel(formLayoutWidget);
        password->setObjectName("password");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, password);

        IdInput = new QLineEdit(formLayoutWidget);
        IdInput->setObjectName("IdInput");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, IdInput);

        PasswordInput = new QLineEdit(formLayoutWidget);
        PasswordInput->setObjectName("PasswordInput");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, PasswordInput);

        LoginButton = new QPushButton(LoginForm);
        LoginButton->setObjectName("LoginButton");
        LoginButton->setGeometry(QRect(140, 200, 56, 18));

        retranslateUi(LoginForm);

        QMetaObject::connectSlotsByName(LoginForm);
    } // setupUi

    void retranslateUi(QDialog *LoginForm)
    {
        LoginForm->setWindowTitle(QCoreApplication::translate("LoginForm", "Dialog", nullptr));
        ExitButton->setText(QCoreApplication::translate("LoginForm", "EXIT", nullptr));
        ID->setText(QCoreApplication::translate("LoginForm", "ID (or Email)", nullptr));
        password->setText(QCoreApplication::translate("LoginForm", "Password", nullptr));
        LoginButton->setText(QCoreApplication::translate("LoginForm", "LOGIN", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginForm: public Ui_LoginForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINFORM_H
