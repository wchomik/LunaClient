TEMPLATE = lib
CONFIG += plugin
QT += qml \
      quick

INCLUDEPATH += ../LunaCore
INCLUDEPATH += $$(EIGEN)

HEADERS += \
        screenplugin.h \
    screenprovider.h \
    screenmodel.h \
    array2d.h
SOURCES += \
        screenplugin.cpp \
    screenprovider.cpp \
    screenmodel.cpp


TARGET = $$qtLibraryTarget(ScreenPlugin)
DESTDIR = ../plugins

CONFIG += install_ok

RESOURCES += \
    qml.qrc \
    qml.qrc

win32 {
    INCLUDEPATH += ./win32
    HEADERS += \
        win32/screencapture.h \
        win32/shaders.h \
        win32/win32errorhandling.h
    SOURCES +=\
        win32/screencapture.cpp \
        win32/win32errorhandling.cpp

    LIBS += -ld3d11 -ldxgi
    DEFINES += _USE_MATH_DEFINES NOMINMAX WIN32_LEAN_AND_MEAN
}

DISTFILES += \
    win32/PassThrough.hlsl \
    win32/VertexShader.hlsl

#LunaCore
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../LunaCore/release/ -lLunaCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../LunaCore/debug/ -lLunaCore
else:unix: LIBS += -L$$OUT_PWD/../LunaCore/ -lLunaCore

INCLUDEPATH += $$PWD/../LunaCore
DEPENDPATH += $$PWD/../LunaCore
