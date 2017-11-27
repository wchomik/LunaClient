TEMPLATE = subdirs

SUBDIRS += Luna \
    LightPlugin \
    LunaCore \
    AudioPlugin \
    ScreenPlugin

LightPlugin.depends = LunaCore
AudioPlugin.depends = LunaCore
ScreenPlugin.depends = LunaCore
Luna.depends = LunaCore LightPlugin ScreenPlugin
