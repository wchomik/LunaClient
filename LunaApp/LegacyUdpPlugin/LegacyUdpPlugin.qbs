import qbs
import Plugin

Plugin {
    Depends { name: "cpp" }
    Depends { name: "SocketLib" }

    files: [
        "udplegacyconnectorplugin.cpp",
        "connectorudplegacy.cpp",
        "legacyudpplugin.cpp",
        "binarystream.cpp",
        "udplegacyconnectorplugin.h",
        "connectorudplegacy.h",
        "legacyudpplugin.h",
        "binarystream.h",
        "qml.qrc",
    ]
}
