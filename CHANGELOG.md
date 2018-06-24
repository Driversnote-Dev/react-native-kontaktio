# Changelog

All notable changes to this project will be documented in this file. If a contribution does not have a mention next to it, [@Andruschenko](https://github.com/Andruschenko) did it.

_The format is based on [Keep a Changelog](http://keepachangelog.com/) and this project adheres to [Semantic Versioning](http://semver.org/)._

**TODO**: Add missing versions to CHANGELOG

## Unreleased

### Added
* Add CHANGELOG

### Fixed
* Handle illegal callback invocation exception

## [v2.0.4] - 2017-10-25

### Changed
* Compatibility with React Native 0.48 and up

## [v2.0.0] - 2017-06-08

### Added
* _iOS_ support: Discovery, ranging and monitoring possible
* _Android_: Basic Eddystone support
* _Android_: New method getBeaconRegions() to get all regions which are set to scan.


### Changed
* _Android_: Rename `init()` to `connect()` and improve functionality so that `disconnect()` is the opposite action.
* Updated example apps
* Improved documentation (start-up documentation tested for react-native versions below and after 0.40.0)

### Fixed
* Several bug fixes

[unreleased]: https://github.com/Artirigo/react-native-kontaktio/compare/v2.0.4...master
[v2.0.4]: https://github.com/Artirigo/react-native-kontaktio/compare/v2.0.3...v2.0.4
[v2.0.0]: https://github.com/Artirigo/react-native-kontaktio/compare/v1.2.0...v2.0.0