project(interface)

set(CMAKE_CXX_STANDARD 14)

find_package(Qt5Quick CONFIG REQUIRED)
set(CMAKE_AUTOMOC ON)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} 
    INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries(${PROJECT_NAME}
    INTERFACE 
        Qt5::Quick
        Eigen3::Eigen
        prism
)

