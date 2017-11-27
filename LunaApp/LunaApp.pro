TEMPLATE = subdirs

SUBDIRS += Luna \
    LightPlugin \
    LunaCore \
    AudioPlugin

LightPlugin.depends = LunaCore
AudioPlugin.depends = LunaCore
Luna.depends = LunaCore LightPlugin
