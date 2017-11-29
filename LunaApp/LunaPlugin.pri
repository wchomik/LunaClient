include(Common.pri)

TEMPLATE = lib
CONFIG += plugin
QT += qml \
      quick

include(LunaCore.pri)

DESTDIR = ../LunaApp/plugins

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../LunaPlugin/release/ -lLunaPlugin
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../LunaPlugin/debug/ -lLunaPlugin
else:unix: LIBS += -L$$OUT_PWD/../LunaPlugin/ -lLunaPlugin

INCLUDEPATH += ../LunaPlugin
DEPENDPATH += ../LunaPlugin
