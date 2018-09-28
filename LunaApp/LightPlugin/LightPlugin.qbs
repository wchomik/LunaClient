import qbs
import Plugin

Plugin {
    name: "LightPlugin"
    Depends { name: "cpp" }

    files: [
        "lightprovider.h",
        "lightmodel.h",
        "lightplugin.h",
        "lighteffectplugin.h",
        "lightprovider.cpp",
        "lightmodel.cpp",
        "lightplugin.cpp",
        "lighteffectplugin.cpp",
        "qml.qrc",
    ]

    Group {
        name: "Windows"
        condition: qbs.targetOS.contains("windows")
        files: [
            "win32/themecolor.h",
            "win32/themecolor.cpp",
        ]
    }

    Properties {
        condition: qbs.targetOS.contains("windows")
        cpp.includePaths: outer.concat("./win32")
    }
}
