include(../Common.pri)
QT += qml quick

SOURCES += \
    main.cpp \
    luna.cpp

HEADERS += \
    luna.h

RESOURCES += qml.qrc

DESTDIR = ../LunaApp

include(../LunaCore.pri)
