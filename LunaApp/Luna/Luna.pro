include(../Common.pri)
QT += qml quick

SOURCES += \
    main.cpp

HEADERS +=

RESOURCES += qml.qrc

DESTDIR = ../LunaApp

include(../LunaCore.pri)

LIBS += -L../LunaApp -lLunaPlugin

INCLUDEPATH += $$PWD/../LunaPlugin
DEPENDPATH += $$PWD/../LunaPlugin

TRANSLATIONS += luna_pl.ts
