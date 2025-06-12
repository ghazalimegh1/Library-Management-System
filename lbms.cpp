#include "lbms.h"
#include "ui_lbms.h"

lbms::lbms(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::lbms)
{
    ui->setupUi(this);
}

lbms::~lbms()
{
    delete ui;
}
