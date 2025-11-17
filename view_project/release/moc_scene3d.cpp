/****************************************************************************
** Meta object code from reading C++ file 'scene3d.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../gui3D/scene3d.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scene3d.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ASDScene3D_t {
    QByteArrayData data[8];
    char stringdata0[99];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ASDScene3D_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ASDScene3D_t qt_meta_stringdata_ASDScene3D = {
    {
QT_MOC_LITERAL(0, 0, 10), // "ASDScene3D"
QT_MOC_LITERAL(1, 11, 14), // "changeFlagAxis"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 13), // "changeFlagSky"
QT_MOC_LITERAL(4, 41, 13), // "changeFlagSun"
QT_MOC_LITERAL(5, 55, 12), // "replaceEarth"
QT_MOC_LITERAL(6, 68, 14), // "replaceEarthDN"
QT_MOC_LITERAL(7, 83, 15) // "replaceEarthAtm"

    },
    "ASDScene3D\0changeFlagAxis\0\0changeFlagSky\0"
    "changeFlagSun\0replaceEarth\0replaceEarthDN\0"
    "replaceEarthAtm"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ASDScene3D[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x0a /* Public */,
       3,    0,   45,    2, 0x0a /* Public */,
       4,    0,   46,    2, 0x0a /* Public */,
       5,    0,   47,    2, 0x0a /* Public */,
       6,    0,   48,    2, 0x0a /* Public */,
       7,    0,   49,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ASDScene3D::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ASDScene3D *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changeFlagAxis(); break;
        case 1: _t->changeFlagSky(); break;
        case 2: _t->changeFlagSun(); break;
        case 3: _t->replaceEarth(); break;
        case 4: _t->replaceEarthDN(); break;
        case 5: _t->replaceEarthAtm(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject ASDScene3D::staticMetaObject = { {
    &ViewerWidget::staticMetaObject,
    qt_meta_stringdata_ASDScene3D.data,
    qt_meta_data_ASDScene3D,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ASDScene3D::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ASDScene3D::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ASDScene3D.stringdata0))
        return static_cast<void*>(this);
    return ViewerWidget::qt_metacast(_clname);
}

int ASDScene3D::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ViewerWidget::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
