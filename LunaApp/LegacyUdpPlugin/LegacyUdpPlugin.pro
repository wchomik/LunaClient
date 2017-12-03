include(../LunaPlugin.pri)

SOURCES += \
    udplegacyconnectorplugin.cpp \
    connectorudplegacy.cpp \
    legacyudpplugin.cpp

HEADERS += \
    udplegacyconnectorplugin.h \
    connectorudplegacy.h \
    legacyudpplugin.h


win32 {
    INCLUDEPATH += ./win32
    SOURCES += \
        win32/socket.cpp
    HEADERS += \
        win32/socket.h
    LIBS += -lWs2_32
}
