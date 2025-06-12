/****************************************************************************
** Meta object code from reading C++ file 'sidebar.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../sidebar.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sidebar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN7SidebarE_t {};
} // unnamed namespace

template <> constexpr inline auto Sidebar::qt_create_metaobjectdata<qt_meta_tag_ZN7SidebarE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Sidebar",
        "showDashboard",
        "",
        "showSearchResources",
        "showMyLoans",
        "showMyReservations",
        "showMyNotifications",
        "showMyUsers",
        "logout"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'showDashboard'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'showSearchResources'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'showMyLoans'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'showMyReservations'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'showMyNotifications'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'showMyUsers'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'logout'
        QtMocHelpers::SignalData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<Sidebar, qt_meta_tag_ZN7SidebarE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Sidebar::staticMetaObject = { {
    QMetaObject::SuperData::link<QFrame::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7SidebarE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7SidebarE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN7SidebarE_t>.metaTypes,
    nullptr
} };

void Sidebar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Sidebar *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->showDashboard(); break;
        case 1: _t->showSearchResources(); break;
        case 2: _t->showMyLoans(); break;
        case 3: _t->showMyReservations(); break;
        case 4: _t->showMyNotifications(); break;
        case 5: _t->showMyUsers(); break;
        case 6: _t->logout(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (Sidebar::*)()>(_a, &Sidebar::showDashboard, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (Sidebar::*)()>(_a, &Sidebar::showSearchResources, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (Sidebar::*)()>(_a, &Sidebar::showMyLoans, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (Sidebar::*)()>(_a, &Sidebar::showMyReservations, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (Sidebar::*)()>(_a, &Sidebar::showMyNotifications, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (Sidebar::*)()>(_a, &Sidebar::showMyUsers, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (Sidebar::*)()>(_a, &Sidebar::logout, 6))
            return;
    }
}

const QMetaObject *Sidebar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Sidebar::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7SidebarE_t>.strings))
        return static_cast<void*>(this);
    return QFrame::qt_metacast(_clname);
}

int Sidebar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void Sidebar::showDashboard()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Sidebar::showSearchResources()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Sidebar::showMyLoans()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Sidebar::showMyReservations()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Sidebar::showMyNotifications()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void Sidebar::showMyUsers()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void Sidebar::logout()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
