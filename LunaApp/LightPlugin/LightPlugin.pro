TEMPLATE = lib
CONFIG += plugin
QT += qml \
      quick
INCLUDEPATH += ../LunaCore
HEADERS += \
        lightplugin.h
SOURCES += \
        lightplugin.cpp
TARGET = $$qtLibraryTarget(LightPlugin)
DESTDIR = ../plugins


EXAMPLE_FILES = lightplugin.json



CONFIG += install_ok
DISTFILES +=

RESOURCES += \
    qml.qrc

#LunaCore
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../LunaCore/release/ -lLunaCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../LunaCore/debug/ -lLunaCore
else:unix: LIBS += -L$$OUT_PWD/../LunaCore/ -lLunaCore

INCLUDEPATH += $$PWD/../LunaCore
DEPENDPATH += $$PWD/../LunaCore
