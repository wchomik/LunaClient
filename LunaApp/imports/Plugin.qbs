import qbs

DynamicLibrary {
    Depends { name: "LunaPlugin" }

    Group {
        fileTagsFilter: product.type
        qbs.install: true
        qbs.installDir: project.pluginsDir
    }
}
