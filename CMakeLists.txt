cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_definitions(_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS=1)
cmake_policy(SET CMP0091 NEW)
project(LunaClient)

include("${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake")
conan_basic_setup(TARGETS)
set_target_properties(CONAN_PKG::eigen PROPERTIES IMPORTED_GLOBAL TRUE)
add_library(Eigen3::Eigen ALIAS CONAN_PKG::eigen)

add_subdirectory(prism)
add_subdirectory(lunaProto)
add_subdirectory(LunaApp)
