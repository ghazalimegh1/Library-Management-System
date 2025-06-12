#include "adminusermanagement.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTableWidget>
#include <QHeaderView>
#include <QFrame>
#include <QPixmap>
#include <QDebug>
#include <QFormLayout>
#include <QComboBox>
#include <QDateEdit>

AdminUserManagement::AdminUserManagement(Library* library,QWidget* parent) : QFrame(parent) {

    setFixedWidth(700);
    setStyleSheet(R"(
        QFrame {
            background-color: #f8fafc;
            color: #1e293b;
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
    QVBoxLayout* allMainLayout = new QVBoxLayout(this);
    allMainLayout->setContentsMargins(16, 16, 16, 16);
    allMainLayout->setSpacing(16); //
    QLabel* profilePic = new QLabel();
    QPixmap profilePixmap("C:/Users/HP/Downloads/profile.png");
    profilePic->setPixmap(profilePixmap.scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    profilePic->setFixedSize(32, 32);


    QPushButton* search = new QPushButton("🔍");
    search->setStyleSheet("width:13px;height:13px;font-size:13px;border-radius:10px;border-width: 1px;border-style: solid;border-color:black;background-color:white;text-align: center");
    QHBoxLayout* topBarLayout = new QHBoxLayout();
    QLineEdit* searchBar = new QLineEdit();
    searchBar->setPlaceholderText("Search for Users");
    searchBar->setMinimumHeight(36);
    searchBar->setStyleSheet(R"(
        QLineEdit {
            background-color: #ffffff;
            border: 1px solid #e5e7eb;
            border-radius: 8px;
            padding-left: 8px;
            font-size: 14px;
        }
    )");
    QPushButton* addUser = new QPushButton("Add User");
    addUser->setStyleSheet(R"(
            QPushButton {
                background-color: #2563EB;
                color: white;
                border: none;
                border-radius: 6px;
                padding: 6px 12px;
                font-size: 13px;
                text-align: center;
            }
            QPushButton:hover {
                background-color: #1d4ed8;
            }
        )");

    QWidget* addForm = new QWidget();
    addForm->setVisible(false);

    QFormLayout* addFormLayout = new QFormLayout(addForm);


    QLineEdit* idEditnew= new QLineEdit();
    QLineEdit* usernameEditnew = new QLineEdit();
    QLineEdit* emailEditnew = new QLineEdit();
    QLineEdit* passwordEditnew = new QLineEdit();


    QComboBox* typeCombo = new QComboBox();
    typeCombo->addItems({"Admin","Student"});

    addFormLayout->addRow("ID:", idEditnew);
    addFormLayout->addRow("Username:", usernameEditnew);
    addFormLayout->addRow("Email:", emailEditnew);
    addFormLayout->addRow("Password:", passwordEditnew);
    addFormLayout->addRow("Type:", typeCombo);


    QLineEdit* yearEditnew = new QLineEdit();
    QLineEdit* groupEditnew = new QLineEdit();


    addFormLayout->addRow("Year:", yearEditnew);
    addFormLayout->addRow("Group:", groupEditnew);



    yearEditnew->setVisible(false);
    groupEditnew->setVisible(false);
    addFormLayout->labelForField(groupEditnew)->setVisible(false);
    addFormLayout->labelForField(yearEditnew)->setVisible(false);




    connect(typeCombo, &QComboBox::currentTextChanged, [=](const QString& type){
        bool isStudent = (type == "Student");


        groupEditnew->setVisible(isStudent);
        addFormLayout->labelForField(groupEditnew)->setVisible(isStudent);
        yearEditnew->setVisible(isStudent);
        addFormLayout->labelForField(yearEditnew)->setVisible(isStudent);


    });


    QPushButton* addSubmitBtn = new QPushButton("Add User");
    addFormLayout->addRow(addSubmitBtn);


    connect(addUser, &QPushButton::clicked, [=]() {
        addForm->setVisible(true);
    });


    connect(addSubmitBtn, &QPushButton::clicked, [=]() {
        QString id = idEditnew->text();
        QString username = usernameEditnew->text();
        QString email = emailEditnew->text();
        QString password = passwordEditnew->text();
        QString type = typeCombo->currentText();

        User* newUser = nullptr;

        if (type == "Student") {
            Student* student = new Student(id.toInt(),username, email, password, yearEditnew->text().toInt(),groupEditnew->text().toInt());

            newUser = student;
        } else  {
            Admin* admin = new Admin(id.toInt(),username, email, password);

            newUser = admin;
        }

        if (newUser) {
            library->addUser(newUser);
            library->saveToJson("C:/Users/HP/Documents/LBMS/build/Desktop_Qt_6_9_1_MinGW_64_bit-Debug/data.json");
            addForm->setVisible(false);
        }
    });


    topBarLayout->addWidget(searchBar);

    topBarLayout->addWidget(search);
    topBarLayout->addStretch();
    topBarLayout->addWidget(addUser);
    topBarLayout->addWidget(profilePic);

    QWidget* topBarWidget = new QWidget();
    topBarWidget->setLayout(topBarLayout);





    QVector<User*> library_users = library->getUsers();

    QLabel* usersTitle = new QLabel("Users");
    usersTitle->setStyleSheet("font-size: 18px; font-weight: bold; color: #1e293b;");




    QTableWidget* usersTable = new QTableWidget();
    usersTable->setColumnCount(6);
    usersTable->setRowCount(library_users.size());

    usersTable->setHorizontalHeaderLabels({ "Name","ID", "Type", "email", "password", "Actions" });


    for(int i = 0; i < usersTable->columnCount(); i++) {
        QTableWidgetItem* header = usersTable->horizontalHeaderItem(i);
        if(header) {
            header->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        }
    }

    int row = 0;


    for(User* user : library_users) {




        QTableWidgetItem* nameItem = new QTableWidgetItem(user->get_username());

        nameItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        usersTable->setItem(row, 0, nameItem);


        QTableWidgetItem* residItem = new QTableWidgetItem(QString::number(user->get_ID()));

        residItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        usersTable->setItem(row, 1, residItem);

        QTableWidgetItem* typeItem = new QTableWidgetItem(user->what_is_role());
        typeItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        usersTable->setItem(row, 2, typeItem);


        QTableWidgetItem* emailItem = new QTableWidgetItem(user->get_email());
        emailItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        usersTable->setItem(row, 3, emailItem);

        QTableWidgetItem* passwordItem = new QTableWidgetItem(user->get_password());
        passwordItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        usersTable->setItem(row, 4, passwordItem);







        usersTable->setRowHeight(row, 44);


        QPushButton* editBtn = new QPushButton("Edit");
        QPushButton* removeBtn = new QPushButton("Remove");

        QString btnStyle1 = R"(
            QPushButton {
                background-color: #2563EB;
                color: white;
                border: none;
                border-radius: 6px;
                padding: 6px 12px;
                font-size: 13px;
                text-align: center;
            }
            QPushButton:hover {
                background-color: #1d4ed8;
            }
        )";

        QString btnStyle2 = R"(
            QPushButton {
                background-color: white;
                color: #2563EB;
                border: 1px solid #2563EB;
                border-radius: 6px;
                padding: 6px 12px;
                font-size: 13px;
                text-align: center;
            }
            QPushButton:hover {
                background-color: #eff6ff;
            }
        )";

        connect(removeBtn,&QPushButton::clicked,[=](){

            library->removeUser(user);
            library->saveToJson("C:/Users/HP/Documents/LBMS/build/Desktop_Qt_6_9_1_MinGW_64_bit-Debug/data.json");
            int rowToMove = usersTable->indexAt(removeBtn->parentWidget()->pos()).row();
            usersTable->removeRow(rowToMove);

        });

        editBtn->setStyleSheet(btnStyle1);
        removeBtn->setStyleSheet(btnStyle2);

        QWidget* actionWidget = new QWidget();
        QHBoxLayout* actionLayout = new QHBoxLayout(actionWidget);
        actionLayout->setContentsMargins(4, 4, 4, 4);
        actionLayout->setSpacing(6);


        QWidget* editForm = new QWidget();
        editForm->setVisible(false);

        QFormLayout* formLayout = new QFormLayout(editForm);


        QLineEdit* idEdit = new QLineEdit();
        QLineEdit* usernameEdit = new QLineEdit();
        QLineEdit* emailEdit = new QLineEdit();
        QLineEdit* passwordEdit = new QLineEdit();




        formLayout->addRow("ID:", idEdit);
        formLayout->addRow("Username:", usernameEdit);
        formLayout->addRow("Email:", emailEdit);
        formLayout->addRow("Password:", passwordEdit);



        QLineEdit* yearEdit = new QLineEdit();
        QLineEdit* groupEdit = new QLineEdit();


        formLayout->addRow("Year:", yearEdit);


        formLayout->addRow("Group:", groupEdit);



        yearEdit->setVisible(false);
        formLayout->labelForField(yearEdit)->setVisible(false);

        groupEdit->setVisible(false);
        formLayout->labelForField(groupEdit)->setVisible(false);


        QString type = user->what_is_role();
        bool isStudent = (type == "Student");


        yearEdit->setVisible(isStudent);
        formLayout->labelForField(yearEdit)->setVisible(isStudent);

        groupEdit->setVisible(isStudent);
        formLayout->labelForField(groupEdit)->setVisible(isStudent);



        QPushButton* submitBtn = new QPushButton("Save Changes");
        formLayout->addRow(submitBtn);


        connect(editBtn, &QPushButton::clicked, [=]() {

            idEdit->setText(QString::number(user->get_ID()));
            emailEdit->setText(user->get_email());
            passwordEdit->setText(user->get_password());
            usernameEdit->setText(user->get_username());

            Student* student = dynamic_cast<Student*>(user);



            if (student) {
                yearEdit->setText(QString::number(student->get_year()));
                groupEdit->setText(QString::number(student->get_group()));
            }



            editForm->setVisible(true);


            connect(submitBtn, &QPushButton::clicked, [=]() {
                for (User* u : library->getUsers()) {
                    if (u->get_ID() == user->get_ID()) {
                        u->set_ID((idEdit->text()).toInt());
                        u->set_Username(usernameEdit->text());
                        u->set_Email(emailEdit->text());
                        u->set_Password(passwordEdit->text());

                        Student* student = dynamic_cast<Student*>(u);


                        if (student) {
                            student->set_year((yearEdit->text()).toInt());
                            student->set_group((groupEdit->text().toInt()));
                        }

                        break;
                    }
                }


                library->saveToJson("C:/Users/HP/Documents/LBMS/build/Desktop_Qt_6_9_1_MinGW_64_bit-Debug/data.json");


                submitBtn->deleteLater();
                editForm->deleteLater();

            });
        });


        actionLayout->addWidget(editBtn);
        actionLayout->addWidget(removeBtn);


        usersTable->setCellWidget(row, 5, actionWidget);
        row++;

    }



    usersTable->setColumnWidth(0, 100);
    usersTable->setColumnWidth(1, 75);
    usersTable->setColumnWidth(2, 75);
    usersTable->setColumnWidth(3, 165);
    usersTable->setColumnWidth(4, 100);
    usersTable->setColumnWidth(5, 150);



    usersTable->setAlternatingRowColors(true);
    usersTable->horizontalHeader()->setStretchLastSection(false);
    usersTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    usersTable->setSelectionMode(QAbstractItemView::NoSelection);
    usersTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    usersTable->setShowGrid(false);
    usersTable->verticalHeader()->setVisible(false);
    usersTable->setStyleSheet(R"(
    QTableWidget {
        background-color: #ffffff;
        border: 1px solid #e5e7eb;
        border-radius: 10px;
        font-size: 14px;
        color: #1e293b;
        gridline-color: #f1f5f9;
    }
    QHeaderView::section {
        background-color: #f3f4f6;
        color: #374151;
        padding: 10px;
        font-weight: bold;
        border: none;
        border-bottom: 1px solid #e5e7eb;
    }
    QTableWidget::item:alternate {
        background-color: #f9fafb;
    }
    QTableCornerButton::section {
        background-color: #f3f4f6;
        border: none;
    }
)");

    connect(search, &QPushButton::clicked, this, [=]() {
        QString keyword = searchBar->text().trimmed().toLower();
        for (int i = 0; i < usersTable->rowCount(); ++i) {
            bool match = false;
            for (int j = 0; j < 6; ++j) {
                QTableWidgetItem* item = usersTable->item(i, j);
                if (item && item->text().toLower().contains(keyword)) {
                    match = true;
                    break;
                }
            }
            usersTable->setRowHidden(i, !match);
        }
    });


    allMainLayout->addWidget(topBarWidget);
    allMainLayout->addWidget(usersTitle);
    allMainLayout->addWidget(usersTable);
}
