import qbs
import qbs.Environment

Module {
    Depends { name: "cpp" }
    cpp.includePaths: [ Environment.getEnv("EIGEN3_DIR") ]
}
