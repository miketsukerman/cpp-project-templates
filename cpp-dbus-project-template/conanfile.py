from conans import ConanFile, CMake

class HelloConan(ConanFile):
    name = "sample"
    version = "0.0.1"
    settings = "os", "compiler", "arch"
    options = {"shared": [True, False]}
    default_options = "shared=True"
    generators = "cmake", "cmake_find_package"
    exports_sources = "include/*"
    
    requires = "catch2/2.13.6", "spdlog/1.8.5", "dbus/1.12.20"

    def build(self):
        for bt in ("Debug", "Release"):
            cmake = CMake(self, build_type=bt)
            cmake.configure()
            cmake.build()
