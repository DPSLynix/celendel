/****************************************************************************
** Meta object code from reading C++ file 'VOIP.h'
**
** Created: Sun 22. Jul 20:25:57 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../VOIP/VOIP.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'VOIP.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_VOIP[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       8,    6,    5,    5, 0x05,

 // slots: signature, parameters, type, tag, flags
      33,   31,    5,    5, 0x0a,
      58,   51,    5,    5, 0x0a,
      75,    5,    5,    5, 0x0a,
      92,    5,    5,    5, 0x08,
     103,  101,    5,    5, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_VOIP[] = {
    "VOIP\0\0,\0dataPerSecond(int,int)\0q\0"
    "setQuality(float)\0volume\0setVolume(float)\0"
    "setEnabled(bool)\0update()\0b\0"
    "send(QByteArray)\0"
};

const QMetaObject VOIP::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_VOIP,
      qt_meta_data_VOIP, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &VOIP::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *VOIP::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *VOIP::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VOIP))
        return static_cast<void*>(const_cast< VOIP*>(this));
    return QObject::qt_metacast(_clname);
}

int VOIP::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: dataPerSecond((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: setQuality((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: setVolume((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: setEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: update(); break;
        case 5: send((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void VOIP::dataPerSecond(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
