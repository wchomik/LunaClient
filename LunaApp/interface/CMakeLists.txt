project(LunaPlugin)

set(CMAKE_CXX_STANDARD 14)

find_package(Qt5Quick CONFIG REQUIRED)
set(CMAKE_AUTOMOC ON)

add_library(${PROJECT_NAME} INTERFACE
    "include/lunaplugin/Application.hpp"
    "include/lunaplugin/lunaplugin.h"
    "include/lunaplugin/luna.h"
    "include/lunaplugin/tabsmodel.h"
    "include/lunaplugin/connectorplugin.h"
    "include/lunaplugin/configurableplugin.h"
    "include/lunaplugin/effectplugin.h"
)

target_include_directories(${PROJECT_NAME} 
    INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries(${PROJECT_NAME}
    Qt5::Quick
    LunaCore
)

