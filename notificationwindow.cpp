#include "notificationwindow.h"
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
#include <QListWidget>
#include <QScrollArea>

NotificationWindow::NotificationWindow(User* user, Library* library): user(user),library(library) {
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
    QVector<Notification*> library_notifications = library->getNotifications();
    int userNotificationCount = 0;
    for(Notification* notif: library_notifications){
        if(notif->get_user()->get_ID() == user->get_ID()) userNotificationCount++;
    }



    QVBoxLayout* allMainLayout = new QVBoxLayout(this);
    allMainLayout->setContentsMargins(16, 16, 16, 16);
    allMainLayout->setSpacing(16); //

    QLabel* notificationTitle = new QLabel("My Notifications");
    notificationTitle->setStyleSheet("font-size: 18px; font-weight: bold; color: #1e293b;");

    allMainLayout->addWidget(notificationTitle);

    QTableWidget* notificationTable = new QTableWidget();
    notificationTable->setColumnCount(2);
    notificationTable->setRowCount(userNotificationCount);

    notificationTable->setHorizontalHeaderLabels({"Notification",""});


    for(int i = 0; i < notificationTable->columnCount(); i++) {
        QTableWidgetItem* header = notificationTable->horizontalHeaderItem(i);
        if(header) {
            header->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        }
    }

    int row = 0;

    for(Notification* notif : library_notifications) {

        if(notif->get_user()->get_ID() == user->get_ID()) {



            QTableWidgetItem* contentItem = new QTableWidgetItem(notif->get_notification_content());
            contentItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            notificationTable->setItem(row, 0, contentItem);




            notificationTable->setRowHeight(row, 44);

            QPushButton* okBtn = new QPushButton("OK");


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
            connect(okBtn, &QPushButton::clicked, [=]() {
                if (!notif || !library || !okBtn) return;

                library->notifications.erase(
                    std::remove(library->notifications.begin(), library->notifications.end(), notif),
                    library->notifications.end()
                    );

                library->saveToJson("C:/Users/HP/Documents/LBMS/build/Desktop_Qt_6_9_1_MinGW_64_bit-Debug/data.json");

                int rowToRemove = notificationTable->indexAt(okBtn->parentWidget()->pos()).row();
                notificationTable->removeRow(rowToRemove);
            });



            okBtn->setStyleSheet(btnStyle1);


            QWidget* actionWidget = new QWidget();
            QHBoxLayout* actionLayout = new QHBoxLayout(actionWidget);
            actionLayout->setContentsMargins(4, 4, 4, 4);
            actionLayout->setSpacing(6);
            actionLayout->addWidget(okBtn);


            notificationTable->setCellWidget(row, 1, actionWidget);
            row++;
        }
    }

    notificationTable->setColumnWidth(0, 570);
    notificationTable->setColumnWidth(1, 96);


    notificationTable->setAlternatingRowColors(true);
    notificationTable->horizontalHeader()->setStretchLastSection(false);
    notificationTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    notificationTable->setSelectionMode(QAbstractItemView::NoSelection);
    notificationTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    notificationTable->setShowGrid(false);
    notificationTable->verticalHeader()->setVisible(false);
    notificationTable->setStyleSheet(R"(
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

    allMainLayout->addWidget(notificationTable);


}
