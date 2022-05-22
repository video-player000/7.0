/****************************************************************************
** Meta object code from reading C++ file 'display.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../display.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'display.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Display_t {
    const uint offsetsAndSize[24];
    char stringdata0[135];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_Display_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_Display_t qt_meta_stringdata_Display = {
    {
QT_MOC_LITERAL(0, 7), // "Display"
QT_MOC_LITERAL(8, 19), // "slot_display_resize"
QT_MOC_LITERAL(28, 0), // ""
QT_MOC_LITERAL(29, 5), // "width"
QT_MOC_LITERAL(35, 6), // "height"
QT_MOC_LITERAL(42, 27), // "slot_display_console_resize"
QT_MOC_LITERAL(70, 6), // "ishide"
QT_MOC_LITERAL(77, 21), // "slot_display_setimage"
QT_MOC_LITERAL(99, 5), // "image"
QT_MOC_LITERAL(105, 10), // "paintEvent"
QT_MOC_LITERAL(116, 12), // "QPaintEvent*"
QT_MOC_LITERAL(129, 5) // "event"

    },
    "Display\0slot_display_resize\0\0width\0"
    "height\0slot_display_console_resize\0"
    "ishide\0slot_display_setimage\0image\0"
    "paintEvent\0QPaintEvent*\0event"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Display[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   38,    2, 0x0a,    1 /* Public */,
       5,    1,   43,    2, 0x0a,    4 /* Public */,
       7,    1,   46,    2, 0x0a,    6 /* Public */,
       9,    1,   49,    2, 0x0a,    8 /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void, QMetaType::QImage,    8,
    QMetaType::Void, 0x80000000 | 10,   11,

       0        // eod
};

void Display::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Display *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->slot_display_resize((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 1: _t->slot_display_console_resize((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 2: _t->slot_display_setimage((*reinterpret_cast< std::add_pointer_t<QImage>>(_a[1]))); break;
        case 3: _t->paintEvent((*reinterpret_cast< std::add_pointer_t<QPaintEvent*>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject Display::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_Display.offsetsAndSize,
    qt_meta_data_Display,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_Display_t
, QtPrivate::TypeAndForceComplete<Display, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QImage, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QPaintEvent *, std::false_type>


>,
    nullptr
} };


const QMetaObject *Display::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Display::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Display.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Display::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
