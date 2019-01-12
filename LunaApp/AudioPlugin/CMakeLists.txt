include(luna_plugin)

set(PLUGIN_NAME AudioPlugin)

luna_plugin(
    NAME
        ${PLUGIN_NAME}
    SOURCES
        "AudioModel.hpp"
        "AudioChannelProcessor.hpp"
        "AudioProvider.hpp"
        "FFT.hpp"
        "SampleBuffer.hpp"
        "AudioPlugin.hpp"
        "AudioEffectPlugin.hpp"

        "AudioModel.cpp"
        "AudioChannelProcessor.cpp"
        "AudioProvider.cpp"
        "FFT.cpp"
        "SampleBuffer.cpp"
        "AudioPlugin.cpp"
        "AudioEffectPlugin.cpp"

        "qml.qrc"
)

target_link_libraries(${PLUGIN_NAME}
    CONAN_PKG::fftw
)

target_include_directories(${PLUGIN_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_compile_definitions(${PLUGIN_NAME} PRIVATE _USE_MATH_DEFINES)

if(WIN32)
    target_sources(${PLUGIN_NAME} PRIVATE
        "win32/audiocapture.hpp"
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
