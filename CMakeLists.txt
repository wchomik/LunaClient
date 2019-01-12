cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
project(LunaClient)

include("${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake")
conan_basic_setup(TARGETS)
set_target_properties(CONAN_PKG::eigen PROPERTIES IMPORTED_GLOBAL TRUE)
add_library(Eigen3::Eigen ALIAS CONAN_PKG::eigen)

add_subdirectory(prism)
add_subdirectory(lunaProto)
add_subdirectory(LunaApp)
