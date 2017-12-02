include(../LunaPlugin.pri)

HEADERS += \
    lightprovider.h \
    lightmodel.h \
    lighttab.h \
    lightplugin.h
SOURCES += \
    lightprovider.cpp \
    lightmodel.cpp \
    lighttab.cpp \
    lightplugin.cpp

RESOURCES += \
    qml.qrc

win32 {
    INCLUDEPATH += ./win32
    HEADERS += \
        win32/themecolor.h
    SOURCES += \
        win32/themecolor.cpp
}
