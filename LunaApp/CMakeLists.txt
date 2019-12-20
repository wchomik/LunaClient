project(LunaApp)


list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/modules")

find_package(Qt5Quick CONFIG REQUIRED)
add_subdirectory(interface)

add_subdirectory(SecureNetworkPlugin)

add_subdirectory(LightPlugin)
add_subdirectory(EffectsPlugin)
if(WIN32)
    add_subdirectory(AudioPlugin)
    add_subdirectory(ScreenPlugin)
endif()

add_subdirectory(Luna)
