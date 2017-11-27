TEMPLATE = lib
CONFIG += plugin
QT += qml \
      quick

INCLUDEPATH += ../LunaCore
INCLUDEPATH += $$(EIGEN)

HEADERS += \
    lightplugin.h \
    lightprovider.h \
    lightmodel.h
SOURCES += \
    lightplugin.cpp \
    lightprovider.cpp \
    lightmodel.cpp

TARGET = $$qtLibraryTarget(LightPlugin)
DESTDIR = ../plugins

CONFIG += install_ok

RESOURCES += \
    qml.qrc

win32 {
    INCLUDEPATH += ./win32
    HEADERS += \
        win32/themecolor.h
    SOURCES += \
        win32/themecolor.cpp
}

#LunaCore
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../LunaCore/release/ -lLunaCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../LunaCore/debug/ -lLunaCore
else:unix: LIBS += -L$$OUT_PWD/../LunaCore/ -lLunaCore

INCLUDEPATH += $$PWD/../LunaCore
DEPENDPATH += $$PWD/../LunaCore
