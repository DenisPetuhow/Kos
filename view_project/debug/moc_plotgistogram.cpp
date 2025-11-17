/****************************************************************************
** Meta object code from reading C++ file 'plotgistogram.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../plotgistogram.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'plotgistogram.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CPlotGistogram_t {
    QByteArrayData data[10];
    char stringdata0[107];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CPlotGistogram_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CPlotGistogram_t qt_meta_stringdata_CPlotGistogram = {
    {
QT_MOC_LITERAL(0, 0, 14), // "CPlotGistogram"
QT_MOC_LITERAL(1, 15, 14), // "setOrientation"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 11), // "orientation"
QT_MOC_LITERAL(4, 43, 11), // "exportChart"
QT_MOC_LITERAL(5, 55, 6), // "setDat"
QT_MOC_LITERAL(6, 62, 25), // "QVector<QVector<double> >"
QT_MOC_LITERAL(7, 88, 6), // "series"
QT_MOC_LITERAL(8, 95, 6), // "titles"
QT_MOC_LITERAL(9, 102, 4) // "titl"

    },
    "CPlotGistogram\0setOrientation\0\0"
    "orientation\0exportChart\0setDat\0"
    "QVector<QVector<double> >\0series\0"
    "titles\0titl"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CPlotGistogram[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x0a /* Public */,
       4,    0,   32,    2, 0x0a /* Public */,
       5,    3,   33,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6, QMetaType::QStringList, QMetaType::QString,    7,    8,    9,

       0        // eod
};

void CPlotGistogram::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CPlotGistogram *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setOrientation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->exportChart(); break;
        case 2: _t->setDat((*reinterpret_cast< QVector<QVector<double> >(*)>(_a[1])),(*reinterpret_cast< QStringList(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QVector<double> > >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CPlotGistogram::staticMetaObject = { {
    &QwtPlot::staticMetaObject,
    qt_meta_stringdata_CPlotGistogram.data,
    qt_meta_data_CPlotGistogram,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CPlotGistogram::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CPlotGistogram::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CPlotGistogram.stringdata0))
        return static_cast<void*>(this);
    return QwtPlot::qt_metacast(_clname);
}

int CPlotGistogram::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QwtPlot::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
