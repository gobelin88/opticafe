/****************************************************************************
** Meta object code from reading C++ file '3d_viewer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../3d_viewer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '3d_viewer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Viewer3D_t {
    QByteArrayData data[17];
    char stringdata[215];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Viewer3D_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Viewer3D_t qt_meta_stringdata_Viewer3D = {
    {
QT_MOC_LITERAL(0, 0, 8), // "Viewer3D"
QT_MOC_LITERAL(1, 9, 10), // "slot_front"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 9), // "slot_back"
QT_MOC_LITERAL(4, 31, 9), // "slot_left"
QT_MOC_LITERAL(5, 41, 10), // "slot_right"
QT_MOC_LITERAL(6, 52, 8), // "slot_top"
QT_MOC_LITERAL(7, 61, 11), // "slot_bottom"
QT_MOC_LITERAL(8, 73, 9), // "slot_init"
QT_MOC_LITERAL(9, 83, 14), // "slot_set_gamma"
QT_MOC_LITERAL(10, 98, 5), // "value"
QT_MOC_LITERAL(11, 104, 12), // "slot_set_cut"
QT_MOC_LITERAL(12, 117, 19), // "slot_set_color_mode"
QT_MOC_LITERAL(13, 137, 10), // "color_mode"
QT_MOC_LITERAL(14, 148, 13), // "slot_set_data"
QT_MOC_LITERAL(15, 162, 47), // "std::vector<std::vector<std::..."
QT_MOC_LITERAL(16, 210, 4) // "data"

    },
    "Viewer3D\0slot_front\0\0slot_back\0slot_left\0"
    "slot_right\0slot_top\0slot_bottom\0"
    "slot_init\0slot_set_gamma\0value\0"
    "slot_set_cut\0slot_set_color_mode\0"
    "color_mode\0slot_set_data\0"
    "std::vector<std::vector<std::vector<double> > >\0"
    "data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Viewer3D[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x0a /* Public */,
       3,    0,   70,    2, 0x0a /* Public */,
       4,    0,   71,    2, 0x0a /* Public */,
       5,    0,   72,    2, 0x0a /* Public */,
       6,    0,   73,    2, 0x0a /* Public */,
       7,    0,   74,    2, 0x0a /* Public */,
       8,    0,   75,    2, 0x0a /* Public */,
       9,    1,   76,    2, 0x0a /* Public */,
      11,    1,   79,    2, 0x0a /* Public */,
      12,    1,   82,    2, 0x0a /* Public */,
      14,    1,   85,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,   10,
    QMetaType::Void, QMetaType::Double,   10,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void, 0x80000000 | 15,   16,

       0        // eod
};

void Viewer3D::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Viewer3D *_t = static_cast<Viewer3D *>(_o);
        switch (_id) {
        case 0: _t->slot_front(); break;
        case 1: _t->slot_back(); break;
        case 2: _t->slot_left(); break;
        case 3: _t->slot_right(); break;
        case 4: _t->slot_top(); break;
        case 5: _t->slot_bottom(); break;
        case 6: _t->slot_init(); break;
        case 7: _t->slot_set_gamma((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: _t->slot_set_cut((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 9: _t->slot_set_color_mode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->slot_set_data((*reinterpret_cast< std::vector<std::vector<std::vector<double> > >(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject Viewer3D::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_Viewer3D.data,
      qt_meta_data_Viewer3D,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Viewer3D::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Viewer3D::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Viewer3D.stringdata))
        return static_cast<void*>(const_cast< Viewer3D*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int Viewer3D::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
