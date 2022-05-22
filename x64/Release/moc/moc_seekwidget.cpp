/****************************************************************************
** Meta object code from reading C++ file 'seekwidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../seekwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'seekwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Seekwidget_t {
    const uint offsetsAndSize[26];
    char stringdata0[162];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_Seekwidget_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_Seekwidget_t qt_meta_stringdata_Seekwidget = {
    {
QT_MOC_LITERAL(0, 10), // "Seekwidget"
QT_MOC_LITERAL(11, 22), // "slot_seekwidget_resize"
QT_MOC_LITERAL(34, 0), // ""
QT_MOC_LITERAL(35, 5), // "width"
QT_MOC_LITERAL(41, 6), // "height"
QT_MOC_LITERAL(48, 20), // "slot_seekwidget_show"
QT_MOC_LITERAL(69, 8), // "position"
QT_MOC_LITERAL(78, 20), // "slot_seekwidget_hide"
QT_MOC_LITERAL(99, 24), // "slot_seekwidget_setimage"
QT_MOC_LITERAL(124, 7), // "t_image"
QT_MOC_LITERAL(132, 10), // "paintEvent"
QT_MOC_LITERAL(143, 12), // "QPaintEvent*"
QT_MOC_LITERAL(156, 5) // "event"

    },
    "Seekwidget\0slot_seekwidget_resize\0\0"
    "width\0height\0slot_seekwidget_show\0"
    "position\0slot_seekwidget_hide\0"
    "slot_seekwidget_setimage\0t_image\0"
    "paintEvent\0QPaintEvent*\0event"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Seekwidget[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   44,    2, 0x0a,    1 /* Public */,
       5,    1,   49,    2, 0x0a,    4 /* Public */,
       7,    0,   52,    2, 0x0a,    6 /* Public */,
       8,    1,   53,    2, 0x0a,    7 /* Public */,
      10,    1,   56,    2, 0x0a,    9 /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::Double,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QImage,    9,
    QMetaType::Void, 0x80000000 | 11,   12,

       0        // eod
};

void Seekwidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Seekwidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->slot_seekwidget_resize((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 1: _t->slot_seekwidget_show((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 2: _t->slot_seekwidget_hide(); break;
        case 3: _t->slot_seekwidget_setimage((*reinterpret_cast< std::add_pointer_t<QImage>>(_a[1]))); break;
        case 4: _t->paintEvent((*reinterpret_cast< std::add_pointer_t<QPaintEvent*>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject Seekwidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_Seekwidget.offsetsAndSize,
    qt_meta_data_Seekwidget,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_Seekwidget_t
, QtPrivate::TypeAndForceComplete<Seekwidget, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QImage, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QPaintEvent *, std::false_type>


>,
    nullptr
} };


const QMetaObject *Seekwidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Seekwidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Seekwidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Seekwidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
