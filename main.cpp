#include "lbms.h"
#include "studenti_interface.h"
#include "newloginform.h"
#include <QApplication>
#include <QDebug>
#include "library.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Library ensia_library;
    QString path = "C:/Users/HP/Documents/LBMS/build/Desktop_Qt_6_9_1_MinGW_64_bit-Debug/data.json";
    bool is_loaded = ensia_library.loadFromJson(path);
    NewLoginForm login_form(&ensia_library);
    login_form.show();


    return a.exec();
}

