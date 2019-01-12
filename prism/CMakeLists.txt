project(prism)

set(CMAKE_CXX_STANDARD 14)

add_library(${PROJECT_NAME}
    "include/prism/Prism.hpp"
    "source/Prism.cpp"    
)

target_include_directories(${PROJECT_NAME} 
    INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include"
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/prism"
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC Eigen3::Eigen
)

