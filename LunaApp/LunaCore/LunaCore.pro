QT       -= gui

TARGET = LunaCore
TEMPLATE = lib

DEFINES += LUNACORE_LIBRARY

INCLUDEPATH += $$(EIGEN)

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
    samplebuffer.cpp \
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
    samplebuffer.h \
    strand.h

SUBDIRS += \
    LunaCore.pro

win32 {
    QMAKE_CXXFLAGS += -arch:AVX
    INCLUDEPATH += ./win32
    SOURCES += \
        win32/socket.cpp
    HEADERS += \
        win32/socket.h
    LIBS += -lWs2_32
    DEFINES += _USE_MATH_DEFINES NOMINMAX WIN32_LEAN_AND_MEAN
}

DISTFILES +=
