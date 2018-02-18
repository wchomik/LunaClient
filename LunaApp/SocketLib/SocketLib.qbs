import qbs

StaticLibrary {
    Depends { name: "cpp" }

    Group {
        name: "windows"
        condition: qbs.targetOS.contains("windows")
        prefix: "win32/"
        files: [
            "socket.h",
            "address.h",
            "networkinterface.h",
            "socket.cpp",
            "address.cpp",
            "networkinterface.cpp",
        ]

        cpp.includePaths: outer.concat("./win32/")
        cpp.dynamicLibraries: outer.concat(["Ws2_32", "Iphlpapi"])
        cpp.defines: outer.concat(["_USE_MATH_DEFINES", "NOMINMAX", "WIN32_LEAN_AND_MEAN"])
    }

    Export {
        condition: qbs.targetOS.contains("windows")
        Depends { name: "cpp" }
        cpp.dynamicLibraries: ["Ws2_32", "Iphlpapi"]
        cpp.minimumWindowsVersion: "6.2"
        cpp.includePaths: "win32/"
        cpp.defines: ["_USE_MATH_DEFINES", "NOMINMAX", "WIN32_LEAN_AND_MEAN"]
    }
}
