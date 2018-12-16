project(LunaPlugin)

set(CMAKE_CXX_STANDARD 14)

find_package(Qt5Quick CONFIG REQUIRED)
set(CMAKE_AUTOMOC ON)

add_library(${PROJECT_NAME} SHARED
    "source/lunaplugin.cpp"
    "source/luna.cpp"
    "source/tabsmodel.cpp"
    "source/connectorplugin.cpp"
    "source/configurableplugin.cpp"
    "source/effectplugin.cpp"

    "include/lunaplugin/lunaplugin.h"
    "include/lunaplugin/lunaplugin_global.h"
    "include/lunaplugin/luna.h"
    "include/lunaplugin/tabsmodel.h"
    "include/lunaplugin/connectorplugin.h"
    "include/lunaplugin/configurableplugin.h"
    "include/lunaplugin/effectplugin.h"
)

target_include_directories(${PROJECT_NAME} 
    INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include"
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/lunaplugin"
)

target_link_libraries(${PROJECT_NAME}
    Qt5::Quick
    LunaCore
)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE LUNAPLUGIN_LIBRARY=1
)

