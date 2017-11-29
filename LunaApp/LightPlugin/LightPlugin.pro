include(../LunaPlugin.pri)

HEADERS += \
    lightplugin.h \
    lightprovider.h \
    lightmodel.h
SOURCES += \
    lightplugin.cpp \
    lightprovider.cpp \
    lightmodel.cpp

RESOURCES += \
    qml.qrc

win32 {
    INCLUDEPATH += ./win32
    HEADERS += \
        win32/themecolor.h
    SOURCES += \
        win32/themecolor.cpp
}
