#include "adminsearchresources.h"
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

AdminSearchResources::AdminSearchResources(Library* library,QWidget* parent) : QFrame(parent) {

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
    searchBar->setPlaceholderText("Search Resources");
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
    QPushButton* addResource = new QPushButton("Add Resource");
    addResource->setStyleSheet(R"(
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

    QLineEdit* titleEditnew = new QLineEdit();
    QLineEdit* categoryEditnew = new QLineEdit();
    QLineEdit* authorEditnew = new QLineEdit();
    QDateEdit* dateEditnew = new QDateEdit();
    dateEditnew->setCalendarPopup(true);
    dateEditnew->setDisplayFormat("yyyy-MM-dd");

    QComboBox* typeCombo = new QComboBox();
    typeCombo->addItems({"Book", "DigitalContent", "Thesis", "Article"});

    addFormLayout->addRow("Title:", titleEditnew);
    addFormLayout->addRow("Category:", categoryEditnew);
    addFormLayout->addRow("Author:", authorEditnew);
    addFormLayout->addRow("Date of Publication:", dateEditnew);
    addFormLayout->addRow("Type:", typeCombo);


    QLineEdit* subjectEditnew = new QLineEdit();
    QLineEdit* universityEditnew = new QLineEdit();
    QLineEdit* journalEditnew = new QLineEdit();

    addFormLayout->addRow("Subject:", subjectEditnew);
    addFormLayout->addRow("University (Thesis only):", universityEditnew);
    addFormLayout->addRow("Journal (Article only):", journalEditnew);


    universityEditnew->setVisible(false);
    addFormLayout->labelForField(universityEditnew)->setVisible(false);

    journalEditnew->setVisible(false);
    addFormLayout->labelForField(journalEditnew)->setVisible(false);


    connect(typeCombo, &QComboBox::currentTextChanged, [=](const QString& type){
        bool isThesis = (type == "Thesis");
        bool isArticle = (type == "Article");

        universityEditnew->setVisible(isThesis);
        addFormLayout->labelForField(universityEditnew)->setVisible(isThesis);

        journalEditnew->setVisible(isArticle);
        addFormLayout->labelForField(journalEditnew)->setVisible(isArticle);
    });


    QPushButton* addSubmitBtn = new QPushButton("Add Resource");
    addFormLayout->addRow(addSubmitBtn);


    connect(addResource, &QPushButton::clicked, [=]() {
        addForm->setVisible(true);
    });


    connect(addSubmitBtn, &QPushButton::clicked, [=]() {
        QString title = titleEditnew->text();
        QString author = authorEditnew->text();
        QString category = categoryEditnew->text();
        QDate pubDate = dateEditnew->date();
        QString type = typeCombo->currentText();

        Resource* newResource = nullptr;

        if (type == "Book") {
            Book* b = new Book(title,category, author, pubDate, true,subjectEditnew->text());

            newResource = b;
        } else if (type == "DigitalContent") {
            Digital_Content* dc = new Digital_Content(title,category, author, pubDate,true, subjectEditnew->text());

            newResource = dc;
        } else if (type == "Thesis") {
            Thesis* th = new Thesis(title, category,author, pubDate,true, subjectEditnew->text(),universityEditnew->text());

            newResource = th;
        } else if (type == "Article") {
            Article* art = new Article(title,category, author, pubDate,true, subjectEditnew->text(),journalEditnew->text());


            newResource = art;
        }

        if (newResource) {
            library->addResource(newResource);
            library->saveToJson("C:/Users/HP/Documents/LBMS/build/Desktop_Qt_6_9_1_MinGW_64_bit-Debug/data.json");
            addForm->setVisible(false);
        }
    });


    topBarLayout->addWidget(searchBar);

    topBarLayout->addWidget(search);
    topBarLayout->addStretch();
    topBarLayout->addWidget(addResource);
    topBarLayout->addWidget(profilePic);

    QWidget* topBarWidget = new QWidget();
    topBarWidget->setLayout(topBarLayout);





    QVector<Resource*> library_resources = library->getResources();

    QLabel* resourcesTitle = new QLabel("Resources");
    resourcesTitle->setStyleSheet("font-size: 18px; font-weight: bold; color: #1e293b;");




    QTableWidget* resourcesTable = new QTableWidget();
    resourcesTable->setColumnCount(7);
    resourcesTable->setRowCount(library_resources.size());

    resourcesTable->setHorizontalHeaderLabels({ "Name","ID", "Type", "availability", "Borrower", "Borrower ID","Actions" });


    for(int i = 0; i < resourcesTable->columnCount(); i++) {
        QTableWidgetItem* header = resourcesTable->horizontalHeaderItem(i);
        if(header) {
            header->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        }
    }

    int row = 0;


    for(Resource* res : library_resources) {
        QString username = "";
        int userId = -1;
        for(Loan* loan: library->getLoans()){
            if(loan->get_resource()->get_res_id() == res->get_res_id()){
                username = loan->get_user()->get_username();
                userId = loan->get_user()->get_ID();
            };
        }



        QTableWidgetItem* nameItem = new QTableWidgetItem(res->get_title());

        nameItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        resourcesTable->setItem(row, 0, nameItem);


        QTableWidgetItem* residItem = new QTableWidgetItem(QString::number(res->get_res_id()));

        residItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        resourcesTable->setItem(row, 1, residItem);

        QTableWidgetItem* typeItem = new QTableWidgetItem(res->resource_type());
        typeItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        resourcesTable->setItem(row, 2, typeItem);


        QTableWidgetItem* availableItem = new QTableWidgetItem(res->is_available() ? "Available" : "Taken");

        availableItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        resourcesTable->setItem(row, 3, availableItem);


        QTableWidgetItem* userItem = new QTableWidgetItem(username=="" ? "None" : username);
        userItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        resourcesTable->setItem(row, 4, userItem);


        QTableWidgetItem* useridItem = new QTableWidgetItem(userId==-1 ? "None" : QString::number(userId));
        useridItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        resourcesTable->setItem(row, 5, useridItem);







        resourcesTable->setRowHeight(row, 70);


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
            for(Reservation* resv: library->getReservations()){
                if(resv->get_resource()->get_res_id() == res->get_res_id()){
                    QString msg = "Your reserved resource is removed from the library, we are sorry.";
                    Notification* notif = new Notification(msg,resv->get_user());
                    library->removeReservation(resv);
                    library->addNotification(notif);
                }
                }
                library->removeResource(res);
                library->saveToJson("C:/Users/HP/Documents/LBMS/build/Desktop_Qt_6_9_1_MinGW_64_bit-Debug/data.json");
                int rowToMove = resourcesTable->indexAt(removeBtn->parentWidget()->pos()).row();
                resourcesTable->removeRow(rowToMove);

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


        QLineEdit* titleEdit = new QLineEdit();
        QLineEdit* categoryEdit = new QLineEdit();
        QLineEdit* authorEdit = new QLineEdit();
        QDateEdit* dateEdit = new QDateEdit();
        dateEdit->setCalendarPopup(true);
        dateEdit->setDisplayFormat("yyyy-MM-dd");



        formLayout->addRow("Title:", titleEdit);
        formLayout->addRow("Category:", categoryEdit);
        formLayout->addRow("Author:", authorEdit);
        formLayout->addRow("Date of Publication:", dateEdit);



        QLineEdit* subjectEdit = new QLineEdit();
        QLineEdit* universityEdit = new QLineEdit();
        QLineEdit* journalEdit = new QLineEdit();

        formLayout->addRow("Subject:", subjectEdit);


        formLayout->addRow("University (Thesis only):", universityEdit);
        formLayout->addRow("Journal (Article only):", journalEdit);


        universityEdit->setVisible(false);
        formLayout->labelForField(universityEdit)->setVisible(false);

        journalEdit->setVisible(false);
        formLayout->labelForField(journalEdit)->setVisible(false);


        QString type = res->resource_type();
            bool isThesis = (type == "Thesis");
            bool isArticle = (type == "Article");

            universityEdit->setVisible(isThesis);
            formLayout->labelForField(universityEdit)->setVisible(isThesis);

            journalEdit->setVisible(isArticle);
            formLayout->labelForField(journalEdit)->setVisible(isArticle);



        QPushButton* submitBtn = new QPushButton("Save Changes");
        formLayout->addRow(submitBtn);


        connect(editBtn, &QPushButton::clicked, [=]() {
            titleEdit->setText(res->get_title());
            authorEdit->setText(res->get_author());
            dateEdit->setDate(res->get_date_of_publication());
            categoryEdit->setText(res->get_category());

            Book* b = dynamic_cast<Book*>(res);
            Article* a = dynamic_cast<Article*>(res);
            Digital_Content* dc = dynamic_cast<Digital_Content*>(res);
            Thesis* th = dynamic_cast<Thesis*>(res);

            if (b) {
                subjectEdit->setText(b->get_subject());
            }
            if (a) {
                subjectEdit->setText(a->get_subject());
                journalEdit->setText(a->get_journal());
            }
            if (dc) {
                subjectEdit->setText(dc->get_subject());
            }
            if (th) {
                subjectEdit->setText(th->get_subject());
                universityEdit->setText(th->get_university());
            }


            editForm->setVisible(true);


            connect(submitBtn, &QPushButton::clicked, [=]() {
                for (Resource* resource : library->getResources()) {
                    if (resource->get_res_id() == res->get_res_id()) {
                        resource->set_title(titleEdit->text());
                        resource->set_author(authorEdit->text());
                        resource->set_date_of_publication(dateEdit->date());
                        resource->set_category(categoryEdit->text());

                        Book* b = dynamic_cast<Book*>(resource);
                        Article* a = dynamic_cast<Article*>(resource);
                        Digital_Content* dc = dynamic_cast<Digital_Content*>(resource);
                        Thesis* th = dynamic_cast<Thesis*>(resource);

                        if (b) {
                            b->set_subject(subjectEdit->text());
                        }
                        if (a) {
                            a->set_subject(subjectEdit->text());
                            a->set_journal(journalEdit->text());
                        }
                        if (dc) {
                            dc->set_subject(subjectEdit->text());
                        }
                        if (th) {
                            th->set_subject(subjectEdit->text());
                            th->set_university(universityEdit->text());
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


        resourcesTable->setCellWidget(row, 6, actionWidget);
        row++;

    }



    resourcesTable->setColumnWidth(0, 100);
    resourcesTable->setColumnWidth(1, 50);
    resourcesTable->setColumnWidth(2, 70);
    resourcesTable->setColumnWidth(3, 100);
    resourcesTable->setColumnWidth(4, 100);
    resourcesTable->setColumnWidth(5, 100);
    resourcesTable->setColumnWidth(6, 137);


    resourcesTable->setAlternatingRowColors(true);
    resourcesTable->horizontalHeader()->setStretchLastSection(false);
    resourcesTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    resourcesTable->setSelectionMode(QAbstractItemView::NoSelection);
    resourcesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    resourcesTable->setShowGrid(false);
    resourcesTable->verticalHeader()->setVisible(false);
    resourcesTable->setStyleSheet(R"(
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
        for (int i = 0; i < resourcesTable->rowCount(); ++i) {
            bool match = false;
            for (int j = 0; j < 6; ++j) {
                QTableWidgetItem* item = resourcesTable->item(i, j);
                if (item && item->text().toLower().contains(keyword)) {
                    match = true;
                    break;
                }
            }
            resourcesTable->setRowHidden(i, !match);
        }
    });


    allMainLayout->addWidget(topBarWidget);
    allMainLayout->addWidget(resourcesTitle);
    allMainLayout->addWidget(resourcesTable);
}
