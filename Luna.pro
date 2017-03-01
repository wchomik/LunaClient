QT += qml quick
QT += network

CONFIG += c++11

INCLUDEPATH += $$(EIGEN)

SOURCES += main.cpp \
    luna/audiochannelprocessor.cpp \
    luna/colorprocessor.cpp \
    luna/colorspace.cpp \
    luna/colorutils.cpp \
    luna/fft.cpp \
    luna/samplebuffer.cpp \
    luna/audioprovider.cpp \
    luna/illuminationprovider.cpp \
    luna/manager.cpp \
    luna/provider.cpp \
    luna/worker.cpp \
    luna/screenprovider.cpp \
    luna/providerfactory.cpp \
    model/settings.cpp \
    luna/connection.cpp

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
    luna/array2d.h \
    luna/audiochannelprocessor.h \
    luna/binarystream.h \
    luna/colormode.h \
    luna/colorprocessor.h \
    luna/colorspace.h \
    luna/colorutils.h \
    luna/fft.h \
    luna/samplebuffer.h \
    luna/providerfactory.h \
    luna/screenprovider.h \
    luna/worker.h \
    luna/provider.h \
    luna/manager.h \
    luna/illuminationprovider.h \
    luna/config.h \
    luna/audioprovider.h \
    model/settings.h \
    delegate.h \
    event.h \
    luna/connection.h

LIBS += -L$$PWD/Lib/

INCLUDEPATH += $$PWD/Include
DEPENDPATH += $$PWD/Include

win32 {
    QMAKE_CXXFLAGS += -arch:AVX
    INCLUDEPATH += ./win32
    SOURCES += ./win32/audiocapture.cpp \
        win32/screencapture.cpp \
        win32/win32errorhandling.cpp \
        win32/socket.cpp
    HEADERS += ./win32/audiocapture.h \
        win32/screencapture.h \
        win32/win32errorhandling.h \
        win32/shaders.h \
        win32/socket.h
    LIBS += -lmmdevapi -lole32 -llibfftw3f-3 -ld3d11 -ldxgi -lWs2_32
    DEFINES += _USE_MATH_DEFINES
}
