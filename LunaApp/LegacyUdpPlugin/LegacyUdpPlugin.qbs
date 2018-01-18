import qbs
import Plugin

Plugin {
    Depends { name: "cpp" }

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

    cpp.includePaths: ["./"]

    Group {
        name: "Windows"
        condition: qbs.targetOS.contains("windows")
        files: [
            "win32/socket.h",
            "win32/address.h",
            "win32/networkinterface.h",
            "win32/socket.cpp",
            "win32/address.cpp",
            "win32/networkinterface.cpp",
        ]
    }

    Properties {
        condition: qbs.targetOS.contains("windows")
        cpp.includePaths: outer.concat("./win32/")
        cpp.dynamicLibraries: outer.concat(["Ws2_32", "Iphlpapi"])
        cpp.minimumWindowsVersion: "6.2"
    }
}
