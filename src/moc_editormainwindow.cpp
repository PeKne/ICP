/****************************************************************************
** Meta object code from reading C++ file 'editormainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "editormainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'editormainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_EditorMainWindow_t {
    QByteArrayData data[22];
    char stringdata0[262];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EditorMainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EditorMainWindow_t qt_meta_stringdata_EditorMainWindow = {
    {
QT_MOC_LITERAL(0, 0, 16), // "EditorMainWindow"
QT_MOC_LITERAL(1, 17, 11), // "save_schema"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 11), // "load_schema"
QT_MOC_LITERAL(4, 42, 10), // "new_schema"
QT_MOC_LITERAL(5, 53, 13), // "add_block_add"
QT_MOC_LITERAL(6, 67, 13), // "add_block_sub"
QT_MOC_LITERAL(7, 81, 13), // "add_block_div"
QT_MOC_LITERAL(8, 95, 13), // "add_block_mul"
QT_MOC_LITERAL(9, 109, 13), // "add_block_pow"
QT_MOC_LITERAL(10, 123, 15), // "add_block_input"
QT_MOC_LITERAL(11, 139, 16), // "add_block_output"
QT_MOC_LITERAL(12, 156, 7), // "run_app"
QT_MOC_LITERAL(13, 164, 9), // "reset_app"
QT_MOC_LITERAL(14, 174, 9), // "debug_app"
QT_MOC_LITERAL(15, 184, 15), // "validate_scheme"
QT_MOC_LITERAL(16, 200, 12), // "check_cycles"
QT_MOC_LITERAL(17, 213, 6), // "Block*"
QT_MOC_LITERAL(18, 220, 7), // "current"
QT_MOC_LITERAL(19, 228, 19), // "std::vector<Block*>"
QT_MOC_LITERAL(20, 248, 7), // "in_path"
QT_MOC_LITERAL(21, 256, 5) // "delay"

    },
    "EditorMainWindow\0save_schema\0\0load_schema\0"
    "new_schema\0add_block_add\0add_block_sub\0"
    "add_block_div\0add_block_mul\0add_block_pow\0"
    "add_block_input\0add_block_output\0"
    "run_app\0reset_app\0debug_app\0validate_scheme\0"
    "check_cycles\0Block*\0current\0"
    "std::vector<Block*>\0in_path\0delay"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EditorMainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x08 /* Private */,
       3,    0,   95,    2, 0x08 /* Private */,
       4,    0,   96,    2, 0x08 /* Private */,
       5,    0,   97,    2, 0x08 /* Private */,
       6,    0,   98,    2, 0x08 /* Private */,
       7,    0,   99,    2, 0x08 /* Private */,
       8,    0,  100,    2, 0x08 /* Private */,
       9,    0,  101,    2, 0x08 /* Private */,
      10,    0,  102,    2, 0x08 /* Private */,
      11,    0,  103,    2, 0x08 /* Private */,
      12,    0,  104,    2, 0x08 /* Private */,
      13,    0,  105,    2, 0x08 /* Private */,
      14,    0,  106,    2, 0x08 /* Private */,
      15,    0,  107,    2, 0x08 /* Private */,
      16,    2,  108,    2, 0x08 /* Private */,
      21,    0,  113,    2, 0x08 /* Private */,

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
    QMetaType::Bool,
    QMetaType::Bool, 0x80000000 | 17, 0x80000000 | 19,   18,   20,
    QMetaType::Void,

       0        // eod
};

void EditorMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EditorMainWindow *_t = static_cast<EditorMainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->save_schema(); break;
        case 1: _t->load_schema(); break;
        case 2: _t->new_schema(); break;
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
        case 13: { bool _r = _t->validate_scheme();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 14: { bool _r = _t->check_cycles((*reinterpret_cast< Block*(*)>(_a[1])),(*reinterpret_cast< std::vector<Block*>(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 15: _t->delay(); break;
        default: ;
        }
    }
}

const QMetaObject EditorMainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_EditorMainWindow.data,
      qt_meta_data_EditorMainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *EditorMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EditorMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_EditorMainWindow.stringdata0))
        return static_cast<void*>(const_cast< EditorMainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int EditorMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
