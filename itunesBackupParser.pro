#-------------------------------------------------
#
# Project created by QtCreator 2017-02-10T21:30:45
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = itunesBackupParser
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    JlCompress.cpp \
    qioapi.cpp \
    quaadler32.cpp \
    quacrc32.cpp \
    quagzipfile.cpp \
    quaziodevice.cpp \
    quazip.cpp \
    quazipdir.cpp \
    quazipfile.cpp \
    quazipfileinfo.cpp \
    quazipnewinfo.cpp \
    unzip.c \
    zip.c

HEADERS  += mainwindow.h \
    crypt.h \
    ioapi.h \
    JlCompress.h \
    quaadler32.h \
    quachecksum32.h \
    quacrc32.h \
    quagzipfile.h \
    quaziodevice.h \
    quazip.h \
    quazip_global.h \
    quazipdir.h \
    quazipfile.h \
    quazipfileinfo.h \
    quazipnewinfo.h \
    unzip.h \
    zip.h

FORMS    += mainwindow.ui





win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../zlib-1.2.11/ -llibz
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../zlib-1.2.11/ -llibzd

INCLUDEPATH += $$PWD/../zlib-1.2.11
DEPENDPATH += $$PWD/../zlib-1.2.11
