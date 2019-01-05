project(LunaCore)


find_package(Qt5Quick CONFIG REQUIRED)
set(CMAKE_AUTOMOC ON)

add_library(${PROJECT_NAME} SHARED
    "source/colorprocessor.cpp"
    "source/colorspace.cpp"
    "source/colorutils.cpp"
    "source/connector.cpp"
    "source/manager.cpp"
    "source/provider.cpp"
    "source/strand.cpp"

    "include/lunacore/lunacore_global.h"
    "include/lunacore/colormode.h"
    "include/lunacore/colorprocessor.h"
    "include/lunacore/colorspace.h"
    "include/lunacore/colorutils.h"
    "include/lunacore/connector.h"
    "include/lunacore/delegate.h"
    "include/lunacore/event.h"
    "include/lunacore/manager.h"
    "include/lunacore/provider.h"
    "include/lunacore/strand.h"
    "include/lunacore/range.h"
)

target_include_directories(${PROJECT_NAME} 
    INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include"
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/lunacore"
)

target_link_libraries(${PROJECT_NAME}
    Qt5::Quick
    CONAN_PKG::eigen
)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE LUNACORE_LIBRARY=1
)
