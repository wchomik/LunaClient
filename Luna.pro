QT += qml quick
QT += network

CONFIG += c++11

INCLUDEPATH += $$(EIGEN)

SOURCES += main.cpp \
    luna.cpp \
    lunalegacy.cpp \
    lunaworker.cpp \
    lunaprovider.cpp \
    lunailluminationprovider.cpp \
    lunamanager.cpp \
    colorspace.cpp \
    colorprocessor.cpp \
    lunaaudioprovider.cpp \
    samplebuffer.cpp \
    fft.cpp \
    colorutils.cpp \
    audiochannelprocessor.cpp \
    lunascreenprovider.cpp \
    lunaproviderfactory.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    luna.h \
    lunalegacy.h \
    lunaworker.h \
    colorutils.h \
    binarystream.h \
    lunaprovider.h \
    lunaconfig.h \
    lunailluminationprovider.h \
    lunamanager.h \
    colorspace.h \
    colormode.h \
    colorprocessor.h \
    lunaaudioprovider.h \
    samplebuffer.h \
    fft.h \
    audiochannelprocessor.h \
    array2d.h \
    lunascreenprovider.h \
    lunaproviderfactory.h

LIBS += -L$$PWD/Lib/

INCLUDEPATH += $$PWD/Include
DEPENDPATH += $$PWD/Include

win32 {
    INCLUDEPATH += ./win32
    SOURCES += ./win32/audiocapture.cpp \
        win32/screencapture.cpp \
        win32/win32errorhandling.cpp
    HEADERS += ./win32/audiocapture.h \
        win32/screencapture.h \
        win32/win32errorhandling.h \
        win32/shaders.h
    LIBS += -lmmdevapi -lole32 -llibfftw3f-3 -ld3d11 -ldxgi
    DEFINES += _USE_MATH_DEFINES
}
