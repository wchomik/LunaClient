import qbs

StaticLibrary {
    id: root
    default property string repoPath: "../DTLS-server/tls/"

    Depends { name: "cpp" }
    Depends { name: "mbedtls" }
    cpp.cxxLanguageVersion: "c++14"

    Group {
        name: "sources"
        prefix: root.repoPath + "source/"
        files: [
            "client.cpp",
            "exception.cpp",
            "server.cpp",
            "session.cpp",
            "session_listener.cpp",
        ]
    }

    cpp.includePaths:root.repoPath + "include/tls/"

    Export {
        Depends { name: "cpp" }
        Depends { name: "mbedtls" }
        cpp.cxxLanguageVersion: "c++14"
        cpp.includePaths: root.repoPath + "include/"
    }

    Group {
        name: "headers"
        prefix: root.repoPath + "include/tls/"
        files: [
            "basic_input_output.hpp",
            "certificate.hpp",
            "client.hpp",
            "configuration.hpp",
            "cookie.hpp",
            "counter_deterministic_random_generator.hpp",
            "entropy.hpp",
            "exception.hpp",
            "private_key.hpp",
            "random_generator.hpp",
            "server.hpp",
            "session.hpp",
            "session_listener.hpp",
            "socket_input_output.hpp",
            "ssl.hpp",
            "standard_cookie.hpp",
            "standard_entropy.hpp",
            "standard_timer.hpp",
            "timer.hpp",
        ]
    }
}
