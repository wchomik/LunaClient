include(luna_plugin)

set(PLUGIN_NAME ScreenPlugin)

luna_plugin(
    NAME 
        ${PLUGIN_NAME}
    SOURCES
        "screenprovider.h"
        "screenmodel.h"
        "array2d.h"
        "screenplugin.h"
        "screeneffectplugin.h"

        "screenprovider.cpp"
        "screenmodel.cpp"
        "screenplugin.cpp"
        "screeneffectplugin.cpp"

        "qml.qrc"
)

if(WIN32)
    target_sources(${PLUGIN_NAME} PRIVATE  
        "win32/screencapture.h"
        "win32/shaders.h"
        "win32/win32errorhandling.h"
        "win32/screencapture.cpp"
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
