/****************************************************************************
** Meta object code from reading C++ file 'ContainerDialog.h'
**
** Created: Wed May 23 17:00:02 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../amvsim/Dialogs/ContainerDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ContainerDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ContainerDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x0a,
      34,   16,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ContainerDialog[] = {
    "ContainerDialog\0\0destroyPressed()\0"
    "cancelDestroyPressed()\0"
};

const QMetaObject ContainerDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ContainerDialog,
      qt_meta_data_ContainerDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ContainerDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ContainerDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ContainerDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ContainerDialog))
        return static_cast<void*>(const_cast< ContainerDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int ContainerDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: destroyPressed(); break;
        case 1: cancelDestroyPressed(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
