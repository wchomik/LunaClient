include(luna_plugin)

set(PLUGIN_NAME SecureNetworkPlugin)

luna_plugin(
    NAME 
        ${PLUGIN_NAME}
    SOURCES

    "dtlssocket.cpp"
    "securehost.cpp"
    "securenetworkconnector.cpp"
    "securenetworkconnectorplugin.cpp"
    "securenetworkplugin.cpp"
    "StrandSerializer.cpp"
    "hostdiscovery.cpp"

    "dtlssocket.h"
    "securehost.h"
    "securenetworkconnector.h"
    "securenetworkconnectorplugin.h"
    "securenetworkplugin.h"
    "StrandSerializer.h"
    "hostdiscovery.h"

    "qml.qrc"
)

find_package(Qt5Network CONFIG REQUIRED)
target_link_libraries(${PLUGIN_NAME} 
    libLuna
    lunaProto
    Qt5::Network
)
