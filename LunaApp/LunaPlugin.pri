include(Common.pri)

TEMPLATE = lib
CONFIG += plugin
QT += qml \
      quick

include(LunaCore.pri)

DESTDIR = ../LunaApp/plugins
