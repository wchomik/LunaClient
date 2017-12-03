include(../Common.pri)
include(../LunaCore.pri)
QT += quick
QT -= gui

TEMPLATE = lib

DEFINES += LUNAPLUGIN_LIBRARY

SOURCES += \
    lunaplugin.cpp \
    luna.cpp \
    tabsmodel.cpp \
    connectorplugin.cpp \
    configurableplugin.cpp \
    effectplugin.cpp

HEADERS += \
    lunaplugin.h \
    lunaplugin_global.h \
    luna.h \
    tabsmodel.h \
    connectorplugin.h \
    configurableplugin.h \
    effectplugin.h

DESTDIR = ../LunaApp
