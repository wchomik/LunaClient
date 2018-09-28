import qbs

DynamicLibrary {
    name: "LunaCore"

    Depends { name: "cpp" }
    Depends { name: "Qt.core" }
    Depends { name: "Qt.quick" }
    Depends { name: "Qt.gui" }
    Depends { name: "Eigen3" }
    Depends { name: "cpufeatures" }


    Export {
        Depends { name: "cpp" }
        Depends { name: "Qt.core" }
        Depends { name: "Qt.quick" }
        Depends { name: "Qt.gui" }
        Depends { name: "Eigen3" }
        Depends { name: "cpufeatures" }
        cpp.cxxLanguageVersion: "c++14"
        cpp.includePaths: [product.sourceDirectory + "/include"]
        cpufeatures.x86_avx: true


        Properties {
            condition: qbs.targetOS.contains("windows")
            cpp.defines: outer.concat(["_USE_MATH_DEFINES", "NOMINMAX", "WIN32_LEAN_AND_MEAN"])
        }
    }

    cpp.defines: ['LUNACORE_LIBRARY=1']
    cpp.cxxLanguageVersion: "c++14"
    cpp.includePaths: ["include/lunacore"]
    cpufeatures.x86_avx: true

    files: [
        "source/colorprocessor.cpp",
        "source/colorspace.cpp",
        "source/colorutils.cpp",
        "source/connector.cpp",
        "source/manager.cpp",
        "source/provider.cpp",
        "source/strand.cpp",

        "include/lunacore/lunacore_global.h",
        "include/lunacore/colormode.h",
        "include/lunacore/colorprocessor.h",
        "include/lunacore/colorspace.h",
        "include/lunacore/colorutils.h",
        "include/lunacore/connector.h",
        "include/lunacore/delegate.h",
        "include/lunacore/event.h",
        "include/lunacore/manager.h",
        "include/lunacore/provider.h",
        "include/lunacore/strand.h",
        "include/lunacore/range.h"
    ]

    Group {
        fileTagsFilter: product.type
        qbs.install: true
        qbs.installDir: project.binDir
    }


    Properties {
        condition: qbs.targetOS.contains("windows")
        cpp.defines: outer.concat(["_USE_MATH_DEFINES", "NOMINMAX", "WIN32_LEAN_AND_MEAN"])
    }

}
