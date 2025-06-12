#include "adminloans.h"
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

AdminLoansWindow::AdminLoansWindow(Library* library,QWidget* parent) : QFrame(parent) {

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




    QVBoxLayout* allMainLayout = new QVBoxLayout(this);
    allMainLayout->setContentsMargins(16, 16, 16, 16);
    allMainLayout->setSpacing(16); // reduced spacing

    QLabel* loansTitle = new QLabel("Loans");
    loansTitle->setStyleSheet("font-size: 18px; font-weight: bold; color: #1e293b;");




    QTableWidget* loansTable = new QTableWidget();
    loansTable->setColumnCount(7);
    loansTable->setRowCount(library_loans.size()); // Set correct row count

    loansTable->setHorizontalHeaderLabels({ "Title", "Type","loan ID", "Due Date", "Status","User",""});


    for(int i = 0; i < loansTable->columnCount(); i++) {
        QTableWidgetItem* header = loansTable->horizontalHeaderItem(i);
        if(header) {
            header->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        }
    }

    int row = 0;

    for(Loan* loan : library_loans) {

        QString username = loan->get_user()->get_username();









            QTableWidgetItem* titleItem = new QTableWidgetItem(loan->get_resource()->get_title());
            titleItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            loansTable->setItem(row, 0, titleItem);


            QTableWidgetItem* typeItem = new QTableWidgetItem(loan->get_resource()->resource_type());
            typeItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            loansTable->setItem(row, 1, typeItem);

            QTableWidgetItem* residItem = new QTableWidgetItem(QString::number(loan->get_loan_id()));
            residItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            loansTable->setItem(row, 2, residItem);


            QTableWidgetItem* dueDateItem = new QTableWidgetItem(loan->due_date().toString("yyyy-MM-dd"));
            dueDateItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            loansTable->setItem(row, 3, dueDateItem);


            int days_remaining = QDate::currentDate().daysTo(loan->due_date());


            QString status;
            if (loan->is_over_due()) {
                status = "Overdue";
            } else if (days_remaining >= 0 && days_remaining < 3) {

                status = "Due Soon";
            }
            else status = "Active";
            QTableWidgetItem* statusItem = new QTableWidgetItem(status);
            statusItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            loansTable->setItem(row, 4, statusItem);

            QTableWidgetItem* userItem = new QTableWidgetItem(username);
            userItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            loansTable->setItem(row, 5, userItem);


            QPushButton* notifyBtn = new QPushButton("Notify");


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



            notifyBtn->setStyleSheet(btnStyle1);

            connect(notifyBtn,&QPushButton::clicked,[=](){
                if(status == "Due Soon"){
                    QString content = "Your Loan for " + loan->get_resource()->get_title() + " is Due Soon !!";
                    Notification* notif = new Notification(content,loan->get_user());
                    library->addNotification(notif);
                    library->saveToJson("C:/Users/HP/Documents/LBMS/build/Desktop_Qt_6_9_1_MinGW_64_bit-Debug/data.json");
                    notifyBtn->deleteLater();
                }
                else if(status == "Overdue"){
                    QString content = "You are Late,Your loan is expired , You need to return " + loan->get_resource()->get_title() + "as soon as possible";
                    Notification* notif = new Notification(content,loan->get_user());
                    library->addNotification(notif);
                    library->saveToJson("C:/Users/HP/Documents/LBMS/build/Desktop_Qt_6_9_1_MinGW_64_bit-Debug/data.json");
                    notifyBtn->deleteLater();
                }
            });


            QWidget* actionWidget = new QWidget();
            QHBoxLayout* actionLayout = new QHBoxLayout(actionWidget);
            actionLayout->setContentsMargins(4, 4, 4, 4);
            actionLayout->setSpacing(6);
            if(status != "Active"){
            actionLayout->addWidget(notifyBtn);
            }

            if(loan->get_number_of_remaining_days() <3 || loan->is_over_due()){
            loansTable->setCellWidget(row, 6, actionWidget);
            }


            loansTable->setRowHeight(row, 44);







            row++;
        }



    loansTable->setColumnWidth(0, 170);
    loansTable->setColumnWidth(1, 75);
    loansTable->setColumnWidth(2, 60);
    loansTable->setColumnWidth(3, 110);
    loansTable->setColumnWidth(4, 75);
    loansTable->setColumnWidth(5, 85);
    loansTable->setColumnWidth(6, 90);


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
