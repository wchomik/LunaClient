TEMPLATE = lib
CONFIG += plugin
QT += qml \
      quick

INCLUDEPATH += ../LunaCore
INCLUDEPATH += $$(EIGEN)

HEADERS += \
    audioplugin.h \
    audiomodel.h \
    audiochannelprocessor.h \
    audioprovider.h \
    fft.h \
    fftw3.h \
    samplebuffer.h
SOURCES += \
    audioplugin.cpp \
    audiomodel.cpp \
    audiochannelprocessor.cpp \
    audioprovider.cpp \
    fft.cpp \
    samplebuffer.cpp

TARGET = $$qtLibraryTarget(AudioPlugin)
DESTDIR = ../plugins

CONFIG += install_ok

RESOURCES += \
    qml.qrc

win32 {
    INCLUDEPATH += ./win32
    SOURCES += \
        win32/audiocapture.cpp \
        win32/win32errorhandling.cpp

    HEADERS += \
        win32/audiocapture.h \
        win32/win32errorhandling.h

    LIBS += -lmmdevapi -lole32 -llibfftw3f-3
    DEFINES += _USE_MATH_DEFINES NOMINMAX WIN32_LEAN_AND_MEAN

    LIBS += -L$$PWD/lib/
}

#LunaCore
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../LunaCore/release/ -lLunaCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../LunaCore/debug/ -lLunaCore
else:unix: LIBS += -L$$OUT_PWD/../LunaCore/ -lLunaCore

INCLUDEPATH += $$PWD/../LunaCore
DEPENDPATH += $$PWD/../LunaCore

