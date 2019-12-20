project(Luna)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_executable(${PROJECT_NAME} 
    "main.cpp"
    "Manager.cpp"
    "Luna.cpp"
    "TabsModel.cpp"

    "Manager.hpp"
    "Luna.hpp"
    "TabsModel.hpp"
    
    "resources/qml.qrc"
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC 
        Qt5::Quick
        "interface"
)

configure_file("qt.conf" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/qt.conf")
