#-------------------------------------------------
#
# Project created by QtCreator 2017-02-10T21:30:45
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = itunesBackupParser
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    instruction.cpp \
    TUpdate.cpp \
    TBackupSender.cpp


HEADERS  += mainwindow.h \
    instruction.h \
    TConstants.h \
    TUpdate.h \
    TBackupSender.h


FORMS    += mainwindow.ui \
    instruction.ui

RESOURCES += \
    images.qrc





