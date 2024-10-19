# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Fixed

- get_input decrement bug.

## [1.3.0] - 2024.09.26

### Added

- "Person" struct type to store information internally.
- Header file for custom types.

### Changed

- Optimized user input reading function.
- Refactoring.

## [1.2.0] - 2024.06.13

### Added

- "Check if birthday entry exist." functionality.
- "List birthdays for current month" functionality.
- Notification if entry does not exist.
- Date format validation.
- Makefile.

### Changed

- Complete refactor, switched to multi file code.
- "Scanf" calls eliminated.
- Better prompts.

### Fixed

- Input buffer bug fixed.
- Other minor fixes.

## [1.1.0] - 2024.06.03

### Added

- Global loop boolean added for minor structure improvement.
- More error handling.

### Changed

- Existence of DB file/"birthdays" table only checked once at start.
- Better input validation.
- String array and memory size adjustments.
- Minor changes in printed messages.
- Some variable names shortened.
- Comment improvements.

## [1.0.0] - 2024.06.02

### Added

- Initial release.

[Unreleased]: https://github.com/OperaVaria/cdb-birthday/compare/1.3.0...HEAD
[1.3.0]: https://github.com/OperaVaria/cdb-birthday/compare/1.2.0...1.3.0
[1.2.0]: https://github.com/OperaVaria/cdb-birthday/compare/1.1.0...1.2.0
[1.1.0]: https://github.com/OperaVaria/cdb-birthday/compare/1.0.0...1.1.0
[1.0.0]: https://github.com/OperaVaria/cdb-birthday/releases/tag/1.0.0
