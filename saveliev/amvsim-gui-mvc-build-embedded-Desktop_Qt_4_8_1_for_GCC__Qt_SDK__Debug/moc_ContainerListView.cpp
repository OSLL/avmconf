/****************************************************************************
** Meta object code from reading C++ file 'ContainerListView.h'
**
** Created: Wed May 23 17:07:16 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../amvsim/ContainerList/ContainerListView.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ContainerListView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ContainerListView[] = {

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
      36,   19,   18,   18, 0x0a,
      79,   70,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ContainerListView[] = {
    "ContainerListView\0\0parent,start,end\0"
    "rowsInserted(QModelIndex,int,int)\0"
    "contName\0itemPressed(QString)\0"
};

void ContainerListView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ContainerListView *_t = static_cast<ContainerListView *>(_o);
        switch (_id) {
        case 0: _t->rowsInserted((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->itemPressed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ContainerListView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ContainerListView::staticMetaObject = {
    { &QListView::staticMetaObject, qt_meta_stringdata_ContainerListView,
      qt_meta_data_ContainerListView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ContainerListView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ContainerListView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ContainerListView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ContainerListView))
        return static_cast<void*>(const_cast< ContainerListView*>(this));
    return QListView::qt_metacast(_clname);
}

int ContainerListView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListView::qt_metacall(_c, _id, _a);
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
