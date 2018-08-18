import qbs
import Plugin

Plugin {
    files: [
        "qml.qrc",
    ]
    Depends { name: "TLS" }
    Depends { name: "SocketLib" }

    Group {
        name: "sources"
        files: [
            "securenetworkconnector.cpp",
            "securenetworkconnectorplugin.cpp",
            "securenetworkplugin.cpp",
            "hostdiscovery.cpp",
        ]
    }

    Group {
        name: "headers"
        files: [
            "client_command_decoder.cpp",
            "client_command_decoder.h",
            "client_encoder.cpp",
            "client_encoder.h",
            "client_handler.h",
            "command_decoder.h",
            "command_dispatcher.cpp",
            "command_dispatcher.h",
            "command_encoder.cpp",
            "command_encoder.h",
            "packets.h",
            "securenetworkconnector.h",
            "securenetworkconnectorplugin.h",
            "securenetworkplugin.h",
            "hostdiscovery.h",
            "serializer.h",
        ]
    }
}
