include(luna_plugin)

luna_plugin(
    NAME 
        LightPlugin
    SOURCES
        "LightProvider.hpp"
        "LightModel.hpp"
        "LightPlugin.hpp"
        "LightEffectPlugin.hpp"

        "LightProvider.cpp"
        "LightModel.cpp"
        "LightPlugin.cpp"
        "LightEffectPlugin.cpp"
        
        "qml.qrc"
)

if(WIN32)
    target_sources(LightPlugin PRIVATE  
        "win32/ThemeColor.hpp"
        "win32/ThemeColor.cpp"
    )
    target_include_directories(LightPlugin PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/win32"
    )
endif()
