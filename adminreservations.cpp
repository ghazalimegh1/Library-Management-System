#include "adminreservations.h"
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

AdminReservationsWindow::AdminReservationsWindow(Library* library,QWidget* parent) : QFrame(parent) {

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




    QVBoxLayout* allMainLayout = new QVBoxLayout(this);
    allMainLayout->setContentsMargins(16, 16, 16, 16);
    allMainLayout->setSpacing(16);

    QLabel* reservationsTitle = new QLabel("Reservations");
    reservationsTitle->setStyleSheet("font-size: 18px; font-weight: bold; color: #1e293b;");




    QTableWidget* reservationsTable = new QTableWidget();
    reservationsTable->setColumnCount(6);
    reservationsTable->setRowCount(library_reservations.size()); // Set correct row count

    reservationsTable->setHorizontalHeaderLabels({ "Title", "Type","reservation ID", "Status","User",""});


    for(int i = 0; i < reservationsTable->columnCount(); i++) {
        QTableWidgetItem* header = reservationsTable->horizontalHeaderItem(i);
        if(header) {
            header->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        }
    }

    int row = 0;

    for(Reservation* reservation : library_reservations) {

        QString username = reservation->get_user()->get_username();









        QTableWidgetItem* titleItem = new QTableWidgetItem(reservation->get_resource()->get_title());
        titleItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        reservationsTable->setItem(row, 0, titleItem);


        QTableWidgetItem* typeItem = new QTableWidgetItem(reservation->get_resource()->resource_type());
        typeItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        reservationsTable->setItem(row, 1, typeItem);

        QTableWidgetItem* residItem = new QTableWidgetItem(QString::number(reservation->get_reservation_id()));
        residItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        reservationsTable->setItem(row, 2, residItem);






        QString status = reservation->get_resource()->is_available() ? "Resource returned" : "Waiting...";
        QTableWidgetItem* statusItem = new QTableWidgetItem(status);
        statusItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        reservationsTable->setItem(row, 3, statusItem);

        QTableWidgetItem* userItem = new QTableWidgetItem(username);
        userItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        reservationsTable->setItem(row, 4, userItem);



        reservationsTable->setRowHeight(row, 44);


        row++;
    }



    reservationsTable->setColumnWidth(0, 170);
    reservationsTable->setColumnWidth(1, 100);
    reservationsTable->setColumnWidth(2, 100);
    reservationsTable->setColumnWidth(3, 100);
    reservationsTable->setColumnWidth(4, 80);




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
