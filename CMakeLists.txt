cmake_minimum_required(VERSION 3.0.0)

project(LunaClient)

include("${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake")
conan_basic_setup(TARGETS)

add_subdirectory(libLuna)
add_subdirectory(LunaApp)
