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
    GUIDE_WHATSAPP.cpp \
    GUIDE_TELEGRAM.cpp \
    GUIDE_WECHAT.cpp \
    GUIDE_MAIN.cpp


HEADERS  += mainwindow.h \
    instruction.h \
    GUIDE_WHATSAPP.h \
    GUIDE_TELEGRAM.h \
    GUIDE_WECHAT.h \
    GUIDE_MAIN.h


FORMS    += mainwindow.ui \
    instruction.ui \
    GUIDE_WHATSAPP.ui \
    GUIDE_TELEGRAM.ui \
    GUIDE_WECHAT.ui \
    GUIDE_MAIN.ui

RESOURCES += \
    images.qrc





