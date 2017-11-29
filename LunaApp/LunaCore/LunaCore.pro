include(../Common.pri)

TEMPLATE = lib
QT -= gui
QT += quick
DEFINES += LUNACORE_LIBRARY


SOURCES += \
    binarystream.cpp \
    colorprocessor.cpp \
    colorspace.cpp \
    colorutils.cpp \
    connector.cpp \
    connectorudplegacy.cpp \
    lunaplugin.cpp \
    manager.cpp \
    provider.cpp \
    strand.cpp

HEADERS += \
    lunacore_global.h \
    binarystream.h \
    colormode.h \
    colorprocessor.h \
    colorspace.h \
    colorutils.h \
    connector.h \
    connectorudplegacy.h \
    delegate.h \
    event.h \
    lunaplugin.h \
    manager.h \
    provider.h \
    strand.h

win32 {
    INCLUDEPATH += ./win32
    SOURCES += \
        win32/socket.cpp
    HEADERS += \
        win32/socket.h
    LIBS += -lWs2_32
}
