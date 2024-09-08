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

- Break apart each of the Chunk type implementations into their own file.
- Class or struct implementation for each PNG Chunk type
  - PLTE
  - IDAT
  - IEND
  - cHRM
  - gAMA
  - iCCP
  - sBIT
  - sRGB
  - bKGD
  - hIST
  - tRNS
  - pHYs
  - sPLT
  - tIME
  - iTXt
  - tEXt
- Tests, many tests.
- Add chunk ordering code to PNGFile following order rules here: [libpngchunks](http://www.libpng.org/pub/png/spec/1.2/PNG-Chunks.html)
  - This is meant to order the chunk vector.  
  
## [0.7.0] - 2024-09-08

### Added

- Added IHDRChunk implementation as well as read and write operations for it.
## [0.6.0] - 2024-09-02

### Added

- PNGChunk class declarations that represent each of the PNGTypes defined here: [libpngchunks](http://www.libpng.org/pub/png/spec/1.2/PNG-Chunks.html)

## [0.5.0] - 2024-09-01

### Added

- CRC genration code straight from: [libpng](http://www.libpng.org/pub/png/spec/1.2/PNG-CRCAppendix.html)
  - Wrapped it up in a class called PNGCrc.
- More error checking for cases where the CRC is invalid.

## [0.4.0] - 2024-08-29

### Added

- TypeCode enumerations for all chunk types.
- Tests for 
- writePNGSignature function.
- writePNGCHhunk function.
- PNGChunk::isValid function

### Changed

- readPNGSignature is now hasPNGSignature.
- readPNGChunk so that it now checks for a valid typeCode and will stop reading if it doesn't
  find a valid code. This is very important so we don't go off reading memory that isn't our own.

## [0.3.0] - 2024-08-25

### Changed

- How we access data from PNGChunk. All elements used to be public as PNGChunk was a struct.
  Changed it to a class and added getters and setters. This will make testing and catching bugs easier
  since we can track the set functions and see where the variables are specifically gettings set.
- Function name of readPNGHeader to readPNGSignature.
- Function name of PNGFile::readPNGFile to PNGFile::load.
- The PNGFile constructor, it now does nothing. I've moved the functionality to the load function.
- Many of the input std::string filename to const std::string &filename.

### Added

- New file PNGIOTypes that will contain definitions for things like the PNG file signature as well as enumerated type codes.

### Removed

- The hard coded file path to the testImage.png file. I was incorrectly using the input filename, meaning
  I wasn't using it at all... oops.

## [0.2.0] - 2024-08-24

### Changed

- Now uses conan to handle dependencies, build, and export as a package!!!!

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
