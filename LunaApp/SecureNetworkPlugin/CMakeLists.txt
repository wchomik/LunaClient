include(luna_plugin)

set(PLUGIN_NAME SecureNetworkPlugin)

luna_plugin(
    NAME 
        ${PLUGIN_NAME}
    SOURCES
    
    "controlsocket.cpp"
    "dtlssocket.cpp"
    "securehost.cpp"
    "securenetworkconnector.cpp"
    "securenetworkconnectorplugin.cpp"
    "securenetworkplugin.cpp"
    "StrandSerializer.cpp"
    "hostdiscovery.cpp"

    "controlsocket.h"
    "dtlssocket.h"
    "securehost.h"
    "securenetworkconnector.h"
    "securenetworkconnectorplugin.h"
    "securenetworkplugin.h"
    "StrandSerializer.h"
    "hostdiscovery.h"
    "sslsink.hpp"

    "qml.qrc"
)

find_package(Qt5Network CONFIG REQUIRED)
target_link_libraries(${PLUGIN_NAME} 
    libLuna
    Qt5::Network
)
