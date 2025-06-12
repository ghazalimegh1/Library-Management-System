#include "newloginform.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QGraphicsOpacityEffect>
#include <QDebug>
#include "studenti_interface.h"
#include "admininterfaces.h"
#include <QMessageBox>

NewLoginForm::NewLoginForm(Library* library, QWidget *parent)
    : QWidget(parent), library(library)
{
    setFixedSize(900, 600);
    setWindowTitle("Library Login");


    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);


    QFrame* leftFrame = new QFrame();
    leftFrame->setStyleSheet("background-color: white;");
    leftFrame->setMinimumWidth(400);

    QVBoxLayout* imageLayout = new QVBoxLayout(leftFrame);
    imageLayout->setAlignment(Qt::AlignCenter);

    QLabel* imageLabel = new QLabel();
    QPixmap pixmap("C:/Users/HP/Downloads/student_reading_a_book.jpg");
    imageLabel->setPixmap(pixmap);
    imageLabel->setScaledContents(true);
    imageLabel->setFixedSize(280, 280);
    imageLayout->addWidget(imageLabel);


    QFrame* rightFrame = new QFrame();
    rightFrame->setStyleSheet("background-color: #1e2a38;");
    rightFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout* rightLayout = new QVBoxLayout(rightFrame);
    rightLayout->setAlignment(Qt::AlignCenter);


    QWidget* loginPanel = new QWidget();
    loginPanel->setStyleSheet(R"(
        background: rgba(255, 255, 255, 0.1);
        border-radius: 20px;
        border: 1px solid rgba(255, 255, 255, 0.3);
    )");
    loginPanel->setFixedSize(380, 360);

    QVBoxLayout* formLayout = new QVBoxLayout(loginPanel);
    formLayout->setContentsMargins(25, 35, 25, 35);
    formLayout->setSpacing(18);


    QLabel* title = new QLabel("Library Management System");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("color: white; font-size: 18px; font-weight: bold; background: transparent; border: none;");
    formLayout->addWidget(title);


    emailInput = new QLineEdit();
    emailInput->setPlaceholderText("📧 Email or ID or Username");
    emailInput->setStyleSheet(R"(
        QLineEdit {
            padding: 10px;
            border-radius: 8px;
            font-size: 13px;
            background-color: rgba(255, 255, 255, 0.85);
            border: none;
        }
    )");
    formLayout->addWidget(emailInput);


    passwordInput = new QLineEdit();
    passwordInput->setPlaceholderText("🔒 Password");
    passwordInput->setEchoMode(QLineEdit::Password);
    passwordInput->setStyleSheet(R"(
        QLineEdit {
            padding: 10px;
            border-radius: 8px;
            font-size: 13px;
            background-color: rgba(255, 255, 255, 0.85);
            border: none;
        }
    )");
    formLayout->addWidget(passwordInput);


    loginButton = new QPushButton("Login");
    loginButton->setStyleSheet(R"(
        QPushButton {
            background-color: #1e88e5;
            color: white;
            border-radius: 8px;
            padding: 10px;
            font-size: 13px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #1565c0;
        }
    )");
    connect(loginButton, &QPushButton::clicked, this, &NewLoginForm::handleLogin);
    formLayout->addWidget(loginButton);

    formLayout->addStretch();


    rightLayout->addWidget(loginPanel);
    mainLayout->addWidget(leftFrame);
    mainLayout->addWidget(rightFrame);
}


void NewLoginForm::handleLogin() {
    QString credential = emailInput->text();
    QString password = passwordInput->text();
    bool isfound = false;
    for (User* user : library->getUsers()) {
        if ((user->get_email() == credential || QString::number(user->get_ID()) ==  credential || user->get_username() == credential) && user->get_password() == password) {
            isfound = true;
            QString role = user->what_is_role();
            if(role=="Student"){
                Student* s = dynamic_cast<Student*>(user);
                Student* student = new Student(user->get_ID(),user->get_username(),user->get_email(),user->get_password(),s->get_group(),s->get_year());
                StudentI_Interface* student_interface = new StudentI_Interface(student,this->library);
                student_interface->show();
                this->hide();
            }else{
                Admin* admin = new Admin(user->get_ID(),user->get_username(),user->get_email(),user->get_password());
                Admin_Interface* admin_interface = new Admin_Interface(admin,this->library);
                admin_interface->show();
                this->hide();
            }




        }
    }

    if(!isfound){
        emailInput->setText("");
        passwordInput->setText("");
        QMessageBox::warning(this,"Credentials","Credentials are incorrect");

    }
}


