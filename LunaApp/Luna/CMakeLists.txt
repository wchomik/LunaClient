project(Luna)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_executable(${PROJECT_NAME} WIN32
    "main.cpp"
    "Manager.cpp"
    "Luna.cpp"
    "TabsModel.cpp"

    "Manager.hpp"
    "Luna.hpp"
    "TabsModel.hpp"

    "resources/qml.qrc"

    "luna.rc"
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Qt5::Quick
        "interface"
)

configure_file("qt.conf" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/qt.conf")

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

install(CODE "
execute_process(COMMAND \"${CONAN_QT_ROOT}/bin/windeployqt.exe\" \"${CMAKE_INSTALL_PREFIX}/bin/Luna.exe\" --qmldir=\"${CMAKE_CURRENT_SOURCE_DIR}/..\")
")
# install(FILES "qt.conf" DESTINATION bin)
