#include "myreservationwindow.h"
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

MyReservationWindow::MyReservationWindow(Student* student,Library* library,QWidget* parent) : QFrame(parent) {

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

    QVector<Reservation*> library_reservations = library->getReservations();


    int studentReservationCount = 0;
    for(Reservation* reservation : library_reservations) {
        if(reservation->get_user()->get_ID() == student->get_ID()) {
            studentReservationCount++;
        }
    }

    QVBoxLayout* allMainLayout = new QVBoxLayout(this);
    allMainLayout->setContentsMargins(16, 16, 16, 16);
    allMainLayout->setSpacing(16);

    QLabel* reservationsTitle = new QLabel("My Reservations");
    reservationsTitle->setStyleSheet("font-size: 18px; font-weight: bold; color: #1e293b;");




    QTableWidget* reservationsTable = new QTableWidget();
    reservationsTable->setColumnCount(4);
    reservationsTable->setRowCount(studentReservationCount);

    reservationsTable->setHorizontalHeaderLabels({ "Title", "Type","availability","Action" });


    for(int i = 0; i < reservationsTable->columnCount(); i++) {
        QTableWidgetItem* header = reservationsTable->horizontalHeaderItem(i);
        if(header) {
            header->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        }
    }

    int row = 0;

    for(Reservation* reservation : library_reservations) {

        if(reservation->get_user()->get_ID() == student->get_ID()) {



            QTableWidgetItem* titleItem = new QTableWidgetItem(reservation->get_resource()->get_title());
            titleItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            reservationsTable->setItem(row, 0, titleItem);


            QTableWidgetItem* typeItem = new QTableWidgetItem(reservation->get_resource()->resource_type());
            typeItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            reservationsTable->setItem(row, 1, typeItem);





            QString status = reservation->get_resource()->is_available() ? "Available" : "Not Available";
            QTableWidgetItem* statusItem = new QTableWidgetItem(status);
            statusItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            reservationsTable->setItem(row, 2, statusItem);


            reservationsTable->setRowHeight(row, 44);


            QPushButton* cancelBtn = new QPushButton("Cancel");


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

            connect(cancelBtn,&QPushButton::clicked,[=](){
                library->removeReservation(reservation);
                library->saveToJson("C:/Users/HP/Documents/LBMS/build/Desktop_Qt_6_9_1_MinGW_64_bit-Debug/data.json");
                int rowToRemove = reservationsTable->indexAt(cancelBtn->parentWidget()->pos()).row();
                reservationsTable->removeRow(rowToRemove);
            });



            cancelBtn->setStyleSheet(btnStyle1);


            QWidget* actionWidget = new QWidget();
            QHBoxLayout* actionLayout = new QHBoxLayout(actionWidget);
            actionLayout->setContentsMargins(4, 4, 4, 4);
            actionLayout->setSpacing(6);
            actionLayout->addWidget(cancelBtn);


            reservationsTable->setCellWidget(row, 3, actionWidget);
            row++;
        }
    }


    reservationsTable->setColumnWidth(0, 267);
    reservationsTable->setColumnWidth(1, 200);
    reservationsTable->setColumnWidth(2, 100);
    reservationsTable->setColumnWidth(3, 100);



    reservationsTable->setAlternatingRowColors(true);
    reservationsTable->horizontalHeader()->setStretchLastSection(false);
    reservationsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    reservationsTable->setSelectionMode(QAbstractItemView::NoSelection);
    reservationsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    reservationsTable->setShowGrid(false);
    reservationsTable->verticalHeader()->setVisible(false);
    reservationsTable->setStyleSheet(R"(
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
    allMainLayout->addWidget(reservationsTitle);
    allMainLayout->addWidget(reservationsTable);


}
