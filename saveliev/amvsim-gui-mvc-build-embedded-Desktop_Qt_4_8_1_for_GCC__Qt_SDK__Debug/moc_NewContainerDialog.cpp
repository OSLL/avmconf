/****************************************************************************
** Meta object code from reading C++ file 'NewContainerDialog.h'
**
** Created: Wed May 23 17:07:02 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../amvsim/Dialogs/NewContainerDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'NewContainerDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_NewContainerDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x0a,
      39,   19,   19,   19, 0x0a,
      56,   19,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_NewContainerDialog[] = {
    "NewContainerDialog\0\0tryCreateHttpFtp()\0"
    "tryCreateLocal()\0chooseFile()\0"
};

void NewContainerDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        NewContainerDialog *_t = static_cast<NewContainerDialog *>(_o);
        switch (_id) {
        case 0: _t->tryCreateHttpFtp(); break;
        case 1: _t->tryCreateLocal(); break;
        case 2: _t->chooseFile(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData NewContainerDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject NewContainerDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_NewContainerDialog,
      qt_meta_data_NewContainerDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &NewContainerDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *NewContainerDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *NewContainerDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NewContainerDialog))
        return static_cast<void*>(const_cast< NewContainerDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int NewContainerDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
