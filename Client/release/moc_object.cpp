/****************************************************************************
** Meta object code from reading C++ file 'object.h'
**
** Created: Sat 19. Mar 11:10:01 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Shared/XML/object.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'object.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Object[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Object[] = {
    "Object\0\0throwUp()\0"
};

const QMetaObject Object::staticMetaObject = {
    { &MaterialThing::staticMetaObject, qt_meta_stringdata_Object,
      qt_meta_data_Object, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Object::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Object::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Object::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Object))
        return static_cast<void*>(const_cast< Object*>(this));
    return MaterialThing::qt_metacast(_clname);
}

int Object::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MaterialThing::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: throwUp(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
