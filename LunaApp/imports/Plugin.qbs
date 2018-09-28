import qbs

LoadableModule {
    Depends { name: "LunaPlugin" }

    Group {
        fileTagsFilter: product.type
        qbs.install: true
        qbs.installDir: project.pluginsDir
    }
}
