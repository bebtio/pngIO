# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html) with the addition of a fourth
version number that represents the TEST_VERSION. 
TEST_VERSION adheres to [Spec Item 10](https://semver.org/spec/v2.0.0-rc.2.html#spec-item-10)
of semantic versioning. So scheme is MAJOR.MINOR.PATCH+TEST_VERSION. 

### Types of changes

- Added:      for new features.
- Changed:    for changes in existing functionality.
- Deprecated: for soon-to-be removed features.
- Removed:    for now removed features.
- Fixed:      for any bug fixes.
- Security:   in case of vulnerabilities.

## [Unreleased]

## [0.7.0] - 2024-09-08

### Added

- Tests for IHDRChunk read and write operations in the PNGIOTypeTests file.

## [0.5.0] - 2024-09-01

### Added

- Tests to check whether the CRC generation code is working.
  - GoodCRCTest
  - BadCRCTest

## [0.4.0] - 2024-08-29

### Added

- Various tests:
  - ReadChunkFailTest
  - ReadInvalidSignatureTest
  - ReadChunkBadFormatTest
  - WriteChunksToFileTest
  - WritePNGToFileTest

### Changed

- All the test are now just PNGTests.
- Renamed the PNGChunkTest.cpp file to PNGTest.
- All tests to TEST_F's and added PNGChunkTest.hpp to initialize shared file paths.

## [0.3.0] - 2024-08-25

### Added 

- PNGChunkTest file which contains tests for:
  - Reading in the correct header.
  - Reading in the correct number of chunks.
  - Reading in the correct data from the png file.

### Removed

- Old HelloWorldTest file.

## [0.2.0] - 2024-08-24

### Added

- Initial PNGIO Test.
