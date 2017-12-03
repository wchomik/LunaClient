include(../LunaPlugin.pri)

HEADERS += \
    lightprovider.h \
    lightmodel.h \
    lightplugin.h \
    lighteffectplugin.h
SOURCES += \
    lightprovider.cpp \
    lightmodel.cpp \
    lightplugin.cpp \
    lighteffectplugin.cpp

RESOURCES += \
    qml.qrc

win32 {
    INCLUDEPATH += ./win32
    HEADERS += \
        win32/themecolor.h
    SOURCES += \
        win32/themecolor.cpp
}
