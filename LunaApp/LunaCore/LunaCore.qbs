import qbs

DynamicLibrary {
    name: "LunaCore"

    Depends { name: "cpp" }
    Depends { name: "Qt.core" }
    Depends { name: "Qt.quick" }
    Depends { name: "Qt.gui" }
    Depends { name: "Eigen3" }

    Export {
        Depends { name: "cpp" }
        Depends { name: "Qt.core" }
        Depends { name: "Qt.quick" }
        Depends { name: "Qt.gui" }
        Depends { name: "Eigen3" }
        cpp.cxxLanguageVersion: "c++14"
        cpp.includePaths: product.sourceDirectory


        Properties {
            condition: qbs.targetOS.contains("windows")
            cpp.defines: outer.concat(["_USE_MATH_DEFINES", "NOMINMAX", "WIN32_LEAN_AND_MEAN"])
        }
    }

    cpp.defines: ['LUNACORE_LIBRARY=1']
    cpp.cxxLanguageVersion: "c++14"

    files: [
        "colorprocessor.cpp",
        "colorspace.cpp",
        "colorutils.cpp",
        "connector.cpp",
        "manager.cpp",
        "provider.cpp",
        "strand.cpp",

        "lunacore_global.h",
        "colormode.h",
        "colorprocessor.h",
        "colorspace.h",
        "colorutils.h",
        "connector.h",
        "delegate.h",
        "event.h",
        "manager.h",
        "provider.h",
        "strand.h",
        "range.h"
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
