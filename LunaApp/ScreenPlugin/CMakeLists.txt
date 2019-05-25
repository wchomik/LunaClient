include(luna_plugin)

set(PLUGIN_NAME ScreenPlugin)

luna_plugin(
    NAME 
        ${PLUGIN_NAME}
    SOURCES
        "ScreenProvider.hpp"
        "ScreenModel.hpp"
        "Array2d.hpp"
        "ScreenPlugin.hpp"
        "ScreenEffectPlugin.hpp"

        "ScreenProvider.cpp"
        "ScreenModel.cpp"
        "ScreenPlugin.cpp"
        "ScreenEffectPlugin.cpp"

        "qml.qrc"
)

target_compile_definitions(${PLUGIN_NAME} PUBLIC NOMINMAX)

target_include_directories(${PLUGIN_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

if(WIN32)
    target_sources(${PLUGIN_NAME} PRIVATE  
        "win32/ScreenCapture.hpp"
        "win32/shaders.h"
        "win32/win32errorhandling.h"
        "win32/ScreenCapture.cpp"
        "win32/win32errorhandling.cpp"
    )
    target_include_directories(${PLUGIN_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/win32"
    )
    target_link_libraries(${PLUGIN_NAME}
        d3d11
        dxgi
    )
endif()
