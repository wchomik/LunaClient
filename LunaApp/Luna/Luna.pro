include(../Common.pri)
QT += qml quick

SOURCES += \
    main.cpp

HEADERS +=

RESOURCES += qml.qrc

DESTDIR = ../LunaApp

include(../LunaCore.pri)

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../LunaPlugin/release/ -lLunaPlugin
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../LunaPlugin/debug/ -lLunaPlugin
else:unix: LIBS += -L$$OUT_PWD/../LunaPlugin/ -lLunaPlugin

INCLUDEPATH += $$PWD/../LunaPlugin
DEPENDPATH += $$PWD/../LunaPlugin
