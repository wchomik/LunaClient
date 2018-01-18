import qbs
import Plugin

Plugin {
    name: "AudioPlugin"

    Depends { name: "cpp" }
    Depends { name: "fftw3" }

    files: [
        "audiomodel.h",
        "audiochannelprocessor.h",
        "audioprovider.h",
        "fft.h",
        "samplebuffer.h",
        "audioplugin.h",
        "audioeffectplugin.h",

        "audiomodel.cpp",
        "audiochannelprocessor.cpp",
        "audioprovider.cpp",
        "fft.cpp",
        "samplebuffer.cpp",
        "audioplugin.cpp",
        "audioeffectplugin.cpp",

        "qml.qrc",
    ]

    cpp.includePaths: ["./"]

    Group {
        name: "Windows"
        condition: qbs.targetOS.contains("windows")
        files: [
            "win32/audiocapture.h",
            "win32/win32errorhandling.h",
            "win32/audiocapture.cpp",
            "win32/win32errorhandling.cpp",
        ]
    }

    Properties {
        condition: qbs.targetOS.contains("windows")
        cpp.includePaths: outer.concat("./win32/")
        cpp.dynamicLibraries: outer.concat(["mmdevapi", "ole32"])
        cpp.minimumWindowsVersion: "6.3"
    }
}
