#include "searchresources.h"
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
#include <QDialog>
#include <QDialogButtonBox>
#include <QSpinBox>

SearchResources::SearchResources(Library* library, Student *student, QWidget* parent) : QFrame(parent) {

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
    allMainLayout->setSpacing(16);
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

    topBarLayout->addWidget(searchBar);

    topBarLayout->addWidget(search);
    topBarLayout->addStretch();
    topBarLayout->addWidget(profilePic);

    QWidget* topBarWidget = new QWidget();
    topBarWidget->setLayout(topBarLayout);





    QVector<Resource*> library_resources = library->getResources();

    QLabel* resourcesTitle = new QLabel("Resources");
    resourcesTitle->setStyleSheet("font-size: 18px; font-weight: bold; color: #1e293b;");



    QTableWidget* resourcesTable = new QTableWidget();
    resourcesTable->setColumnCount(7);
    resourcesTable->setRowCount(library_resources.size());

    resourcesTable->setHorizontalHeaderLabels({ "Name", "Type", "availability", "category", "Author","published","Actions" });

    for(int i = 0; i < resourcesTable->columnCount(); i++) {
        QTableWidgetItem* header = resourcesTable->horizontalHeaderItem(i);
        if(header) {
            header->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        }
    }

    int row = 0;


    for(Resource* res : library_resources) {

            QTableWidgetItem* nameItem = new QTableWidgetItem(res->get_title());

            nameItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            resourcesTable->setItem(row, 0, nameItem);

            QTableWidgetItem* typeItem = new QTableWidgetItem(res->resource_type());
            typeItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            resourcesTable->setItem(row, 1, typeItem);

            QTableWidgetItem* availableItem = new QTableWidgetItem(res->is_available() ? "Available" : "Taken");

            availableItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            resourcesTable->setItem(row, 2, availableItem);


            QTableWidgetItem* categoryItem = new QTableWidgetItem(res->get_category());
            categoryItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            resourcesTable->setItem(row, 3, categoryItem);


            QTableWidgetItem* authorItem = new QTableWidgetItem(res->get_author());
            authorItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            resourcesTable->setItem(row, 4, authorItem);

            QTableWidgetItem* dateOfPublicationItem = new QTableWidgetItem(res->get_date_of_publication().toString("yyyy-MM-dd"));
            dateOfPublicationItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            resourcesTable->setItem(row, 5, dateOfPublicationItem);




            resourcesTable->setRowHeight(row, 70);

            QPushButton* reserveBtn = new QPushButton("Reserve");
            QPushButton* loanBtn = new QPushButton("loan");

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

            reserveBtn->setStyleSheet(btnStyle1);
            loanBtn->setStyleSheet(btnStyle2);

            QWidget* actionWidget = new QWidget();
            QHBoxLayout* actionLayout = new QHBoxLayout(actionWidget);
            actionLayout->setContentsMargins(4, 4, 4, 4);
            actionLayout->setSpacing(6);

            connect(loanBtn,&QPushButton::clicked,[=](){
                QDialog dialog(loanBtn);
                dialog.setWindowTitle("Choose number of days");
                QVBoxLayout layout(&dialog);
                QSpinBox spinBox;
                spinBox.setRange(3,21);
                spinBox.setValue(7);
                layout.addWidget(new QLabel("Max Days is 21"));
                layout.addWidget(&spinBox);
                QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
                layout.addWidget(&buttonBox);
                connect(&buttonBox,&QDialogButtonBox::accepted,&dialog,&QDialog::accept);
                connect(&buttonBox,&QDialogButtonBox::rejected,&dialog,&QDialog::reject);
                if(dialog.exec()==QDialog::Accepted){
                    int selectedDays = spinBox.value();
                    res->set_availability(false);
                    library->addLoan(new Loan(selectedDays,res,student,library));

                    library->saveToJson("C:/Users/HP/Documents/LBMS/build/Desktop_Qt_6_9_1_MinGW_64_bit-Debug/data.json");



                    loanBtn->deleteLater();
                }


            });



            connect(reserveBtn,&QPushButton::clicked,[=](){
                res->add_reserving_user(student);
                library->saveToJson("C:/Users/HP/Documents/LBMS/build/Desktop_Qt_6_9_1_MinGW_64_bit-Debug/data.json");
                reserveBtn->deleteLater();
            });

            bool user_already_reserved = false;
            for(User* user: res->get_user_reserved()){
                if(user->get_ID() == student->get_ID()){
                    user_already_reserved = true;
                    break;
                }
            }

            bool user_already_take_res = false;

            for(Loan* loan: library->getLoans()){
                if(loan->get_user()->get_ID() == student->get_ID() && loan->get_resource()->get_res_id() == res->get_res_id()){
                    user_already_take_res = true;
                    break;
                }
            }




            if(res->is_available()) actionLayout->addWidget(loanBtn);
            else if(!user_already_reserved && !user_already_take_res && res->get_user_reserved().size() < 5) actionLayout->addWidget(reserveBtn);
            else if(res->get_user_reserved().size() == 5) actionLayout->addWidget(new QLabel("full"));


            resourcesTable->setCellWidget(row, 6, actionWidget);
            row++;

        }


    resourcesTable->setColumnWidth(0, 100);
    resourcesTable->setColumnWidth(1, 75);
    resourcesTable->setColumnWidth(2, 75);
    resourcesTable->setColumnWidth(3, 100);
    resourcesTable->setColumnWidth(4, 100);
    resourcesTable->setColumnWidth(5, 100);
    resourcesTable->setColumnWidth(6, 100);

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
            for (int j = 0; j < 6; ++j) { // Ignore actions column
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
