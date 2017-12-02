include(../Common.pri)
include(../LunaCore.pri)
QT       += quick
QT       -= gui

TEMPLATE = lib

DEFINES += CONNECTORPLUGIN_LIBRARY

SOURCES += \
        connectorplugin.cpp

HEADERS += \
        connectorplugin.h \
        connectorplugin_global.h 
