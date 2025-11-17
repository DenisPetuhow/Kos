/****************************************************************************
** Meta object code from reading C++ file 'neworbobj.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ASD/neworbobj.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'neworbobj.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CNewOrbObj_t {
    QByteArrayData data[13];
    char stringdata0[123];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CNewOrbObj_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CNewOrbObj_t qt_meta_stringdata_CNewOrbObj = {
    {
QT_MOC_LITERAL(0, 0, 10), // "CNewOrbObj"
QT_MOC_LITERAL(1, 11, 6), // "accept"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 9), // "setdattab"
QT_MOC_LITERAL(4, 29, 9), // "setdatsys"
QT_MOC_LITERAL(5, 39, 7), // "opentle"
QT_MOC_LITERAL(6, 47, 9), // "settabtle"
QT_MOC_LITERAL(7, 57, 10), // "chekparam1"
QT_MOC_LITERAL(8, 68, 10), // "chekparam2"
QT_MOC_LITERAL(9, 79, 10), // "chekparam3"
QT_MOC_LITERAL(10, 90, 10), // "chekparam4"
QT_MOC_LITERAL(11, 101, 10), // "chekparam5"
QT_MOC_LITERAL(12, 112, 10) // "chekparam6"

    },
    "CNewOrbObj\0accept\0\0setdattab\0setdatsys\0"
    "opentle\0settabtle\0chekparam1\0chekparam2\0"
    "chekparam3\0chekparam4\0chekparam5\0"
    "chekparam6"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CNewOrbObj[] = {

 // content:
       8,       // revision
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
       3,    0,   70,    2, 0x09 /* Protected */,
       4,    0,   71,    2, 0x09 /* Protected */,
       5,    0,   72,    2, 0x09 /* Protected */,
       6,    0,   73,    2, 0x09 /* Protected */,
       7,    0,   74,    2, 0x09 /* Protected */,
       8,    0,   75,    2, 0x09 /* Protected */,
       9,    0,   76,    2, 0x09 /* Protected */,
      10,    0,   77,    2, 0x09 /* Protected */,
      11,    0,   78,    2, 0x09 /* Protected */,
      12,    0,   79,    2, 0x09 /* Protected */,

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

       0        // eod
};

void CNewOrbObj::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CNewOrbObj *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->accept(); break;
        case 1: _t->setdattab(); break;
        case 2: _t->setdatsys(); break;
        case 3: _t->opentle(); break;
        case 4: _t->settabtle(); break;
        case 5: _t->chekparam1(); break;
        case 6: _t->chekparam2(); break;
        case 7: _t->chekparam3(); break;
        case 8: _t->chekparam4(); break;
        case 9: _t->chekparam5(); break;
        case 10: _t->chekparam6(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject CNewOrbObj::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_CNewOrbObj.data,
    qt_meta_data_CNewOrbObj,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CNewOrbObj::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CNewOrbObj::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CNewOrbObj.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int CNewOrbObj::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
