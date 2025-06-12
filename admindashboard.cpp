#include "admindashboard.h"
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
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>


AdminDashboard::AdminDashboard(Admin* admin, Library* library, QWidget* parent)
    : QFrame(parent) {
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

    QVector<User*> library_users = library->getUsers();
    QVector<Resource*> library_resources = library->getResources();
    QVector<Reservation*> library_reservations = library->getReservations();
    QVector<Loan*> library_loans = library->getLoans();

    int number_of_reservation = library_reservations.size();
    int number_of_resources = library_resources.size();
    int number_of_users = library_users.size();
    int number_of_loans = library_loans.size();

    // Count resources by type
    int bookCount = 0, digitalCount = 0, thesisCount = 0, articleCount = 0;
    for (Resource* res : library_resources) {
        QString type = res->resource_type();
        if (type == "Book") bookCount++;
        else if (type == "Digital Content") digitalCount++;
        else if (type == "Thesis") thesisCount++;
        else if (type == "Article") articleCount++;
    }

    QVBoxLayout* allMainLayout = new QVBoxLayout(this);
    allMainLayout->setContentsMargins(10, 10, 10, 10);
    allMainLayout->setSpacing(8);

    // --- Top Bar ---
    QHBoxLayout* topBarLayout = new QHBoxLayout();
    topBarLayout->setSpacing(6);

    QLabel* profilePic = new QLabel();
    QPixmap profilePixmap("C:/Users/HP/Downloads/profile.png");
    profilePic->setPixmap(profilePixmap.scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    profilePic->setFixedSize(32, 32);

    topBarLayout->addStretch();
    topBarLayout->addWidget(new QLabel(admin->get_username()));
    topBarLayout->addWidget(profilePic);

    QWidget* topBarWidget = new QWidget();
    topBarWidget->setLayout(topBarLayout);

    QLabel* mainTitle = new QLabel("Admin Interface");
    mainTitle->setStyleSheet("font-size: 27px; font-weight: bold; color: #1e293b;");

    QLabel* welcomeLabel = new QLabel("Welcome back " + admin->get_username());
    welcomeLabel->setStyleSheet("font-size: 20px; color: #475569;");

    // --- Bar Chart ---
    QBarSet* set = new QBarSet("Resources");
    *set << bookCount << digitalCount << thesisCount << articleCount;


    set->setColor(QColor("#3b82f6")); // Blue

    QBarSeries* series = new QBarSeries();
    series->append(set);
    series->setLabelsVisible(true);
    series->setLabelsFormat("@value");

    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Library Resource Types");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->hide();
    chart->setBackgroundBrush(Qt::transparent);

    QStringList categories;
    categories << "Books" << "Digital" << "Thesis" << "Articles";

    QBarCategoryAxis* axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    int maxCount = std::max({bookCount, digitalCount, thesisCount, articleCount});
    QValueAxis* axisY = new QValueAxis();
    axisY->setRange(0, maxCount + 1);
    axisY->setTickCount(qMin(maxCount + 2, 6));
    axisY->setLabelFormat("%d");
    axisY->setTitleText("Count");
    axisY->setLabelsColor(QColor("#475569"));
    axisY->setLinePenColor(QColor("#94a3b8"));
    axisY->setGridLineColor(QColor("#e2e8f0"));

    axisY->setLabelsFont(QFont("Arial", 10));
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setFixedHeight(250);
    chartView->setStyleSheet("background: transparent;");

    // --- Summary Cards ---
    QHBoxLayout* cardsLayout = new QHBoxLayout();
    cardsLayout->setSpacing(10);

    struct CardData {
        QString icon;
        int value;
        QString label;

        CardData(const QString& i, const int& v, const QString& l)
            : icon(i), value(v), label(l) {}
    };

    QList<CardData> cards = {
        CardData("👤", number_of_users, "Users"),
        CardData("📚", number_of_resources, "Resources"),
        CardData("📅", number_of_loans, "Loans"),
        CardData("🔖", number_of_reservation, "Reservations")
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

    // --- Final Assembly ---
    allMainLayout->addWidget(topBarWidget);
    allMainLayout->addWidget(mainTitle);
    allMainLayout->addWidget(welcomeLabel);
    allMainLayout->addWidget(chartView);     // 👈 Bar chart inserted here
    allMainLayout->addWidget(cardsWidget);
}

