import qbs
import qbs.Environment

Module {
    Depends { name: "cpp" }
    cpp.includePaths: [ Environment.getEnv("FFTW3_DIR") ]
    cpp.libraryPaths: [ Environment.getEnv("FFTW3_DIR") ]

    cpp.staticLibraries: "libfftw3f-3"
    cpp.dynamicLibraries: "libfftw3f-3"
}
