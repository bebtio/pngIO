from conan import ConanFile
from conan.tools.cmake import CMake
from conan.tools.files import load

class PngIORecipe(ConanFile):

    name = "pngio"
    url = "https://github.com/bebtio/pngIO"

    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    options = {"shared": [True,False]}
    default_options = {"shared": False}

    # Grab the version number from the VERSION file.
    def set_version(self):
        self.version =  load(self,"VERSION").strip()

    # List of dependencies goes here.
    # One self.requires per dependency.
    def requirements(self):
        self.requires("gtest/1.15.0")

    # This will build and compile our sources and executables.
    def build(self):

        # Call cmake on our project.
        cmake = CMake(self)
        cmake.configure()

        # Build our sources and executables.
        cmake.build()

        # Run our tests on each build.
        self.run("./test/test")