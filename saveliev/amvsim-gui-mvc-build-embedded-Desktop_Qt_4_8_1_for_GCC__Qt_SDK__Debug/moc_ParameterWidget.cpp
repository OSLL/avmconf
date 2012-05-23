/****************************************************************************
** Meta object code from reading C++ file 'ParameterWidget.h'
**
** Created: Wed May 23 17:09:43 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../amvsim/ParameterWidgets/ParameterWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ParameterWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ParameterWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      29,   17,   16,   16, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_ParameterWidget[] = {
    "ParameterWidget\0\0parId,value\0"
    "parameterChanged(std::string,Value*)\0"
};

void ParameterWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ParameterWidget *_t = static_cast<ParameterWidget *>(_o);
        switch (_id) {
        case 0: _t->parameterChanged((*reinterpret_cast< const std::string(*)>(_a[1])),(*reinterpret_cast< Value*(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ParameterWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ParameterWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ParameterWidget,
      qt_meta_data_ParameterWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ParameterWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ParameterWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ParameterWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ParameterWidget))
        return static_cast<void*>(const_cast< ParameterWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int ParameterWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void ParameterWidget::parameterChanged(const std::string & _t1, Value * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
