/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_WorkerThread_t {
    QByteArrayData data[12];
    char stringdata[181];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WorkerThread_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WorkerThread_t qt_meta_stringdata_WorkerThread = {
    {
QT_MOC_LITERAL(0, 0, 12), // "WorkerThread"
QT_MOC_LITERAL(1, 13, 13), // "sig_output_1d"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 19), // "std::vector<double>"
QT_MOC_LITERAL(4, 48, 4), // "data"
QT_MOC_LITERAL(5, 53, 3), // "Box"
QT_MOC_LITERAL(6, 57, 3), // "box"
QT_MOC_LITERAL(7, 61, 13), // "sig_output_2d"
QT_MOC_LITERAL(8, 75, 33), // "std::vector<std::vector<doubl..."
QT_MOC_LITERAL(9, 109, 13), // "sig_output_3d"
QT_MOC_LITERAL(10, 123, 47), // "std::vector<std::vector<std::..."
QT_MOC_LITERAL(11, 171, 9) // "sig_solve"

    },
    "WorkerThread\0sig_output_1d\0\0"
    "std::vector<double>\0data\0Box\0box\0"
    "sig_output_2d\0std::vector<std::vector<double> >\0"
    "sig_output_3d\0"
    "std::vector<std::vector<std::vector<double> > >\0"
    "sig_solve"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WorkerThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   34,    2, 0x06 /* Public */,
       7,    2,   39,    2, 0x06 /* Public */,
       9,    2,   44,    2, 0x06 /* Public */,
      11,    0,   49,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    QMetaType::Void, 0x80000000 | 8, 0x80000000 | 5,    4,    6,
    QMetaType::Void, 0x80000000 | 10, 0x80000000 | 5,    4,    6,
    QMetaType::Void,

       0        // eod
};

void WorkerThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WorkerThread *_t = static_cast<WorkerThread *>(_o);
        switch (_id) {
        case 0: _t->sig_output_1d((*reinterpret_cast< std::vector<double>(*)>(_a[1])),(*reinterpret_cast< Box(*)>(_a[2]))); break;
        case 1: _t->sig_output_2d((*reinterpret_cast< std::vector<std::vector<double> >(*)>(_a[1])),(*reinterpret_cast< Box(*)>(_a[2]))); break;
        case 2: _t->sig_output_3d((*reinterpret_cast< std::vector<std::vector<std::vector<double> > >(*)>(_a[1])),(*reinterpret_cast< Box(*)>(_a[2]))); break;
        case 3: _t->sig_solve(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (WorkerThread::*_t)(std::vector<double> , Box );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WorkerThread::sig_output_1d)) {
                *result = 0;
            }
        }
        {
            typedef void (WorkerThread::*_t)(std::vector<std::vector<double> > , Box );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WorkerThread::sig_output_2d)) {
                *result = 1;
            }
        }
        {
            typedef void (WorkerThread::*_t)(std::vector<std::vector<std::vector<double> > > , Box );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WorkerThread::sig_output_3d)) {
                *result = 2;
            }
        }
        {
            typedef void (WorkerThread::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WorkerThread::sig_solve)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject WorkerThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_WorkerThread.data,
      qt_meta_data_WorkerThread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *WorkerThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WorkerThread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_WorkerThread.stringdata))
        return static_cast<void*>(const_cast< WorkerThread*>(this));
    return QThread::qt_metacast(_clname);
}

int WorkerThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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
void WorkerThread::sig_output_1d(std::vector<double> _t1, Box _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WorkerThread::sig_output_2d(std::vector<std::vector<double> > _t1, Box _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void WorkerThread::sig_output_3d(std::vector<std::vector<std::vector<double> > > _t1, Box _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void WorkerThread::sig_solve()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[29];
    char stringdata[392];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 15), // "slot_run_script"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 16), // "slot_load_script"
QT_MOC_LITERAL(4, 45, 16), // "slot_save_script"
QT_MOC_LITERAL(5, 62, 23), // "slot_direct_save_script"
QT_MOC_LITERAL(6, 86, 17), // "slot_text_changed"
QT_MOC_LITERAL(7, 104, 4), // "pick"
QT_MOC_LITERAL(8, 109, 2), // "p0"
QT_MOC_LITERAL(9, 112, 2), // "p1"
QT_MOC_LITERAL(10, 115, 9), // "slot_conv"
QT_MOC_LITERAL(11, 125, 9), // "slot_func"
QT_MOC_LITERAL(12, 135, 12), // "slot_conv_1d"
QT_MOC_LITERAL(13, 148, 12), // "slot_func_1d"
QT_MOC_LITERAL(14, 161, 12), // "slot_conv_2d"
QT_MOC_LITERAL(15, 174, 12), // "slot_func_2d"
QT_MOC_LITERAL(16, 187, 12), // "slot_conv_3d"
QT_MOC_LITERAL(17, 200, 12), // "slot_func_3d"
QT_MOC_LITERAL(18, 213, 22), // "slot_load_conv_setting"
QT_MOC_LITERAL(19, 236, 8), // "filename"
QT_MOC_LITERAL(20, 245, 22), // "slot_save_conv_setting"
QT_MOC_LITERAL(21, 268, 15), // "slot_solve_over"
QT_MOC_LITERAL(22, 284, 11), // "id1_changed"
QT_MOC_LITERAL(23, 296, 2), // "id"
QT_MOC_LITERAL(24, 299, 11), // "id2_changed"
QT_MOC_LITERAL(25, 311, 11), // "id3_changed"
QT_MOC_LITERAL(26, 323, 22), // "update_button_names_1d"
QT_MOC_LITERAL(27, 346, 22), // "update_button_names_2d"
QT_MOC_LITERAL(28, 369, 22) // "update_button_names_3d"

    },
    "MainWindow\0slot_run_script\0\0"
    "slot_load_script\0slot_save_script\0"
    "slot_direct_save_script\0slot_text_changed\0"
    "pick\0p0\0p1\0slot_conv\0slot_func\0"
    "slot_conv_1d\0slot_func_1d\0slot_conv_2d\0"
    "slot_func_2d\0slot_conv_3d\0slot_func_3d\0"
    "slot_load_conv_setting\0filename\0"
    "slot_save_conv_setting\0slot_solve_over\0"
    "id1_changed\0id\0id2_changed\0id3_changed\0"
    "update_button_names_1d\0update_button_names_2d\0"
    "update_button_names_3d"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      24,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  134,    2, 0x0a /* Public */,
       3,    0,  135,    2, 0x0a /* Public */,
       4,    0,  136,    2, 0x0a /* Public */,
       5,    0,  137,    2, 0x0a /* Public */,
       6,    0,  138,    2, 0x0a /* Public */,
       7,    2,  139,    2, 0x0a /* Public */,
      10,    0,  144,    2, 0x0a /* Public */,
      11,    0,  145,    2, 0x0a /* Public */,
      12,    0,  146,    2, 0x0a /* Public */,
      13,    0,  147,    2, 0x0a /* Public */,
      14,    0,  148,    2, 0x0a /* Public */,
      15,    0,  149,    2, 0x0a /* Public */,
      16,    0,  150,    2, 0x0a /* Public */,
      17,    0,  151,    2, 0x0a /* Public */,
      18,    1,  152,    2, 0x0a /* Public */,
      18,    0,  155,    2, 0x0a /* Public */,
      20,    0,  156,    2, 0x0a /* Public */,
      21,    0,  157,    2, 0x0a /* Public */,
      22,    1,  158,    2, 0x0a /* Public */,
      24,    1,  161,    2, 0x0a /* Public */,
      25,    1,  164,    2, 0x0a /* Public */,
      26,    0,  167,    2, 0x0a /* Public */,
      27,    0,  168,    2, 0x0a /* Public */,
      28,    0,  169,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,    8,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   19,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   23,
    QMetaType::Void, QMetaType::Int,   23,
    QMetaType::Void, QMetaType::Int,   23,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->slot_run_script(); break;
        case 1: _t->slot_load_script(); break;
        case 2: _t->slot_save_script(); break;
        case 3: _t->slot_direct_save_script(); break;
        case 4: _t->slot_text_changed(); break;
        case 5: _t->pick((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 6: _t->slot_conv(); break;
        case 7: _t->slot_func(); break;
        case 8: _t->slot_conv_1d(); break;
        case 9: _t->slot_func_1d(); break;
        case 10: _t->slot_conv_2d(); break;
        case 11: _t->slot_func_2d(); break;
        case 12: _t->slot_conv_3d(); break;
        case 13: _t->slot_func_3d(); break;
        case 14: _t->slot_load_conv_setting((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 15: _t->slot_load_conv_setting(); break;
        case 16: _t->slot_save_conv_setting(); break;
        case 17: _t->slot_solve_over(); break;
        case 18: _t->id1_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: _t->id2_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: _t->id3_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: _t->update_button_names_1d(); break;
        case 22: _t->update_button_names_2d(); break;
        case 23: _t->update_button_names_3d(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 24)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 24;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 24)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 24;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
