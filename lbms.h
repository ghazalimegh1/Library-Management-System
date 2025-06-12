#ifndef LBMS_H
#define LBMS_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class lbms;
}
QT_END_NAMESPACE

class lbms : public QMainWindow
{
    Q_OBJECT

public:
    lbms(QWidget *parent = nullptr);
    ~lbms();

private:
    Ui::lbms *ui;
};
#endif // LBMS_H
