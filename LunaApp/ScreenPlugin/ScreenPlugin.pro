include(../LunaPlugin.pri)

HEADERS += \
    screenprovider.h \
    screenmodel.h \
    array2d.h \
    screentab.h \
    screenplugin.h
SOURCES += \
    screenprovider.cpp \
    screenmodel.cpp \
    screentab.cpp \
    screenplugin.cpp

RESOURCES += \
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
}

DISTFILES += \
    win32/PassThrough.hlsl \
    win32/VertexShader.hlsl
