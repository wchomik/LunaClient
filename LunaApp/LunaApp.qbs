import qbs

Project {
    references: [
        "LunaCore/LunaCore.qbs",
        "LunaPlugin/LunaPlugin.qbs",
        "Luna/Luna.qbs",

        "LightPlugin/LightPlugin.qbs",
        "EffectsPlugin/EffectsPlugin.qbs",
        "ScreenPlugin/ScreenPlugin.qbs",
        "AudioPlugin/AudioPlugin.qbs",
        "SecureNetworkPlugin/SecureNetworkPlugin.qbs",
    ]

    property string binDir: "bin"
    property string pluginsDir: "bin/plugins"
}
