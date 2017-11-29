TEMPLATE = subdirs

SUBDIRS += \
    LunaCore \
    LightPlugin \
    AudioPlugin \
    ScreenPlugin \
    Luna \

LightPlugin.depends = LunaCore
AudioPlugin.depends = LunaCore
ScreenPlugin.depends = LunaCore
Luna.depends = LunaCore LightPlugin ScreenPlugin
