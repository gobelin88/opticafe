/****************************************************************************
** Meta object code from reading C++ file 'image_viewer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../image_viewer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'image_viewer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ImageViewer_t {
    QByteArrayData data[9];
    char stringdata[71];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ImageViewer_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ImageViewer_t qt_meta_stringdata_ImageViewer = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ImageViewer"
QT_MOC_LITERAL(1, 12, 4), // "pick"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 2), // "p0"
QT_MOC_LITERAL(4, 21, 2), // "p1"
QT_MOC_LITERAL(5, 24, 8), // "setImage"
QT_MOC_LITERAL(6, 33, 5), // "image"
QT_MOC_LITERAL(7, 39, 15), // "slot_save_image"
QT_MOC_LITERAL(8, 55, 15) // "slot_load_image"

    },
    "ImageViewer\0pick\0\0p0\0p1\0setImage\0image\0"
    "slot_save_image\0slot_load_image"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ImageViewer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   39,    2, 0x0a /* Public */,
       7,    0,   42,    2, 0x0a /* Public */,
       8,    0,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double, QMetaType::Double,    3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::QImage,    6,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ImageViewer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ImageViewer *_t = static_cast<ImageViewer *>(_o);
        switch (_id) {
        case 0: _t->pick((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 1: _t->setImage((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 2: _t->slot_save_image(); break;
        case 3: _t->slot_load_image(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ImageViewer::*_t)(double , double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ImageViewer::pick)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject ImageViewer::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ImageViewer.data,
      qt_meta_data_ImageViewer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ImageViewer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ImageViewer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ImageViewer.stringdata))
        return static_cast<void*>(const_cast< ImageViewer*>(this));
    return QWidget::qt_metacast(_clname);
}

int ImageViewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void ImageViewer::pick(double _t1, double _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
