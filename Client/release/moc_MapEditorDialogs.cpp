/****************************************************************************
** Meta object code from reading C++ file 'MapEditorDialogs.h'
**
** Created: Sun 22. Jul 20:25:58 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../MapEditorDialogs.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MapEditorDialogs.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AddObjectDialog[] = {

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
      17,   16,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_AddObjectDialog[] = {
    "AddObjectDialog\0\0vcng(int)\0"
};

const QMetaObject AddObjectDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_AddObjectDialog,
      qt_meta_data_AddObjectDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AddObjectDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AddObjectDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AddObjectDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AddObjectDialog))
        return static_cast<void*>(const_cast< AddObjectDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int AddObjectDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: vcng((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_NewMapDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x08,
      34,   13,   13,   13, 0x08,
      59,   55,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_NewMapDialog[] = {
    "NewMapDialog\0\0on_browse_pressed()\0"
    "on_mbrowse_pressed()\0ind\0"
    "on_typeCB_currentIndexChanged(int)\0"
};

const QMetaObject NewMapDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_NewMapDialog,
      qt_meta_data_NewMapDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &NewMapDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *NewMapDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *NewMapDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NewMapDialog))
        return static_cast<void*>(const_cast< NewMapDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int NewMapDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_browse_pressed(); break;
        case 1: on_mbrowse_pressed(); break;
        case 2: on_typeCB_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
