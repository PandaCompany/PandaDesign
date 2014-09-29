#-------------------------------------------------
#
# Project created by QtCreator 2014-09-28T10:08:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PandaDesign
TEMPLATE = app

SOURCES += main.cpp\
    layer.cpp \
    window.cpp \
    canvas.cpp \
    grouplayer.cpp \
    freehandlayer.cpp \
    freehandcontrols.cpp

HEADERS  += \
    layer.h \
    window.h \
    canvas.h \
    grouplayer.h \
    freehandlayer.h \
    freehandcontrols.h

FORMS    += window.ui \
    freehandcontrols.ui
