import qbs

Application {
    name: "Luna"

    Depends { name: "LunaPlugin" }
    consoleApplication: false

    files: [
        "main.cpp",
        "qml.qrc"
    ]

    Group {
        fileTagsFilter: product.type
        qbs.install: true
        qbs.installDir: project.binDir
    }
}
