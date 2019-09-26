from conans import ConanFile

class LunaConanfile(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = [
        "fftw/3.3.8@bincrafters/stable",
        "eigen/3.3.4@conan/stable",
    ]
    generators = "cmake"
    default_options = {
        "fftw:precision" : "single",
        "fftw:shared" : True,
    }

    def imports(self):
        self.copy("*.dll", src="bin", dst="bin",)
        self.copy("*.so*", src="lib", dst="bin",)

    def requirements(self):
        if self.settings.os == "Linux":
            self.requires("libalsa/1.1.5@conan/stable")
