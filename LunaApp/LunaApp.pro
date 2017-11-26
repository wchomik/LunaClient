TEMPLATE = subdirs

SUBDIRS += Luna \
    LightPlugin \
    LunaCore

Luna.depends = LunaCore
LightPlugin.depends = LunaCore
