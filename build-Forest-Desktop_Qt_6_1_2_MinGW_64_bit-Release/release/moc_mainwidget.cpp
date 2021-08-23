/****************************************************************************
** Meta object code from reading C++ file 'mainwidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.1.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Forest/mainwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.1.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWidget_t {
    const uint offsetsAndSize[40];
    char stringdata0[221];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_MainWidget_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_MainWidget_t qt_meta_stringdata_MainWidget = {
    {
QT_MOC_LITERAL(0, 10), // "MainWidget"
QT_MOC_LITERAL(11, 10), // "Timer_tick"
QT_MOC_LITERAL(22, 0), // ""
QT_MOC_LITERAL(23, 16), // "Timer_human_tick"
QT_MOC_LITERAL(40, 10), // "Normalmode"
QT_MOC_LITERAL(51, 5), // "value"
QT_MOC_LITERAL(57, 9), // "Speedmode"
QT_MOC_LITERAL(67, 9), // "Pausemode"
QT_MOC_LITERAL(77, 16), // "Normalmode_human"
QT_MOC_LITERAL(94, 15), // "Pausemode_human"
QT_MOC_LITERAL(110, 10), // "Stop_human"
QT_MOC_LITERAL(121, 10), // "Print_info"
QT_MOC_LITERAL(132, 3), // "num"
QT_MOC_LITERAL(136, 4), // "type"
QT_MOC_LITERAL(141, 8), // "f_update"
QT_MOC_LITERAL(150, 16), // "Print_human_info"
QT_MOC_LITERAL(167, 7), // "f_clear"
QT_MOC_LITERAL(175, 18), // "Print_weather_info"
QT_MOC_LITERAL(194, 17), // "Print_forest_info"
QT_MOC_LITERAL(212, 8) // "Show_pic"

    },
    "MainWidget\0Timer_tick\0\0Timer_human_tick\0"
    "Normalmode\0value\0Speedmode\0Pausemode\0"
    "Normalmode_human\0Pausemode_human\0"
    "Stop_human\0Print_info\0num\0type\0f_update\0"
    "Print_human_info\0f_clear\0Print_weather_info\0"
    "Print_forest_info\0Show_pic"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWidget[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   92,    2, 0x0a,    0 /* Public */,
       3,    0,   93,    2, 0x0a,    1 /* Public */,
       4,    1,   94,    2, 0x0a,    2 /* Public */,
       6,    1,   97,    2, 0x0a,    4 /* Public */,
       7,    1,  100,    2, 0x0a,    6 /* Public */,
       8,    1,  103,    2, 0x0a,    8 /* Public */,
       9,    1,  106,    2, 0x0a,   10 /* Public */,
      10,    1,  109,    2, 0x0a,   12 /* Public */,
      11,    3,  112,    2, 0x0a,   14 /* Public */,
      15,    1,  119,    2, 0x0a,   18 /* Public */,
      17,    0,  122,    2, 0x0a,   20 /* Public */,
      18,    0,  123,    2, 0x0a,   21 /* Public */,
      19,    2,  124,    2, 0x0a,   22 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   12,   13,   14,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   12,   13,

       0        // eod
};

void MainWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->Timer_tick(); break;
        case 1: _t->Timer_human_tick(); break;
        case 2: _t->Normalmode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->Speedmode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->Pausemode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->Normalmode_human((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->Pausemode_human((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->Stop_human((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->Print_info((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 9: _t->Print_human_info((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->Print_weather_info(); break;
        case 11: _t->Print_forest_info(); break;
        case 12: _t->Show_pic((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_MainWidget.offsetsAndSize,
    qt_meta_data_MainWidget,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_MainWidget_t

, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>


>,
    nullptr
} };


const QMetaObject *MainWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int MainWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
