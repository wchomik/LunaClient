project(LunaApp)


list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/modules")

add_subdirectory(LunaCore)
add_subdirectory(LunaPlugin)

add_subdirectory(SecureNetworkPlugin)

add_subdirectory(LightPlugin)
add_subdirectory(EffectsPlugin)
add_subdirectory(AudioPlugin)
add_subdirectory(ScreenPlugin)

add_subdirectory(Luna)
