#ifndef LOAN_H
#define LOAN_H
#include "resource.h"
#include "user.h"
#include "library.h"
#include <QDate>
#include <QJsonObject>

class Library;

class Loan
{
private:
    int loan_id;
    int number_of_days;
    Resource* res;
    User* user;
    QDate borrowDate;
    bool is_renewed;
    static int number_of_loans;

public:
    Loan(int,Resource*,User*,Library* = nullptr);
    Loan(const Loan* other);
    ~Loan();
    void renew_loan();
    bool is_over_due() const;
    void notify_user(Library *library = nullptr) const;
    QDate due_date() const;
    int get_number_of_remaining_days() const;
    int get_loan_id() const;
    const QDate& get_borrow_date() const;
    const Resource* get_resource() const;
    const User* get_user() const;
    bool get_is_renewed() const;
    void set_is_renewed(bool);
    void set_loan_id(int);
    void set_number_of_days(int);
    void set_borrow_date(QDate&);
    int days_overdue() const;
    void mark_returned();
    bool is_returned() const;
    bool can_renew() const;
    bool is_active() const;
    static int get_total_loans();
    QJsonObject toJson() const;
    void fromJson(const QJsonObject& obj);
    void resolvePointers(const QList<Resource*>& resources, const QList<User*>& users);
    static Loan* fromJsonStatic(const QJsonObject& json);
    int temp_user_id = -1;
    int temp_res_id = -1;
};

#endif // LOAN_H
