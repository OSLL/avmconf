/****************************************************************************
** Meta object code from reading C++ file 'OptionsParameterWidget.h'
**
** Created: Wed May 23 17:09:47 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../amvsim/ParameterWidgets/OptionsParameterWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'OptionsParameterWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_OptionsParameterWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   23,   23,   23, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_OptionsParameterWidget[] = {
    "OptionsParameterWidget\0\0radioSwitched(int)\0"
};

void OptionsParameterWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        OptionsParameterWidget *_t = static_cast<OptionsParameterWidget *>(_o);
        switch (_id) {
        case 0: _t->radioSwitched((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData OptionsParameterWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject OptionsParameterWidget::staticMetaObject = {
    { &ParameterWidget::staticMetaObject, qt_meta_stringdata_OptionsParameterWidget,
      qt_meta_data_OptionsParameterWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &OptionsParameterWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *OptionsParameterWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *OptionsParameterWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OptionsParameterWidget))
        return static_cast<void*>(const_cast< OptionsParameterWidget*>(this));
    return ParameterWidget::qt_metacast(_clname);
}

int OptionsParameterWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ParameterWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
