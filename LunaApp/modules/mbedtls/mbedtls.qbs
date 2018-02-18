import qbs
import qbs.Environment

Module {
    Depends { name: "cpp" }
    cpp.includePaths: [ Environment.getEnv("MBEDTLS_DIR") + "/include/" ]
    cpp.libraryPaths: [ Environment.getEnv("MBEDTLS_DIR") + "/lib/" ]

    cpp.staticLibraries: [
        "mbedcrypto",
        "mbedtls",
        "mbedx509"
    ]
}
