QT += qml quick

CONFIG += c++14

INCLUDEPATH += $$(EIGEN)

SOURCES += \
    main.cpp \
    luna.cpp

RESOURCES += qml.qrc

HEADERS += \
    luna.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



INCLUDEPATH += $$PWD/Include
DEPENDPATH += $$PWD/Include

win32 {
    QMAKE_CXXFLAGS += -arch:AVX
    DEFINES += _USE_MATH_DEFINES
}

#LunaCore
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../LunaCore/release/ -lLunaCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../LunaCore/debug/ -lLunaCore
else:unix: LIBS += -L$$OUT_PWD/../LunaCore/ -lLunaCore

INCLUDEPATH += $$PWD/../LunaCore
DEPENDPATH += $$PWD/../LunaCore
