include(luna_plugin)

luna_plugin(
    NAME
        EffectsPlugin
    SOURCES
        "EffectsPlugin.cpp"
        "FlameProvider.cpp"
        "FlameEffectPlugin.cpp"
        "FlameModel.cpp"
        "Noise.cpp"
        "PlasmaProvider.cpp"
        "PlasmaModel.cpp"
        "PlasmaEffectPlugin.cpp"

        "EffectsPlugin.hpp"
        "FlameProvider.hpp"
        "FlameEffectPlugin.hpp"
        "FlameModel.hpp"
        "Noise.hpp"
        "PlasmaProvider.hpp"
        "PlasmaModel.hpp"
        "PlasmaEffectPlugin.hpp"

        "qml.qrc"
)