import qbs
import Plugin

Plugin {
    name: "SecureNetworkPlugin"
    files: [
        "qml.qrc",
    ]

    Depends { name: "libLuna" }
    Depends { name: "Qt.network" }
    Group {
        name: "sources"
        files: [
            "controlsocket.cpp",
            "dtlssocket.cpp",
            "securehost.cpp",
            "securenetworkconnector.cpp",
            "securenetworkconnectorplugin.cpp",
            "securenetworkplugin.cpp",
            "StrandSerializer.cpp",
            "hostdiscovery.cpp",
        ]
    }

    Group {
        name: "headers"
        files: [
            "controlsocket.h",
            "dtlssocket.h",
            "securehost.h",
            "securenetworkconnector.h",
            "securenetworkconnectorplugin.h",
            "securenetworkplugin.h",
            "StrandSerializer.h",
            "hostdiscovery.h",
            "sslsink.hpp",
        ]
    }
}
