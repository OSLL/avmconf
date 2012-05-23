/****************************************************************************
** Meta object code from reading C++ file 'DoubleParameterWithRangeWidget.h'
**
** Created: Wed May 23 17:09:49 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../amvsim/ParameterWidgets/DoubleParameterWithRangeWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DoubleParameterWithRangeWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DoubleParameterWithRangeWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      32,   31,   31,   31, 0x0a,
      53,   31,   31,   31, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_DoubleParameterWithRangeWidget[] = {
    "DoubleParameterWithRangeWidget\0\0"
    "editChanged(QString)\0sliderMoved(int)\0"
};

void DoubleParameterWithRangeWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DoubleParameterWithRangeWidget *_t = static_cast<DoubleParameterWithRangeWidget *>(_o);
        switch (_id) {
        case 0: _t->editChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DoubleParameterWithRangeWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DoubleParameterWithRangeWidget::staticMetaObject = {
    { &ParameterWidget::staticMetaObject, qt_meta_stringdata_DoubleParameterWithRangeWidget,
      qt_meta_data_DoubleParameterWithRangeWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DoubleParameterWithRangeWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DoubleParameterWithRangeWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DoubleParameterWithRangeWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DoubleParameterWithRangeWidget))
        return static_cast<void*>(const_cast< DoubleParameterWithRangeWidget*>(this));
    return ParameterWidget::qt_metacast(_clname);
}

int DoubleParameterWithRangeWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ParameterWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
