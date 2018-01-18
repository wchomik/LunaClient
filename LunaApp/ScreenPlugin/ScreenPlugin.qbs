import qbs
import Plugin

Plugin {
    name: "ScreenPlugin"

    Depends { name: "cpp" }

    files: [
        "screenprovider.h",
        "screenmodel.h",
        "array2d.h",
        "screenplugin.h",
        "screeneffectplugin.h",

        "screenprovider.cpp",
        "screenmodel.cpp",
        "screenplugin.cpp",
        "screeneffectplugin.cpp",

        "qml.qrc",
    ]

    cpp.includePaths: ["./"]

    Group {
        name: "Windows"
        condition: qbs.targetOS.contains("windows")
        files: [
            "win32/screencapture.h",
            "win32/shaders.h",
            "win32/win32errorhandling.h",
            "win32/screencapture.cpp",
            "win32/win32errorhandling.cpp",
        ]
    }

    Properties {
        condition: qbs.targetOS.contains("windows")
        cpp.includePaths: outer.concat("./win32/")
        cpp.dynamicLibraries: outer.concat(["d3d11", "dxgi"])
        cpp.minimumWindowsVersion: "6.3"
    }
}
