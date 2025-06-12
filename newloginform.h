#ifndef NEWLOGINFORM_H
#define NEWLOGINFORM_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include "library.h"

class NewLoginForm : public QWidget {
    Q_OBJECT

public:
    explicit NewLoginForm(Library* library, QWidget *parent = nullptr);

signals:


private slots:
    void handleLogin();

private:
    QLineEdit* emailInput;
    QLineEdit* passwordInput;
    QPushButton* loginButton;
    QLabel* errorLabel;

    Library* library;
};

#endif // NEWLOGINFORM_H
