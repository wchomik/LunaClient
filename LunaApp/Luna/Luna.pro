QT += qml quick

CONFIG += c++14

INCLUDEPATH += $$(EIGEN)

SOURCES += \
    main.cpp \
    luna/illuminationprovider.cpp \
    model/settings.cpp \
    model/lightprovidersettings.cpp \
    win32/themecolor.cpp

RESOURCES += qml.qrc

HEADERS += \
    luna/illuminationprovider.h \
    model/settings.h \
    model/providersettings.h \
    model/lightprovidersettings.h \
    win32/themecolor.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


LIBS += -L$$PWD/Lib/

INCLUDEPATH += $$PWD/Include
DEPENDPATH += $$PWD/Include

win32 {
    QMAKE_CXXFLAGS += -arch:AVX
    INCLUDEPATH += ./win32
    #LIBS += -lmmdevapi -lole32 -llibfftw3f-3 -ld3d11 -ldxgi
    DEFINES += _USE_MATH_DEFINES NOMINMAX WIN32_LEAN_AND_MEAN
}

DISTFILES += \
    win32/PassThrough.hlsl \
    win32/VertexShader.hlsl

#LunaCore
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../LunaCore/release/ -lLunaCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../LunaCore/debug/ -lLunaCore
else:unix: LIBS += -L$$OUT_PWD/../LunaCore/ -lLunaCore

INCLUDEPATH += $$PWD/../LunaCore
DEPENDPATH += $$PWD/../LunaCore
