TEMPLATE = subdirs

SUBDIRS += \
    LunaCore \
    LunaPlugin \
    LightPlugin \
    AudioPlugin \
    ScreenPlugin \
    Luna \
    ConnectorPlugin

LunaPlugin.depends = LunaCore

LightPlugin.depends = LunaPlugin
AudioPlugin.depends = LunaPlugin
ScreenPlugin.depends = LunaPlugin

Luna.depends = LunaCore LightPlugin ScreenPlugin
