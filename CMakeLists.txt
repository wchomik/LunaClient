cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_CXX_STANDARD 17)
project(LunaClient)

include("${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake")
conan_basic_setup(TARGETS)
set_target_properties(CONAN_PKG::eigen PROPERTIES IMPORTED_GLOBAL TRUE)
add_library(Eigen3::Eigen ALIAS CONAN_PKG::eigen)

add_subdirectory(prism)
add_subdirectory(lunaProto)
add_subdirectory(LunaApp)
