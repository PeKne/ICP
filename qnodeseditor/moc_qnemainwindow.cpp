/****************************************************************************
** Meta object code from reading C++ file 'qnemainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qnemainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qnemainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QNEMainWindow_t {
    QByteArrayData data[16];
    char stringdata0[179];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QNEMainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QNEMainWindow_t qt_meta_stringdata_QNEMainWindow = {
    {
QT_MOC_LITERAL(0, 0, 13), // "QNEMainWindow"
QT_MOC_LITERAL(1, 14, 8), // "saveFile"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 8), // "loadFile"
QT_MOC_LITERAL(4, 33, 8), // "new_file"
QT_MOC_LITERAL(5, 42, 13), // "add_block_add"
QT_MOC_LITERAL(6, 56, 13), // "add_block_sub"
QT_MOC_LITERAL(7, 70, 13), // "add_block_div"
QT_MOC_LITERAL(8, 84, 13), // "add_block_mul"
QT_MOC_LITERAL(9, 98, 13), // "add_block_pow"
QT_MOC_LITERAL(10, 112, 15), // "add_block_input"
QT_MOC_LITERAL(11, 128, 16), // "add_block_output"
QT_MOC_LITERAL(12, 145, 7), // "run_app"
QT_MOC_LITERAL(13, 153, 9), // "reset_app"
QT_MOC_LITERAL(14, 163, 9), // "debug_app"
QT_MOC_LITERAL(15, 173, 5) // "delay"

    },
    "QNEMainWindow\0saveFile\0\0loadFile\0"
    "new_file\0add_block_add\0add_block_sub\0"
    "add_block_div\0add_block_mul\0add_block_pow\0"
    "add_block_input\0add_block_output\0"
    "run_app\0reset_app\0debug_app\0delay"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QNEMainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x08 /* Private */,
       3,    0,   85,    2, 0x08 /* Private */,
       4,    0,   86,    2, 0x08 /* Private */,
       5,    0,   87,    2, 0x08 /* Private */,
       6,    0,   88,    2, 0x08 /* Private */,
       7,    0,   89,    2, 0x08 /* Private */,
       8,    0,   90,    2, 0x08 /* Private */,
       9,    0,   91,    2, 0x08 /* Private */,
      10,    0,   92,    2, 0x08 /* Private */,
      11,    0,   93,    2, 0x08 /* Private */,
      12,    0,   94,    2, 0x08 /* Private */,
      13,    0,   95,    2, 0x08 /* Private */,
      14,    0,   96,    2, 0x08 /* Private */,
      15,    0,   97,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QNEMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QNEMainWindow *_t = static_cast<QNEMainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->saveFile(); break;
        case 1: _t->loadFile(); break;
        case 2: _t->new_file(); break;
        case 3: _t->add_block_add(); break;
        case 4: _t->add_block_sub(); break;
        case 5: _t->add_block_div(); break;
        case 6: _t->add_block_mul(); break;
        case 7: _t->add_block_pow(); break;
        case 8: _t->add_block_input(); break;
        case 9: _t->add_block_output(); break;
        case 10: _t->run_app(); break;
        case 11: _t->reset_app(); break;
        case 12: _t->debug_app(); break;
        case 13: _t->delay(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject QNEMainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_QNEMainWindow.data,
      qt_meta_data_QNEMainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QNEMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QNEMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QNEMainWindow.stringdata0))
        return static_cast<void*>(const_cast< QNEMainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int QNEMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
