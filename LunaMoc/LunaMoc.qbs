import qbs


Project {
    name: "LunaMoc"
    Application {
        Depends { name: "cpp" }
        cpp.cxxLanguageVersion: "c++14"
        Depends { name: "Qt.core" }
        Depends { name: "Qt.quick" }
        Depends { name: "Qt.gui" }
        Depends { name: "Qt.network" }

        files: [
            "main.cpp",
            "dataobject.cpp",
            "pixelprovider.cpp",
            "udpserver.cpp",
            "dataobject.h",
            "pixelprovider.h",
            "udpserver.h",
            "qml.qrc",
        ]
    }
}