/****************************************************************************
** Meta object code from reading C++ file 'Speex.h'
**
** Created: Sun 22. Jul 20:25:51 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../VOIP/Speex.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Speex.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_VOIPSystem__Speex[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x05,
      39,   18,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      64,   62,   18,   18, 0x0a,
      90,   82,   18,   18, 0x0a,
     117,  112,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_VOIPSystem__Speex[] = {
    "VOIPSystem::Speex\0\0encoded(QByteArray)\0"
    "decoded(ALshortVector)\0q\0setQuality(float)\0"
    "samples\0encode(ALshortVector)\0data\0"
    "decode(QByteArray)\0"
};

const QMetaObject VOIPSystem::Speex::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_VOIPSystem__Speex,
      qt_meta_data_VOIPSystem__Speex, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &VOIPSystem::Speex::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *VOIPSystem::Speex::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *VOIPSystem::Speex::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VOIPSystem__Speex))
        return static_cast<void*>(const_cast< Speex*>(this));
    return QObject::qt_metacast(_clname);
}

int VOIPSystem::Speex::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: encoded((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 1: decoded((*reinterpret_cast< const ALshortVector(*)>(_a[1]))); break;
        case 2: setQuality((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: encode((*reinterpret_cast< ALshortVector(*)>(_a[1]))); break;
        case 4: decode((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void VOIPSystem::Speex::encoded(const QByteArray & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VOIPSystem::Speex::decoded(const ALshortVector & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
