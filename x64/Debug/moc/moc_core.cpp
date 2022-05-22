/****************************************************************************
** Meta object code from reading C++ file 'core.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../core.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'core.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Core_t {
    const uint offsetsAndSize[40];
    char stringdata0[272];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_Core_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_Core_t qt_meta_stringdata_Core = {
    {
QT_MOC_LITERAL(0, 4), // "Core"
QT_MOC_LITERAL(5, 20), // "signal_core_duration"
QT_MOC_LITERAL(26, 0), // ""
QT_MOC_LITERAL(27, 8), // "duration"
QT_MOC_LITERAL(36, 17), // "signal_core_clock"
QT_MOC_LITERAL(54, 5), // "clock"
QT_MOC_LITERAL(60, 28), // "signal_core_getimage_display"
QT_MOC_LITERAL(89, 5), // "image"
QT_MOC_LITERAL(95, 31), // "signal_core_getimage_seekwidget"
QT_MOC_LITERAL(127, 15), // "slot_core_pause"
QT_MOC_LITERAL(143, 5), // "pause"
QT_MOC_LITERAL(149, 16), // "slot_core_volume"
QT_MOC_LITERAL(166, 6), // "volume"
QT_MOC_LITERAL(173, 14), // "slot_core_seek"
QT_MOC_LITERAL(188, 7), // "int64_t"
QT_MOC_LITERAL(196, 9), // "timestamp"
QT_MOC_LITERAL(206, 14), // "slot_core_skip"
QT_MOC_LITERAL(221, 15), // "slot_core_upend"
QT_MOC_LITERAL(237, 11), // "upend_speed"
QT_MOC_LITERAL(249, 22) // "slot_core_upend_cancel"

    },
    "Core\0signal_core_duration\0\0duration\0"
    "signal_core_clock\0clock\0"
    "signal_core_getimage_display\0image\0"
    "signal_core_getimage_seekwidget\0"
    "slot_core_pause\0pause\0slot_core_volume\0"
    "volume\0slot_core_seek\0int64_t\0timestamp\0"
    "slot_core_skip\0slot_core_upend\0"
    "upend_speed\0slot_core_upend_cancel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Core[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   74,    2, 0x06,    1 /* Public */,
       4,    1,   77,    2, 0x06,    3 /* Public */,
       6,    1,   80,    2, 0x06,    5 /* Public */,
       8,    1,   83,    2, 0x06,    7 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       9,    1,   86,    2, 0x0a,    9 /* Public */,
      11,    1,   89,    2, 0x0a,   11 /* Public */,
      13,    1,   92,    2, 0x0a,   13 /* Public */,
      16,    0,   95,    2, 0x0a,   15 /* Public */,
      17,    1,   96,    2, 0x0a,   16 /* Public */,
      19,    0,   99,    2, 0x0a,   18 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    5,
    QMetaType::Void, QMetaType::QImage,    7,
    QMetaType::Void, QMetaType::QImage,    7,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,   18,
    QMetaType::Void,

       0        // eod
};

void Core::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Core *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->signal_core_duration((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 1: _t->signal_core_clock((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 2: _t->signal_core_getimage_display((*reinterpret_cast< std::add_pointer_t<QImage>>(_a[1]))); break;
        case 3: _t->signal_core_getimage_seekwidget((*reinterpret_cast< std::add_pointer_t<QImage>>(_a[1]))); break;
        case 4: _t->slot_core_pause((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 5: _t->slot_core_volume((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 6: _t->slot_core_seek((*reinterpret_cast< std::add_pointer_t<int64_t>>(_a[1]))); break;
        case 7: _t->slot_core_skip(); break;
        case 8: _t->slot_core_upend((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 9: _t->slot_core_upend_cancel(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Core::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Core::signal_core_duration)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Core::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Core::signal_core_clock)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Core::*)(QImage );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Core::signal_core_getimage_display)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Core::*)(QImage );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Core::signal_core_getimage_seekwidget)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject Core::staticMetaObject = { {
    QMetaObject::SuperData::link<QThread::staticMetaObject>(),
    qt_meta_stringdata_Core.offsetsAndSize,
    qt_meta_data_Core,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_Core_t
, QtPrivate::TypeAndForceComplete<Core, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QImage, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QImage, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int64_t, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *Core::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Core::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Core.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int Core::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void Core::signal_core_duration(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Core::signal_core_clock(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Core::signal_core_getimage_display(QImage _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Core::signal_core_getimage_seekwidget(QImage _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
