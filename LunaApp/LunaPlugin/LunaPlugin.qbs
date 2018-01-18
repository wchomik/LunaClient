import qbs

DynamicLibrary {
    name: "LunaPlugin"

    Depends { name: "LunaCore" }
    Depends { name: "cpp" }

    Export {
        Depends { name: "cpp" }
        Depends { name: "LunaCore" }
        cpp.includePaths: product.sourceDirectory + "/include"
    }

    cpp.defines: ['LUNAPLUGIN_LIBRARY=1']
    cpp.includePaths: "include/lunaplugin"

    files: [
        "source/lunaplugin.cpp",
        "source/luna.cpp",
        "source/tabsmodel.cpp",
        "source/connectorplugin.cpp",
        "source/configurableplugin.cpp",
        "source/effectplugin.cpp",

        "include/lunaplugin/lunaplugin.h",
        "include/lunaplugin/lunaplugin_global.h",
        "include/lunaplugin/luna.h",
        "include/lunaplugin/tabsmodel.h",
        "include/lunaplugin/connectorplugin.h",
        "include/lunaplugin/configurableplugin.h",
        "include/lunaplugin/effectplugin.h"
    ]

    Group {
        fileTagsFilter: product.type
        qbs.install: true
        qbs.installDir: project.binDir
    }
}
