/****************************************************************************
** Meta object code from reading C++ file 'paintlabel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MyLabel/paintlabel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'paintlabel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PaintLabel_t {
    QByteArrayData data[9];
    char stringdata0[82];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PaintLabel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PaintLabel_t qt_meta_stringdata_PaintLabel = {
    {
QT_MOC_LITERAL(0, 0, 10), // "PaintLabel"
QT_MOC_LITERAL(1, 11, 15), // "changeImageSize"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 4), // "size"
QT_MOC_LITERAL(4, 33, 8), // "addLabel"
QT_MOC_LITERAL(5, 42, 5), // "index"
QT_MOC_LITERAL(6, 48, 12), // "currentLabel"
QT_MOC_LITERAL(7, 61, 11), // "removeLabel"
QT_MOC_LITERAL(8, 73, 8) // "paintNow"

    },
    "PaintLabel\0changeImageSize\0\0size\0"
    "addLabel\0index\0currentLabel\0removeLabel\0"
    "paintNow"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PaintLabel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       4,    1,   42,    2, 0x06 /* Public */,
       6,    1,   45,    2, 0x06 /* Public */,
       7,    1,   48,    2, 0x06 /* Public */,
       8,    0,   51,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,

       0        // eod
};

void PaintLabel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PaintLabel *_t = static_cast<PaintLabel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changeImageSize((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 1: _t->addLabel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->currentLabel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->removeLabel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->paintNow(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (PaintLabel::*_t)(float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PaintLabel::changeImageSize)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (PaintLabel::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PaintLabel::addLabel)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (PaintLabel::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PaintLabel::currentLabel)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (PaintLabel::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PaintLabel::removeLabel)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (PaintLabel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PaintLabel::paintNow)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject PaintLabel::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_PaintLabel.data,
      qt_meta_data_PaintLabel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PaintLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PaintLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PaintLabel.stringdata0))
        return static_cast<void*>(const_cast< PaintLabel*>(this));
    return QLabel::qt_metacast(_clname);
}

int PaintLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void PaintLabel::changeImageSize(float _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PaintLabel::addLabel(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PaintLabel::currentLabel(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PaintLabel::removeLabel(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void PaintLabel::paintNow()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
