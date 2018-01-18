import qbs

Project {
    references: [
        "LunaCore/LunaCore.qbs",
        "LunaPlugin/LunaPlugin.qbs",
        "Luna/Luna.qbs",

        "LegacyUdpPlugin/LegacyUdpPlugin.qbs",

        "LightPlugin/LightPlugin.qbs",
        "EffectsPlugin/EffectsPlugin.qbs",
        "ScreenPlugin/ScreenPlugin.qbs",
        "AudioPlugin/AudioPlugin.qbs"
    ]

    property string binDir: "bin"
    property string pluginsDir: "bin/plugins"
}
