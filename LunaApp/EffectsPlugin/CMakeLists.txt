include(luna_plugin)

luna_plugin(
    NAME
        EffectsPlugin
    SOURCES
        "effectsplugin.cpp"
        "flameprovider.cpp"
        "flameeffectplugin.cpp"
        "flamemodel.cpp"
        "noise.cpp"
        "plasmaprovider.cpp"
        "plasmamodel.cpp"
        "plasmaeffectplugin.cpp"

        "effectsplugin.h"
        "flameprovider.h"
        "flameeffectplugin.h"
        "flamemodel.h"
        "noise.h"
        "plasmaprovider.h"
        "plasmamodel.h"
        "plasmaeffectplugin.h"

        "qml.qrc"
)