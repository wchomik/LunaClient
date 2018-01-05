include(../LunaPlugin.pri)

SOURCES += \
    udplegacyconnectorplugin.cpp \
    connectorudplegacy.cpp \
    legacyudpplugin.cpp \
    binarystream.cpp \
    win32/address.cpp \
    win32/networkinterface.cpp

HEADERS += \
    udplegacyconnectorplugin.h \
    connectorudplegacy.h \
    legacyudpplugin.h \
    binarystream.h \
    win32/address.h \
    win32/networkinterface.h


win32 {
    INCLUDEPATH += ./win32
    SOURCES += \
        win32/socket.cpp
    HEADERS += \
        win32/socket.h
    LIBS += -lWs2_32 -lIphlpapi
}

RESOURCES += \
    qml.qrc
