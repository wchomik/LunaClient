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
            "dtlssocket.cpp",
            "securehost.cpp",
            "securenetworkconnector.cpp",
            "securenetworkconnectorplugin.cpp",
            "securenetworkplugin.cpp",
            "hostdiscovery.cpp",
        ]
    }

    Group {
        name: "headers"
        files: [
            "dtlssocket.h",
            "securehost.h",
            "securenetworkconnector.h",
            "securenetworkconnectorplugin.h",
            "securenetworkplugin.h",
            "hostdiscovery.h",
            "sslsink.hpp",
        ]
    }
}
