project(Luna)


find_package(Qt5Quick CONFIG REQUIRED)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_executable(${PROJECT_NAME} 
    "main.cpp"
    "manager.cpp"

    "manager.h"
    
    "qml.qrc"
)

target_link_libraries(${PROJECT_NAME}
    Qt5::Quick
    LunaCore
    LunaPlugin
)
