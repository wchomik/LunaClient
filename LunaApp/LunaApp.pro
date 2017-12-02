TEMPLATE = subdirs

SUBDIRS += \
    LunaCore \
    LunaPlugin \
    Luna

LunaPlugin.depends += LunaCore
Luna.depends += LunaPlugin

#LightPlugin
SUBDIRS += LightPlugin
LightPlugin.depends = LunaPlugin
Luna.depens += LightPlugin

#AudioPlugin
SUBDIRS += AudioPlugin
AudioPlugin.depends = LunaPlugin
Luna.depens += AudioPlugin

#ScreenPlugin
SUBDIRS += ScreenPlugin
ScreenPlugin.depends = LunaPlugin
Luna.depends += ScreenPlugin



