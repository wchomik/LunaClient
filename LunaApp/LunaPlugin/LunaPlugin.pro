include(../Common.pri)
include(../LunaCore.pri)
QT       += quick
QT       -= gui

TEMPLATE = lib

DEFINES += LUNAPLUGIN_LIBRARY

SOURCES += \
        lunaplugin.cpp \
    luna.cpp \
    lunatab.cpp \
    tabsmodel.cpp

HEADERS += \
        lunaplugin.h \
        lunaplugin_global.h \ 
    luna.h \
    lunatab.h \
    tabsmodel.h

DESTDIR = ../LunaApp
