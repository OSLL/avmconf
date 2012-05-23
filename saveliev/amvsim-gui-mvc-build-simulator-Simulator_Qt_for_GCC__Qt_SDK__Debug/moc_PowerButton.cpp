/****************************************************************************
** Meta object code from reading C++ file 'PowerButton.h'
**
** Created: Wed May 23 17:00:18 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../amvsim/ContainerList/PowerButton.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PowerButton.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PowerButton[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_PowerButton[] = {
    "PowerButton\0"
};

const QMetaObject PowerButton::staticMetaObject = {
    { &QToolButton::staticMetaObject, qt_meta_stringdata_PowerButton,
      qt_meta_data_PowerButton, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PowerButton::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PowerButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PowerButton::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PowerButton))
        return static_cast<void*>(const_cast< PowerButton*>(this));
    return QToolButton::qt_metacast(_clname);
}

int PowerButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QToolButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_TextPowerButton[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_TextPowerButton[] = {
    "TextPowerButton\0"
};

const QMetaObject TextPowerButton::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_TextPowerButton,
      qt_meta_data_TextPowerButton, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TextPowerButton::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TextPowerButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TextPowerButton::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TextPowerButton))
        return static_cast<void*>(const_cast< TextPowerButton*>(this));
    return QPushButton::qt_metacast(_clname);
}

int TextPowerButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
