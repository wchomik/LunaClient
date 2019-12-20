from conans import ConanFile, CMake

class LunaConanfile(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = [
        "fftw/3.3.8@bincrafters/stable",
        "eigen/3.3.4@conan/stable",
        "qt/5.14.0@bincrafters/stable",
    ]
    generators = "cmake"
    default_options = {
        "fftw:precision" : "single",
        "fftw:shared" : True,
        "qt:qtquickcontrols" : True,
        "qt:qtquickcontrols2" : True,
        "qt:qtdeclarative" : True,
        "qt:qtwinextras" : True,
        "qt:multiconfiguration" : True,
        "qt:qtimageformats" : True,
    }

    def imports(self):
        self.copy("*.dll", src="bin", dst="bin")

    def requirements(self):
        if self.settings.os == "Linux":
            self.requires("libalsa/1.1.5@conan/stable")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()