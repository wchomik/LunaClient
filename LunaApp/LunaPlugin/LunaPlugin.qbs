import qbs

DynamicLibrary {
    name: "LunaPlugin"

    Depends { name: "LunaCore" }
    Depends { name: "cpp" }

    Export {
        Depends { name: "cpp" }
        Depends { name: "LunaCore" }
        cpp.includePaths: product.sourceDirectory
    }

    cpp.defines: ['LUNAPLUGIN_LIBRARY=1']

    files: [
        "lunaplugin.cpp",
        "luna.cpp",
        "tabsmodel.cpp",
        "connectorplugin.cpp",
        "configurableplugin.cpp",
        "effectplugin.cpp",

        "lunaplugin.h",
        "lunaplugin_global.h",
        "luna.h",
        "tabsmodel.h",
        "connectorplugin.h",
        "configurableplugin.h",
        "effectplugin.h"
    ]

    Group {
        fileTagsFilter: product.type
        qbs.install: true
        qbs.installDir: project.binDir
    }
}
