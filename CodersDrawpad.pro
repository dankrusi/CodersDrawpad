#-------------------------------------------------
#
# Project created by QtCreator 2013-04-11T12:33:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CodersDrawpad
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sketcher.cpp \
    path.cpp \
    point.cpp \
    controlpoint.cpp \
    util.cpp

HEADERS  += mainwindow.h \
    sketcher.h \
    path.h \
    point.h \
    controlpoint.h \
    util.h

FORMS    += mainwindow.ui
