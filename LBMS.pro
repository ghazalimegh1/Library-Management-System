QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin.cpp \
    admindashboard.cpp \
    admininterfaces.cpp \
    adminloans.cpp \
    adminreservations.cpp \
    adminsearchresources.cpp \
    adminusermanagement.cpp \
    article.cpp \
    book.cpp \
    digital_content.cpp \
    library.cpp \
    loan.cpp \
    main.cpp \
    lbms.cpp \
    maincontent.cpp \
    myloanswindow.cpp \
    myreservationwindow.cpp \
    newloginform.cpp \
    notification.cpp \
    notificationwindow.cpp \
    reservation.cpp \
    resource.cpp \
    searchresources.cpp \
    sidebar.cpp \
    student.cpp \
    studenti_interface.cpp \
    thesis.cpp \
    user.cpp

HEADERS += \
    admin.h \
    admindashboard.h \
    admininterfaces.h \
    adminloans.h \
    adminreservations.h \
    adminsearchresources.h \
    adminusermanagement.h \
    article.h \
    book.h \
    digital_content.h \
    lbms.h \
    library.h \
    loan.h \
    maincontent.h \
    myloanswindow.h \
    myreservationwindow.h \
    newloginform.h \
    notification.h \
    notificationwindow.h \
    reservation.h \
    resource.h \
    searchresources.h \
    sidebar.h \
    student.h \
    studenti_interface.h \
    thesis.h \
    user.h

FORMS += \
    lbms.ui \
    studenti_interface.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
