include(luna_plugin)

set(PLUGIN_NAME AudioPlugin)

luna_plugin(
    NAME
        ${PLUGIN_NAME}
    SOURCES
        "audiomodel.h"
        "audiochannelprocessor.h"
        "audioprovider.h"
        "fft.h"
        "samplebuffer.h"
        "audioplugin.h"
        "audioeffectplugin.h"

        "audiomodel.cpp"
        "audiochannelprocessor.cpp"
        "audioprovider.cpp"
        "fft.cpp"
        "samplebuffer.cpp"
        "audioplugin.cpp"
        "audioeffectplugin.cpp"

        "qml.qrc"
)

target_link_libraries(${PLUGIN_NAME}
    CONAN_PKG::fftw
)

if(WIN32)
    target_sources(${PLUGIN_NAME} PRIVATE
        "win32/audiocapture.h"
        "win32/win32errorhandling.h"
        "win32/audiocapture.cpp"
        "win32/win32errorhandling.cpp"
    )
    target_include_directories(${PLUGIN_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/win32"
    )
    target_link_libraries(${PLUGIN_NAME}
        # winmm
        ksuser
        # uuid
        # ole32
    )
endif()
