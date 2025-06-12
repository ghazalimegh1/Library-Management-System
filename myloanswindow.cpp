#include "myloanswindow.h"
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

MyLoansWindow::MyLoansWindow(Student* student,Library* library,QWidget* parent) : QFrame(parent) {

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

    QVector<Loan*> library_loans = library->getLoans();


    int studentLoanCount = 0;
    for(Loan* loan : library_loans) {
        if(loan->get_user()->get_ID() == student->get_ID()) {
            studentLoanCount++;
        }
    }

    QVBoxLayout* allMainLayout = new QVBoxLayout(this);
    allMainLayout->setContentsMargins(16, 16, 16, 16);
    allMainLayout->setSpacing(16);

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
    allMainLayout->addWidget(loansTitle);
    allMainLayout->addWidget(loansTable);


}
