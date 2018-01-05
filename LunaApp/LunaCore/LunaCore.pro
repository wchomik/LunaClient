include(../Common.pri)

TEMPLATE = lib
QT -= gui
QT += quick
DEFINES += LUNACORE_LIBRARY

DESTDIR = ../LunaApp

SOURCES += \
    colorprocessor.cpp \
    colorspace.cpp \
    colorutils.cpp \
    connector.cpp \
    manager.cpp \
    provider.cpp \
    strand.cpp

HEADERS += \
    lunacore_global.h \
    colormode.h \
    colorprocessor.h \
    colorspace.h \
    colorutils.h \
    connector.h \
    delegate.h \
    event.h \
    manager.h \
    provider.h \
    strand.h \
    range.h
