/****************************************************************************
** Meta object code from reading C++ file '2d_viewer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../2d_viewer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '2d_viewer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Viewer2D_t {
    QByteArrayData data[14];
    char stringdata[152];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Viewer2D_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Viewer2D_t qt_meta_stringdata_Viewer2D = {
    {
QT_MOC_LITERAL(0, 0, 8), // "Viewer2D"
QT_MOC_LITERAL(1, 9, 4), // "pick"
QT_MOC_LITERAL(2, 14, 0), // ""
QT_MOC_LITERAL(3, 15, 2), // "p0"
QT_MOC_LITERAL(4, 18, 2), // "p1"
QT_MOC_LITERAL(5, 21, 13), // "slot_set_data"
QT_MOC_LITERAL(6, 35, 33), // "std::vector<std::vector<doubl..."
QT_MOC_LITERAL(7, 69, 4), // "data"
QT_MOC_LITERAL(8, 74, 15), // "slot_save_image"
QT_MOC_LITERAL(9, 90, 15), // "slot_load_image"
QT_MOC_LITERAL(10, 106, 14), // "slot_set_gamma"
QT_MOC_LITERAL(11, 121, 5), // "value"
QT_MOC_LITERAL(12, 127, 19), // "slot_set_color_mode"
QT_MOC_LITERAL(13, 147, 4) // "mode"

    },
    "Viewer2D\0pick\0\0p0\0p1\0slot_set_data\0"
    "std::vector<std::vector<double> >\0"
    "data\0slot_save_image\0slot_load_image\0"
    "slot_set_gamma\0value\0slot_set_color_mode\0"
    "mode"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Viewer2D[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   49,    2, 0x0a /* Public */,
       8,    0,   52,    2, 0x0a /* Public */,
       9,    0,   53,    2, 0x0a /* Public */,
      10,    1,   54,    2, 0x0a /* Public */,
      12,    1,   57,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double, QMetaType::Double,    3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Int,   13,

       0        // eod
};

void Viewer2D::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Viewer2D *_t = static_cast<Viewer2D *>(_o);
        switch (_id) {
        case 0: _t->pick((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 1: _t->slot_set_data((*reinterpret_cast< std::vector<std::vector<double> >(*)>(_a[1]))); break;
        case 2: _t->slot_save_image(); break;
        case 3: _t->slot_load_image(); break;
        case 4: _t->slot_set_gamma((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->slot_set_color_mode((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Viewer2D::*_t)(double , double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Viewer2D::pick)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject Viewer2D::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Viewer2D.data,
      qt_meta_data_Viewer2D,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Viewer2D::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Viewer2D::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Viewer2D.stringdata))
        return static_cast<void*>(const_cast< Viewer2D*>(this));
    return QWidget::qt_metacast(_clname);
}

int Viewer2D::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void Viewer2D::pick(double _t1, double _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
