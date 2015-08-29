#-------------------------------------------------
#
# Project created by QtCreator 2015-08-25T14:45:32
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = flowFree
TEMPLATE = app


SOURCES += main.cpp\
    block.cpp \
    way.cpp \
    welcomeinterface.cpp \
    designinterface.cpp \
    gameinterface.cpp \
    gameinfo.cpp \
    drawer.cpp \
    textinfo.cpp \
    switcher.cpp \
    chooseinterface.cpp \
    settingform.cpp \
    music.cpp \
    solution.cpp

HEADERS  += \
    enviroment.h \
    block.h \
    way.h \
    welcomeinterface.h \
    designinterface.h \
    gameinterface.h \
    gameinfo.h \
    drawer.h \
    textinfo.h \
    switcher.h \
    chooseinterface.h \
    settingform.h \
    music.h \
    solution.h

FORMS    += \
    welcomeinterface.ui \
    designinterface.ui \
    gameinterface.ui \r
    chooseinterface.ui \
    settingform.ui \
    gamedialog.ui

RESOURCES += \
    resource.qrc

RC_FILE = ./icon/icon.rc
