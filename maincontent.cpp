#include "maincontent.h"
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
#include <QMessageBox>

MainContent::MainContent(Student* student,Library* library,QWidget* parent) : QFrame(parent) {
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
    QVector<Resource*> student_resources;
    QVector<Loan*> student_loans;
    QVector<Loan*> library_loans = library->getLoans();

    int student_number_of_reservation = 0;
    for(Reservation* reservation: library->getReservations()){
        if(reservation->get_user()->get_ID() == student->get_ID()){
            student_number_of_reservation++;
        }
    }


    int student_notifications = 0;



    QVBoxLayout* allMainLayout = new QVBoxLayout(this);
    allMainLayout->setContentsMargins(16, 16, 16, 16);
    allMainLayout->setSpacing(16);

    // --- Top Bar ---
    QHBoxLayout* topBarLayout = new QHBoxLayout();
    topBarLayout->setSpacing(6);



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

    QLabel* profilePic = new QLabel();
    QPixmap profilePixmap("C:/Users/HP/Downloads/profile.png");
    profilePic->setPixmap(profilePixmap.scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    profilePic->setFixedSize(32, 32);

    QPushButton* search = new QPushButton("🔍");
    search->setStyleSheet("width:13px;height:13px;font-size:13px;border-radius:10px;border-width: 1px;border-style: solid;border-color:black;background-color:white;text-align: center");


    topBarLayout->addWidget(searchBar);

    topBarLayout->addWidget(search);
    topBarLayout->addStretch();
    topBarLayout->addWidget(profilePic);

    QWidget* topBarWidget = new QWidget();
    topBarWidget->setLayout(topBarLayout);

    // --- Titles ---
    QLabel* mainTitle = new QLabel("Student Interface");
    mainTitle->setStyleSheet("font-size: 27px; font-weight: bold; color: #1e293b;");

    QLabel* welcomeLabel = new QLabel("Welcome back "+ student->get_username());
    welcomeLabel->setStyleSheet("font-size: 20px; color: #475569;");

    // --- Summary Cards ---
    QHBoxLayout* cardsLayout = new QHBoxLayout();
    cardsLayout->setSpacing(16);

    int studentLoanCount = 0;
    for(Loan* loan : library_loans) {
        if(loan->get_user()->get_ID() == student->get_ID()) {
            studentLoanCount++;
        }
    }

    struct CardData {
        QString icon;
        int value;
        QString label;

        CardData(const QString& i, const int& v, const QString& l)
            : icon(i), value(v), label(l) {}
    };

    QList<CardData> cards = {
        CardData("📚", studentLoanCount,"Loans"),
        CardData("📋", student_number_of_reservation, "Reservations"),
        CardData("🔔", student_notifications, "Notifications")
    };



    for (const CardData& data : cards) {
        QFrame* card = new QFrame();
        card->setFixedSize(150, 100);
        card->setStyleSheet(R"(
        QFrame {
            background-color: #f9f9f9;
            border: 1px solid #e2e8f0;
            border-radius: 16px;
        }
        QLabel {
            color: #334155;
        }
    )");

        QVBoxLayout* cardLayout = new QVBoxLayout(card);
        cardLayout->setAlignment(Qt::AlignCenter);
        cardLayout->setSpacing(6);

        QLabel* iconLabel = new QLabel(data.icon);
        iconLabel->setAlignment(Qt::AlignCenter);
        iconLabel->setStyleSheet("font-size: 24px;border: none");

        QLabel* valueLabel = new QLabel(QString::number(data.value));
        valueLabel->setAlignment(Qt::AlignCenter);
        valueLabel->setStyleSheet("font-size: 20px; font-weight: bold; color: #1e293b;border: none");

        QLabel* titleLabel = new QLabel(data.label);
        titleLabel->setAlignment(Qt::AlignCenter);
        titleLabel->setStyleSheet("font-size: 13px; color: #475569;border: none");

        cardLayout->addWidget(iconLabel);
        cardLayout->addWidget(valueLabel);
        cardLayout->addWidget(titleLabel);

        cardsLayout->addWidget(card);
    }

    QWidget* cardsWidget = new QWidget();
    cardsWidget->setLayout(cardsLayout);


    // --- My Loans Table ---
    QLabel* loansTitle = new QLabel("My Loans");
    loansTitle->setStyleSheet("font-size: 18px; font-weight: bold; color: #1e293b;");




    QTableWidget* loansTable = new QTableWidget();
    loansTable->setColumnCount(5);
    loansTable->setRowCount(studentLoanCount);

    loansTable->setHorizontalHeaderLabels({ "Title", "Type", "Due Date", "Status", "Actions" });


    for(int i = 0; i < loansTable->columnCount(); i++) {
        QTableWidgetItem* header = loansTable->horizontalHeaderItem(i);
        if(header) {
            header->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        }
    }

    int row = 0;

    for(Loan* loan : library_loans) {

        if(loan->get_user()->get_ID() == student->get_ID()) {



            QTableWidgetItem* titleItem = new QTableWidgetItem(loan->get_resource()->get_title());
            titleItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            loansTable->setItem(row, 0, titleItem);


            QTableWidgetItem* typeItem = new QTableWidgetItem(loan->get_resource()->resource_type());
            typeItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            loansTable->setItem(row, 1, typeItem);


            QTableWidgetItem* dueDateItem = new QTableWidgetItem(loan->due_date().toString("yyyy-MM-dd"));
            dueDateItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            loansTable->setItem(row, 2, dueDateItem);


            int days_remaining = QDate::currentDate().daysTo(loan->due_date());


            QString status;
            if (loan->is_over_due()) {
                status = "Overdue";
            } else if (days_remaining >= 0 && days_remaining < 3) {
                qDebug("do we get here?");
                status = "Due Soon";
            }else{
                status = "Active";
            }

            QTableWidgetItem* statusItem = new QTableWidgetItem(status);
            statusItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            loansTable->setItem(row, 3, statusItem);


            loansTable->setRowHeight(row, 44);


            QPushButton* returnBtn = new QPushButton("Return");
            QPushButton* renewBtn = new QPushButton("Renew");

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


            returnBtn->setStyleSheet(btnStyle1);
            renewBtn->setStyleSheet(btnStyle2);

            connect(renewBtn,&QPushButton::clicked,[=](){
                loan->renew_loan();
                library->saveToJson("C:/Users/HP/Documents/LBMS/build/Desktop_Qt_6_9_1_MinGW_64_bit-Debug/data.json");
                renewBtn->deleteLater();
                QMessageBox::information(nullptr,"Renew", "Loan has been renewed");

            });

            connect(returnBtn,&QPushButton::clicked,[=](){
                Resource* r;
                for(Resource* res: library->getResources()){
                    if(res->get_res_id() == loan->get_resource()->get_res_id()){
                        r = res;
                        break;
                    }
                }



                r->set_availability(true);
                if(r->get_user_reserved().size() > 0){
                    QString msg = "Your Resource \"" + r->get_title() + "\" is now available.";
                    Notification* notif = new Notification(msg,r->next_borrower());
                    library->addNotification(notif);
                    for(Reservation* reservation: library->getReservations()){
                        if(reservation->get_user()->get_ID() == notif->get_user()->get_ID() && r->get_res_id() == reservation->get_resource()->get_res_id()){
                            library->removeReservation(reservation);
                            break;
                        }
                    }
                }
                library->removeLoan(loan);
                library->saveToJson("C:/Users/HP/Documents/LBMS/build/Desktop_Qt_6_9_1_MinGW_64_bit-Debug/data.json");
                int rowToRemove = loansTable->indexAt(returnBtn->parentWidget()->pos()).row();
                loansTable->removeRow(rowToRemove);
            });


            QWidget* actionWidget = new QWidget();
            QHBoxLayout* actionLayout = new QHBoxLayout(actionWidget);
            actionLayout->setContentsMargins(4, 4, 4, 4);
            actionLayout->setSpacing(6);
            actionLayout->addWidget(returnBtn);

            if(loan->get_resource()->get_user_reserved().size() == 0 && loan->can_renew()){
                actionLayout->addWidget(renewBtn);
            }

            loansTable->setCellWidget(row, 4, actionWidget);
            row++;
        }
    }


    loansTable->setColumnWidth(0, 200);
    loansTable->setColumnWidth(1, 100);
    loansTable->setColumnWidth(2, 100);
    loansTable->setColumnWidth(3, 100);
    loansTable->setColumnWidth(4, 160);


    loansTable->setAlternatingRowColors(true);
    loansTable->horizontalHeader()->setStretchLastSection(false);
    loansTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    loansTable->setSelectionMode(QAbstractItemView::NoSelection);
    loansTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    loansTable->setShowGrid(false);
    loansTable->verticalHeader()->setVisible(false);
    loansTable->setStyleSheet(R"(
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


    allMainLayout->addWidget(topBarWidget);
    allMainLayout->addWidget(mainTitle);
    allMainLayout->addWidget(welcomeLabel);
    allMainLayout->addWidget(cardsWidget);
    allMainLayout->addWidget(loansTitle);
    allMainLayout->addWidget(loansTable);

    for(int i =0;i<student_resources.size();i++){
        delete student_resources[i];
        delete student_loans[i];

    }


}
