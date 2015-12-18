/****************************************************************************
** Meta object code from reading C++ file '1d_viewer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../1d_viewer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '1d_viewer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Viewer1D_t {
    QByteArrayData data[9];
    char stringdata[65];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Viewer1D_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Viewer1D_t qt_meta_stringdata_Viewer1D = {
    {
QT_MOC_LITERAL(0, 0, 8), // "Viewer1D"
QT_MOC_LITERAL(1, 9, 4), // "pick"
QT_MOC_LITERAL(2, 14, 0), // ""
QT_MOC_LITERAL(3, 15, 2), // "p0"
QT_MOC_LITERAL(4, 18, 13), // "slot_set_data"
QT_MOC_LITERAL(5, 32, 19), // "std::vector<double>"
QT_MOC_LITERAL(6, 52, 4), // "data"
QT_MOC_LITERAL(7, 57, 3), // "Box"
QT_MOC_LITERAL(8, 61, 3) // "box"

    },
    "Viewer1D\0pick\0\0p0\0slot_set_data\0"
    "std::vector<double>\0data\0Box\0box"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Viewer1D[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    2,   27,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double,    3,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 7,    6,    8,

       0        // eod
};

void Viewer1D::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Viewer1D *_t = static_cast<Viewer1D *>(_o);
        switch (_id) {
        case 0: _t->pick((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->slot_set_data((*reinterpret_cast< std::vector<double>(*)>(_a[1])),(*reinterpret_cast< Box(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Viewer1D::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Viewer1D::pick)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject Viewer1D::staticMetaObject = {
    { &QCustomPlot::staticMetaObject, qt_meta_stringdata_Viewer1D.data,
      qt_meta_data_Viewer1D,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Viewer1D::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Viewer1D::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Viewer1D.stringdata))
        return static_cast<void*>(const_cast< Viewer1D*>(this));
    return QCustomPlot::qt_metacast(_clname);
}

int Viewer1D::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCustomPlot::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void Viewer1D::pick(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
