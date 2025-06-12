#include "loan.h"
#include <QDate>
#include <QString>
#include <QDebug>
#include "library.h"
#include "notification.h"

int Loan::number_of_loans = 0;

Loan::Loan(int days, Resource* resource, User* borrower, Library * library)
    : loan_id(++number_of_loans),
    number_of_days(days > 0 ? days : 14),
    res(resource),
    user(borrower),
    borrowDate(QDate::currentDate()),
    is_renewed(false) {
    notify_user(library);
}

Loan::Loan(const Loan* other)
    : loan_id(other->loan_id),
    number_of_days(other->number_of_days),
    res(other->res->clone()),
    user(other->user->clone()),
    borrowDate(other->borrowDate),
    is_renewed(other->is_renewed)
{
    number_of_loans++;
}


Loan::~Loan() {
    --number_of_loans;
    delete user;
    delete res;
}

void Loan::renew_loan() {
    if (can_renew()) {
        number_of_days += 7;
        is_renewed = true;
    }
}

bool Loan::is_over_due() const {
    return QDate::currentDate() > due_date();
}

void Loan::notify_user(Library* library) const {
    if(library == nullptr) return;
    if (is_over_due()) {
        QString content = "Warning: Your loan for resource  " + res->get_title() + " is overdue. Please return it as soon as possible.";
        Notification* notification = new Notification(content,this->get_user());
        library->addNotification(notification);

    }
    else if(get_number_of_remaining_days() < 3){
        QString content = "Still " + QString::number(get_number_of_remaining_days()) + "days for becoming overdue for resource " + res->get_title();
        Notification* notification = new Notification(content,this->get_user());
       library->addNotification(notification);
    }
}

QDate Loan::due_date() const {
    return borrowDate.addDays(number_of_days);
}

int Loan::get_number_of_remaining_days() const {
    return QDate::currentDate().daysTo(due_date());
}

int Loan::get_loan_id() const {
    return loan_id;
}

const QDate& Loan::get_borrow_date() const {
    return borrowDate;
}

const Resource* Loan::get_resource() const {
    return res;
}

const User* Loan::get_user() const {
    return user;
}

bool Loan::get_is_renewed() const {
    return is_renewed;
}

void Loan::set_is_renewed(bool renewed) {
    is_renewed = renewed;
}

void Loan::set_loan_id(int id) {
    loan_id = id;
}

void Loan::set_number_of_days(int days) {
    number_of_days = days;
}

int Loan::days_overdue() const {
    if (!is_over_due()) return 0;
    return due_date().daysTo(QDate::currentDate());
}

bool Loan::is_returned() const {
    return res->is_available();
}

void Loan::mark_returned() {
    res->set_availability(true);
}

bool Loan::can_renew() const {
    return !is_renewed && !is_over_due();
}

bool Loan::is_active() const {
    return !is_returned() && !is_over_due();
}


int Loan::get_total_loans(){
    return number_of_loans;
}

QJsonObject Loan::toJson() const {
    QJsonObject obj;
    obj["loan_id"] = loan_id;
    obj["number_of_days"] = number_of_days;
    obj["resource_id"] = res ? res->get_res_id() : -1;
    obj["user_id"] = user ? user->get_ID() : -1;
    obj["borrowDate"] = borrowDate.toString(Qt::ISODate);
    obj["is_renewed"] = is_renewed;
    obj["returned"] = is_returned();
    return obj;
}

void Loan::fromJson(const QJsonObject& obj) {
    loan_id = obj["loan_id"].toInt();
    number_of_days = obj["number_of_days"].toInt();

    borrowDate = QDate::fromString(obj["borrowDate"].toString(), Qt::ISODate);
    is_renewed = obj["is_renewed"].toBool();
    res->set_availability(obj["returned"].toBool());
}

void Loan::resolvePointers(const QList<Resource*>& resources, const QList<User*>& users) {
    for (Resource* r : resources) {
        if (r && r->get_res_id() == temp_res_id) {
            res = r;
            break;
        }
    }

    for (User* u : users) {
        if (u && u->get_ID() == temp_user_id) {
            user = u;
            break;
        }
    }

    if (!res || !user) {
        qWarning() << "⚠️ Could not resolve pointers for loan ID:" << loan_id;
    }
}

void Loan::set_borrow_date(QDate & b_date) {
    this->borrowDate = b_date;
}


Loan* Loan::fromJsonStatic(const QJsonObject& json) {
    int id = json["loan_id"].toInt();
    int resourceId = json["resource_id"].toInt();
    int userId = json["user_id"].toInt();
    int days = json["number_of_days"].toInt();
    QDate loanDate = QDate::fromString(json["borrowDate"].toString(), Qt::ISODate);
    bool isRenewed = json["is_renewed"].toBool();

    User* user = loadUserByIdFromComplexFile("data.json", userId);
    Resource* resource = loadResourceByIdFromComplexFile("data.json", resourceId);

    if (!user || !resource) {
        qWarning() << "❌ Failed to load Loan: user or resource not found.";
        return nullptr;
    }

    Loan* loan = new Loan(days, resource, user);
    loan->set_loan_id(id);
    loan->set_is_renewed(isRenewed);
    loan->set_borrow_date(loanDate);



    if (json.contains("returned") && json["returned"].toBool())
        resource->set_availability(true);
    else
        resource->set_availability(false);

    return loan;
}


