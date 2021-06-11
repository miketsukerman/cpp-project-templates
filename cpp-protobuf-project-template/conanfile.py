from conans import ConanFile, CMake
import os 
class HelloConan(ConanFile):
    name = "sample"
    version = "0.0.1"
    settings = "os", "compiler", "arch"
    options = {"shared": [True, False]}
    default_options = "shared=True"
    generators = "cmake", "cmake_find_package", "virtualrunenv"
    exports_sources = "include/*"
    
    requires = "catch2/2.13.6", "spdlog/1.8.5", "protobuf/3.15.5"

    def build(self):
        protoc = os.path.join(self.deps_cpp_info['protobuf'].rootpath,'bin','protoc')

        for bt in ("Debug", "Release"):
            cmake = CMake(self, build_type=bt)
            cmake.definitions['PROTOC_GENERATOR'] = protoc
            cmake.configure()
            cmake.build()
