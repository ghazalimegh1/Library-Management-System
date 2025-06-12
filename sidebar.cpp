#include "sidebar.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

Sidebar::Sidebar(QStringList& buttons,QWidget* parent) : QFrame(parent) {
    setFixedWidth(200);
    setStyleSheet(R"(
        QFrame {
            background-color: #1e2a38;
            color: white;
        }
        QPushButton {
            background-color: transparent;
            color: white;
            padding: 10px;
            text-align: left;
            border: none;
            font-size: 14px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #2d3b4e;
        }
        QLabel {
            font-size: 18px;
            font-weight: bold;
        }
    )");

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(15, 15, 15, 15);
    layout->setSpacing(10);

    QLabel* title = new QLabel("📚 Library");
    layout->addWidget(title);
    layout->addSpacing(20);


    QPushButton* dashboardBtn = new QPushButton(buttons[0]);
    QPushButton* searchBtn = new QPushButton(buttons[1]);
    QPushButton* loansBtn = new QPushButton(buttons[2]);
    QPushButton* reservationsBtn = new QPushButton(buttons[3]);
    QPushButton* notificationsBtn = new QPushButton(buttons[4]);

    QPushButton* usersBtn;
    QPushButton* logoutBtn;;

    if(buttons.size()==6){
        usersBtn = nullptr;
        logoutBtn = new QPushButton(buttons[5]);
    }
    else if(buttons.size() == 7){
        usersBtn = new QPushButton(buttons[5]);
        logoutBtn = new QPushButton(buttons[6]);
    }

    layout->addWidget(dashboardBtn);
    layout->addWidget(searchBtn);
    layout->addWidget(loansBtn);
    layout->addWidget(reservationsBtn);
    layout->addWidget(notificationsBtn);
    if(usersBtn){
        layout->addWidget(usersBtn);
        layout->addWidget(logoutBtn);
    }
    else{
        layout->addWidget(logoutBtn);
    }

    layout->addStretch();

    connect(dashboardBtn, &QPushButton::clicked, this, [this]() {
        emit showDashboard();
    });
    connect(searchBtn, &QPushButton::clicked, this, [this]() {
        emit showSearchResources();
    });
    connect(loansBtn, &QPushButton::clicked, this, [this]() {
        emit showMyLoans();
    });
    connect(reservationsBtn, &QPushButton::clicked, this, [this]() {
        emit showMyReservations();
    });
    connect(notificationsBtn, &QPushButton::clicked, this, [this]() {
        emit showMyNotifications();
    });
    connect(usersBtn,&QPushButton::clicked,this,[this](){
        emit showMyUsers();
    });
    connect(logoutBtn, &QPushButton::clicked, this, [this]() {
        emit logout();
    });

}


