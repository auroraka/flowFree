#-------------------------------------------------
#
# Project created by QtCreator 2015-08-25T14:45:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = flowFree
TEMPLATE = app


SOURCES += main.cpp\
    chooseform.cpp \
    block.cpp \
    way.cpp \
    gamecontrol.cpp

HEADERS  += \
    chooseform.h \
    enviroment.h \
    block.h \
    way.h \
    gamecontrol.h

FORMS    += \
    gamecontrol.ui
