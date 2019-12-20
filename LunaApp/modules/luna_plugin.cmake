macro(luna_plugin)
    set(options)
    set(oneValueArgs NAME)
    set(multiValueArgs SOURCES)
    cmake_parse_arguments(PLUGIN "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
    
    add_library(${PLUGIN_NAME} MODULE ${PLUGIN_SOURCES})
    
    target_link_libraries(${PLUGIN_NAME}
        Qt5::Quick
        "interface"
        prism
    )

    install(TARGETS ${PLUGIN_NAME} DESTINATION lib)
endmacro()
