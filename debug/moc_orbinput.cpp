/****************************************************************************
** Meta object code from reading C++ file 'orbinput.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../orbinput.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'orbinput.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_COrbInput_t {
    QByteArrayData data[17];
    char stringdata0[223];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_COrbInput_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_COrbInput_t qt_meta_stringdata_COrbInput = {
    {
QT_MOC_LITERAL(0, 0, 9), // "COrbInput"
QT_MOC_LITERAL(1, 10, 14), // "createOrbitObj"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 20), // "createSystemOrbitObj"
QT_MOC_LITERAL(4, 47, 16), // "loadOrbitObjFile"
QT_MOC_LITERAL(5, 64, 16), // "loadDefaultParam"
QT_MOC_LITERAL(6, 81, 7), // "strFile"
QT_MOC_LITERAL(7, 89, 16), // "saveOrbitObjFile"
QT_MOC_LITERAL(8, 106, 11), // "addOrbitObj"
QT_MOC_LITERAL(9, 118, 11), // "delOrbitObj"
QT_MOC_LITERAL(10, 130, 11), // "findParamKA"
QT_MOC_LITERAL(11, 142, 17), // "fillListWidgetBsk"
QT_MOC_LITERAL(12, 160, 12), // "viewParamBsk"
QT_MOC_LITERAL(13, 173, 11), // "addParamBsa"
QT_MOC_LITERAL(14, 185, 12), // "editParamBsa"
QT_MOC_LITERAL(15, 198, 11), // "delParamBsa"
QT_MOC_LITERAL(16, 210, 12) // "saveParamBsa"

    },
    "COrbInput\0createOrbitObj\0\0"
    "createSystemOrbitObj\0loadOrbitObjFile\0"
    "loadDefaultParam\0strFile\0saveOrbitObjFile\0"
    "addOrbitObj\0delOrbitObj\0findParamKA\0"
    "fillListWidgetBsk\0viewParamBsk\0"
    "addParamBsa\0editParamBsa\0delParamBsa\0"
    "saveParamBsa"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_COrbInput[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x0a /* Public */,
       3,    0,   85,    2, 0x0a /* Public */,
       4,    0,   86,    2, 0x0a /* Public */,
       5,    1,   87,    2, 0x0a /* Public */,
       7,    0,   90,    2, 0x0a /* Public */,
       8,    0,   91,    2, 0x0a /* Public */,
       9,    0,   92,    2, 0x0a /* Public */,
      10,    0,   93,    2, 0x0a /* Public */,
      11,    0,   94,    2, 0x0a /* Public */,
      12,    0,   95,    2, 0x0a /* Public */,
      13,    0,   96,    2, 0x0a /* Public */,
      14,    0,   97,    2, 0x0a /* Public */,
      15,    0,   98,    2, 0x0a /* Public */,
      16,    0,   99,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
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

void COrbInput::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<COrbInput *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->createOrbitObj(); break;
        case 1: _t->createSystemOrbitObj(); break;
        case 2: _t->loadOrbitObjFile(); break;
        case 3: _t->loadDefaultParam((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->saveOrbitObjFile(); break;
        case 5: _t->addOrbitObj(); break;
        case 6: _t->delOrbitObj(); break;
        case 7: _t->findParamKA(); break;
        case 8: _t->fillListWidgetBsk(); break;
        case 9: _t->viewParamBsk(); break;
        case 10: _t->addParamBsa(); break;
        case 11: _t->editParamBsa(); break;
        case 12: _t->delParamBsa(); break;
        case 13: _t->saveParamBsa(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject COrbInput::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_COrbInput.data,
    qt_meta_data_COrbInput,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *COrbInput::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *COrbInput::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_COrbInput.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Ui_OrbInputClass"))
        return static_cast< Ui_OrbInputClass*>(this);
    return QWidget::qt_metacast(_clname);
}

int COrbInput::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
