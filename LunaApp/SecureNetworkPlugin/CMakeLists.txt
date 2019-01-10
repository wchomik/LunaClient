include(luna_plugin)

set(PLUGIN_NAME SecureNetworkPlugin)

luna_plugin(
    NAME 
        ${PLUGIN_NAME}
    SOURCES
        "DTLSSocket.cpp"
        "SecureHost.cpp"
        "SecureNetworkConnector.cpp"
        "SecureNetworkConnectorPlugin.cpp"
        "SecureNetworkPlugin.cpp"
        "StrandSerializer.cpp"
        "HostDiscovery.cpp"

        "DTLSSocket.hpp"
        "SecureHost.hpp"
        "SecureNetworkConnector.hpp"
        "SecureNetworkConnectorPlugin.hpp"
        "SecureNetworkPlugin.hpp"
        "StrandSerializer.hpp"
        "HostDiscovery.hpp"

        "qml.qrc"
)

find_package(Qt5Network CONFIG REQUIRED)
target_link_libraries(${PLUGIN_NAME} 
    lunaProto
    Qt5::Network
)
