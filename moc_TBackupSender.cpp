/****************************************************************************
** Meta object code from reading C++ file 'TBackupSender.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "TBackupSender.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TBackupSender.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TBackupSender_t {
    QByteArrayData data[16];
    char stringdata0[220];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TBackupSender_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TBackupSender_t qt_meta_stringdata_TBackupSender = {
    {
QT_MOC_LITERAL(0, 0, 13), // "TBackupSender"
QT_MOC_LITERAL(1, 14, 21), // "finish_backup_sending"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 10), // "finishCode"
QT_MOC_LITERAL(4, 48, 17), // "tabBarClickedSlot"
QT_MOC_LITERAL(5, 66, 5), // "tabId"
QT_MOC_LITERAL(6, 72, 12), // "showAllTasks"
QT_MOC_LITERAL(7, 85, 22), // "btnSendBackupClickSlot"
QT_MOC_LITERAL(8, 108, 16), // "getTargetAppList"
QT_MOC_LITERAL(9, 125, 13), // "setUrlAndGuid"
QT_MOC_LITERAL(10, 139, 16), // "finishSendBackup"
QT_MOC_LITERAL(11, 156, 20), // "QProcess::ExitStatus"
QT_MOC_LITERAL(12, 177, 11), // "runSendProc"
QT_MOC_LITERAL(13, 189, 10), // "targetApps"
QT_MOC_LITERAL(14, 200, 13), // "endSendBackUp"
QT_MOC_LITERAL(15, 214, 5) // "clean"

    },
    "TBackupSender\0finish_backup_sending\0"
    "\0finishCode\0tabBarClickedSlot\0tabId\0"
    "showAllTasks\0btnSendBackupClickSlot\0"
    "getTargetAppList\0setUrlAndGuid\0"
    "finishSendBackup\0QProcess::ExitStatus\0"
    "runSendProc\0targetApps\0endSendBackUp\0"
    "clean"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TBackupSender[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   67,    2, 0x0a /* Public */,
       6,    0,   70,    2, 0x08 /* Private */,
       7,    1,   71,    2, 0x08 /* Private */,
       8,    0,   74,    2, 0x08 /* Private */,
       9,    0,   75,    2, 0x08 /* Private */,
      10,    2,   76,    2, 0x08 /* Private */,
      12,    1,   81,    2, 0x08 /* Private */,
      14,    0,   84,    2, 0x08 /* Private */,
      15,    0,   85,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::QStringList,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 11,    2,    2,
    QMetaType::Void, QMetaType::QStringList,   13,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TBackupSender::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TBackupSender *_t = static_cast<TBackupSender *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->finish_backup_sending((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->tabBarClickedSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->showAllTasks(); break;
        case 3: _t->btnSendBackupClickSlot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: { QStringList _r = _t->getTargetAppList();
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = _r; }  break;
        case 5: { bool _r = _t->setUrlAndGuid();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 6: _t->finishSendBackup((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        case 7: _t->runSendProc((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 8: _t->endSendBackUp(); break;
        case 9: _t->clean(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TBackupSender::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TBackupSender::finish_backup_sending)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject TBackupSender::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TBackupSender.data,
      qt_meta_data_TBackupSender,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TBackupSender::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TBackupSender::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TBackupSender.stringdata0))
        return static_cast<void*>(const_cast< TBackupSender*>(this));
    return QObject::qt_metacast(_clname);
}

int TBackupSender::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void TBackupSender::finish_backup_sending(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
