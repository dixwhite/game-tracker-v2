#-------------------------------------------------
#
# Project created by QtCreator 2017-05-16T19:36:15
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GameTrackerV2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    dbmanager.cpp \
    jsonparser.cpp \
    dialog.cpp \
    global.cpp \
    editdialog.cpp \
    manualadd.cpp

HEADERS  += mainwindow.h \
    dbmanager.h \
    jsonparser.h \
    dialog.h \
    global.h \
    editdialog.h \
    manualadd.h

FORMS    += mainwindow.ui \
    dialog.ui \
    editdialog.ui \
    manualadd.ui

RESOURCES += \
    icons.qrc \
    style.qrc

