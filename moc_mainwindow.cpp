/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[18];
    char stringdata0[332];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 18), // "finishFetchProfile"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 20), // "QProcess::ExitStatus"
QT_MOC_LITERAL(4, 52, 15), // "finishModifyApp"
QT_MOC_LITERAL(5, 68, 11), // "endParseApp"
QT_MOC_LITERAL(6, 80, 16), // "finishUpdateSlot"
QT_MOC_LITERAL(7, 97, 9), // "errorCode"
QT_MOC_LITERAL(8, 107, 19), // "on_startBtn_clicked"
QT_MOC_LITERAL(9, 127, 14), // "startCreateApp"
QT_MOC_LITERAL(10, 142, 23), // "sendReportToServerReply"
QT_MOC_LITERAL(11, 166, 14), // "QNetworkReply*"
QT_MOC_LITERAL(12, 181, 5), // "reply"
QT_MOC_LITERAL(13, 187, 24), // "on_chooseFileBtn_clicked"
QT_MOC_LITERAL(14, 212, 19), // "on_action_triggered"
QT_MOC_LITERAL(15, 232, 31), // "on_actionOpenTasksDir_triggered"
QT_MOC_LITERAL(16, 264, 37), // "on_actionOpenCurrentTaskDir_t..."
QT_MOC_LITERAL(17, 302, 29) // "on_btnOpenReadyIpaDir_clicked"

    },
    "MainWindow\0finishFetchProfile\0\0"
    "QProcess::ExitStatus\0finishModifyApp\0"
    "endParseApp\0finishUpdateSlot\0errorCode\0"
    "on_startBtn_clicked\0startCreateApp\0"
    "sendReportToServerReply\0QNetworkReply*\0"
    "reply\0on_chooseFileBtn_clicked\0"
    "on_action_triggered\0on_actionOpenTasksDir_triggered\0"
    "on_actionOpenCurrentTaskDir_triggered\0"
    "on_btnOpenReadyIpaDir_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   74,    2, 0x0a /* Public */,
       4,    2,   79,    2, 0x0a /* Public */,
       5,    2,   84,    2, 0x0a /* Public */,
       6,    1,   89,    2, 0x0a /* Public */,
       8,    0,   92,    2, 0x08 /* Private */,
       9,    0,   93,    2, 0x08 /* Private */,
      10,    1,   94,    2, 0x08 /* Private */,
      13,    0,   97,    2, 0x08 /* Private */,
      14,    0,   98,    2, 0x08 /* Private */,
      15,    0,   99,    2, 0x08 /* Private */,
      16,    0,  100,    2, 0x08 /* Private */,
      17,    0,  101,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 3,    2,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 3,    2,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 3,    2,    2,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->finishFetchProfile((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        case 1: _t->finishModifyApp((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        case 2: _t->endParseApp((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        case 3: _t->finishUpdateSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_startBtn_clicked(); break;
        case 5: _t->startCreateApp(); break;
        case 6: _t->sendReportToServerReply((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 7: _t->on_chooseFileBtn_clicked(); break;
        case 8: _t->on_action_triggered(); break;
        case 9: _t->on_actionOpenTasksDir_triggered(); break;
        case 10: _t->on_actionOpenCurrentTaskDir_triggered(); break;
        case 11: _t->on_btnOpenReadyIpaDir_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
