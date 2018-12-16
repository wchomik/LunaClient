include(luna_plugin)

luna_plugin(
    NAME 
        LightPlugin
    SOURCES
        "lightprovider.h"
        "lightmodel.h"
        "lightplugin.h"
        "lighteffectplugin.h"
        "lightprovider.cpp"
        "lightmodel.cpp"
        "lightplugin.cpp"
        "lighteffectplugin.cpp"
        "qml.qrc"
)

if(WIN32)
    target_sources(LightPlugin PRIVATE  
        "win32/themecolor.h"
        "win32/themecolor.cpp"
    )
    target_include_directories(LightPlugin PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/win32"
    )
endif()
