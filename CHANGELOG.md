# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

### Types of changes

- Added:      for new features.
- Changed:    for changes in existing functionality.
- Deprecated: for soon-to-be removed features.
- Removed:    for now removed features.
- Fixed:      for any bug fixes.
- Security:   in case of vulnerabilities.

## [Unreleased]

- Upgrade to a conanfile.py so we can group the gross build commands in the README.md to a function.
- CRC check for PNGReader
- PNG Writer
  - CRC generator for writes
- Class or struct for each PNG Chunk type
  - Enum for chunk types codes
- Tests, many tests.

## [0.0.0] - 2024-08-24

### Added

- This file
- All source files.