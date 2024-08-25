# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html) with the addition of a fourth
version number that represents the TEST_VERSION. Test version adheres to [Spec Item 10](https://semver.org/spec/v2.0.0-rc.2.html#spec-item-10)
of semantic versioning. So scheme is MAJOR.MINOR.PATCH+TEST_VERSION. Changes to the TEST_VERSION, however, 
will be tracked in the ./test/CHANGLOG.md and the TEST_VERSION will be included/incremented
when changes to the tests have been made without changes being made to the library itself.

### Types of changes

- Added:      for new features.
- Changed:    for changes in existing functionality.
- Deprecated: for soon-to-be removed features.
- Removed:    for now removed features.
- Fixed:      for any bug fixes.
- Security:   in case of vulnerabilities.

## [Unreleased]

- Turn this project into a conan package.
- Compile PNGIO sources into a libary.
  - static
  - shared
- CRC check for PNGReader
- PNG Writer
  - CRC generator for writes
- Class or struct for each PNG Chunk type
  - Enum for chunk types codes
- Tests, many tests.

## [0.3.0] - 2024-08-25

### Changed

- How we access data from PNGChunk. All elements used to be public as PNGChunk was a struct.
  Changed it to a class and added getters and setters. This will make testing and catching bugs easier
  since we can track the set functions and see where the variables are specifically gettings set.

### Removed

- The hard coded file path to the testImage.png file. I was incorrectly using the input filename, meaning
  I wasn't using it at all... oops.

## [0.2.0] - 2024-08-24

### Removed

- main.cpp. Code will now be executed by gtest code.

## [0.1.0] - 2024-08-24

### Added

- conanfile.py build function. This will let conan generate our cmake files as well
  as build our sources and executables with fewer commands. We can now build by doing
  conan install -of build . && conan build -of build .

### Changed

- README.md to reflect the new build instructions.

## [0.0.0] - 2024-08-24

### Added

- This file
- All source files.