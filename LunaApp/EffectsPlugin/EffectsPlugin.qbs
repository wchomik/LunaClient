import qbs
import Plugin

Plugin {
    name: "EffectsPlugin"

    files: [
        "effectsplugin.cpp",
        "flameprovider.cpp",
        "flameeffectplugin.cpp",
        "flamemodel.cpp",
        "noise.cpp",
        "plasmaprovider.cpp",
        "plasmamodel.cpp",
        "plasmaeffectplugin.cpp",

        "effectsplugin.h",
        "flameprovider.h",
        "flameeffectplugin.h",
        "flamemodel.h",
        "noise.h",
        "plasmaprovider.h",
        "plasmamodel.h",
        "plasmaeffectplugin.h",

        "qml.qrc",
    ]
}
