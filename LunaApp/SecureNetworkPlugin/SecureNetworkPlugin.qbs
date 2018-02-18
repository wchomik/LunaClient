import qbs
import Plugin

Plugin {
    Depends { name: "TLS" }

    Group {
        name: "sources"
        files: [
            "securenetworkconnectorplugin.cpp",

        ]
    }

    Group {
        name: "headers"
        files: [
            "securenetworkconnector.h",
            "securenetworkconnectorplugin.h",
        ]
    }
}
