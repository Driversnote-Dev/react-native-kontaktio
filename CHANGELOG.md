# Changelog

All notable changes to this project will be documented in this file. If a contribution does not have a mention next to it, [@Andruschenko](https://github.com/Andruschenko) did it.

_The format is based on [Keep a Changelog](http://keepachangelog.com/) and this project adheres to [Semantic Versioning](http://semver.org/)._

## [unreleased]

## [v2.10.0] - 2021-11-26

### Changed

- _Android_: Migrate to androidx.
- _Android_: Downgrade the Kontakt.io SDK to version `5.0.14` since it is the last version to target Android SDK 30 and since versions >= `5.0.15` might trigger the new Android 12 bluetooth permission model.

## [v2.9.0] - 2021-11-13

### Changed

- _Android_: Change the Kontakt.io SDK source and update to version `5.0.15`

## [v2.8.0] - 2021-01-10

### Changed

- _Android_: Update Kontakt.io SDK to version `5.0.0`
- _iOS_: Update Kontakt.io SDK to version `3.0.4`

## [v2.7.2] - 2020-03-06

### Changed

- Updated setup docs to include instructions on auto-linking
- Added new minimal example to README which works with RN 0.61

## [v2.7.1] - 2020-02-22

### Added

- Support for RN >= 0.60 and autolinking (incl. pod install section), by @pkondrashkov (see #67)

### Changed

- Update of permission information, by @nylsoo (see #63)

## [v2.7.0] - 2019-09-17

### Added

- _iOS_: Update Kontakt.io SDK to version `1.5.1`

### Changed

- _iOS_: Eddystone support
- _iOS_: Other minor code fixes

## [v2.6.2] - 2019-06-07

### Changed

- Update `KontaktBeacons.podspec`

## [v2.6.1] - 2019-05-22

### Changed

- Added information about the event `didDetermineState` and the method `requestStateForRegion` to the docs.

## [v2.6.0] - 2019-05-09

### Changed

- _Android_: Don't set `proximityManager` to `null` in `disconnect` function.
- _Android_: Make calls to `isConnected` function safer.
- _Android_: Make calls to `isScanning` function safer.

## [v2.5.4] - 2019-02-18

### Changed

- _Android_: Improved behavior of the `isConnected` function to resolve with `false` if `connect` wasn't called before and only reject in case of other errors. With this fix, `isConnected` may be called anytime. So far calling it before `connect` was called lead to a Promise rejection which is counter-intuitive because you'd expect to call this function to check whether this is the case.

## [v2.5.0] - 2019-02-07

### Added

- _iOS_: New function `requestStateForRegion` and corresponding listener `didDetermineState`.

### Changed

- Improved iOS setup documentation: Added a troubleshooting case

## [v2.4.0] - 2018-12-19

### Added

- _Android_: Add event `beaconInitStatus` as an alternative to the returned Promise of the `connect()` call.

### Changed

- _Android_: Remove routine to prevent repeated promise resolve or reject calls for the same promise. After the second call to the library, this case would not resolve or reject anything which caused the Promise chain on the Javascript side to halt.
- _Android_: Move `isConnected()` implementation into BeaconProximityManager file

## [v2.3.0] - 2018-11-08

### Changed

- _Android_: Wrap every call of so-far not-error-handled methods into an if-else statement which checks whether its object which is created after the `connect()` call is defined to avoid null-pointer exceptions.

## [v2.2.0] - 2018-11-08

### Changed

- _Android_: Upgraded gradle build tools to Version 25

## [v2.1.0] - 2018-06-24

### Added

- _Android_: Add Secure Profile. It is used when scanning for Beacon Pros, by @jampueroc (see #36)
- _Android_: Add KontaktTelemetry (with Acceleration) to Secure Profile - only works with BeaconPros, by @Andruschenko (see #36)
- Add CHANGELOG

### Changed

- _Android_: Update to SDK version 4.0.1 (Important: Version 4.0.0. removes support for Kontakt.io nRF51-based devices (Beacon, Tough Beacon, USB Beacon) with firmware < 4.0)
- Fixed and updated parts of the documentation. Added images to the iOS setup guide.

### Fixed

- Handle illegal callback invocation exception, by @JonasWho (see #21)

## [v2.0.4] - 2017-10-25

### Changed

- Compatibility with React Native 0.48 and up, by @exKAZUu (see #19)

## [v2.0.0] - 2017-06-08

### Added

- _iOS_ support: Discovery, ranging and monitoring possible
- _Android_: Basic Eddystone support
- _Android_: New method getBeaconRegions() to get all regions which are set to scan.

### Changed

- _Android_: Rename `init()` to `connect()` and improve functionality so that `disconnect()` is the opposite action.
- Updated example apps
- Improved documentation (start-up documentation tested for react-native versions below and after 0.40.0)

### Fixed

- Several bug fixes


[unreleased]: https://github.com/Artirigo/react-native-kontaktio/compare/v2.9.0...master
[v2.9.0]: https://github.com/Artirigo/react-native-kontaktio/compare/v2.8.0...v2.9.0
[v2.8.0]: https://github.com/Artirigo/react-native-kontaktio/compare/v2.7.2...v2.8.0
[v2.7.2]: https://github.com/Artirigo/react-native-kontaktio/compare/v2.7.1...v2.7.2
[v2.7.1]: https://github.com/Artirigo/react-native-kontaktio/compare/v2.7.0...v2.7.1
[v2.7.0]: https://github.com/Artirigo/react-native-kontaktio/compare/v2.6.2...v2.7.0
[v2.6.2]: https://github.com/Artirigo/react-native-kontaktio/compare/v2.6.1...v2.6.2
[v2.6.1]: https://github.com/Artirigo/react-native-kontaktio/compare/v2.6.0...v2.6.1
[v2.6.0]: https://github.com/Artirigo/react-native-kontaktio/compare/v2.5.4...v2.6.0
[v2.5.4]: https://github.com/Artirigo/react-native-kontaktio/compare/v2.5.0...v2.5.4
[v2.5.0]: https://github.com/Artirigo/react-native-kontaktio/compare/v2.4.0...v2.5.0
[v2.4.0]: https://github.com/Artirigo/react-native-kontaktio/compare/v2.3.0...v2.4.0
[v2.3.0]: https://github.com/Artirigo/react-native-kontaktio/compare/v2.2.0...v2.3.0
[v2.2.0]: https://github.com/Artirigo/react-native-kontaktio/compare/v2.1.0...v2.2.0
[v2.1.0]: https://github.com/Artirigo/react-native-kontaktio/compare/v2.0.4...v2.1.0
[v2.0.4]: https://github.com/Artirigo/react-native-kontaktio/compare/v2.0.3...v2.0.4
[v2.0.0]: https://github.com/Artirigo/react-native-kontaktio/compare/v1.2.0...v2.0.0
