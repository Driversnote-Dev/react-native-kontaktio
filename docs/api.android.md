# Android

## API Documentation

#### Main objects: `beacon` and `region`

The following two objects are the main players of this module and will be referred to multiple times throughout this documentation:

##### `beacon` / `eddystone`

```js
{
	// each beacon contains:
	name: string
	address: string
	rssi: number
	proximity: string (either IMMEDIATE, NEAR, FAR or UNKNOWN)
	// if Kontakt.io beacon this is useful, otherwise mostly -1 or similar
	accuracy: string (distance in meters)
	batteryPower: number (percentage as int)
	txPower: number
	firmwareVersion: string
	uniqueId: string
	isShuffled: string
	// if its of type IBEACON additionally:
	uuid: string
	major: number
	minor: number
	// if its of type EDDYSTONE additionally:
	namespace: string
	instanceId: string
	url: string
	eid: string
	encryptedTelemetry: string,
	telemetry: {
		batteryVoltage: number
		temperature: number,
		pduCount: number
		timeSincePowerUp: number,
		version: number,
	}
}
```

##### `region` (iBeacons)

```js
{
  identifier
  uuid
  secureUuid
  major
  minor
}
```

##### `namespace` (Eddystone)

```js
{
  identifier
  instanceId
  namespace
  secureNamespace
}
```

#### Events

##### Event flow

In case regions are defined, events will commonly occur in this order if 1) a beacon signal is detected, 2) the signal changes and 3) the signal is lost:

1.  detected

    - regionDidEnter / namespaceDidEnter
    - beaconDidAppear / eddystoneDidAppear

2.  changed

    - beaconsDidUpdate / eddystonesDidUpdate
      _ Sent whenever a change in proximity is detected.
      _ This event is sent separately for each currently scanned region if at least one of its beacons has changed.

3.  lost
    - beaconDidDisappear / eddystoneDidDisappear
    - regionDidExit / namespaceDidExit

##### Event overview

| Event                     | Beacon Type | Description                                                                                                                                                                                                                                                                                                                                                                                      |
| :------------------------ | :---------- | :----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **beaconDidAppear**       | iBeacon     | Sends `{ beacon, region }` if a beacon appears for the first time. `region` is one of the regions defined with `setBeaconRegion` or `setBeaconRegions` or the region _everywhere_ if no region was defined. `beacon` and `region` have the form as defined above.                                                                                                                                |
| **beaconDidDisappear**    | iBeacon     | Sends `{ beacon, region }` if a beacon which was previously scanned is out of the range of the device. `region` is one of the regions defined with `setBeaconRegion` or `setBeaconRegions` or the region _everywhere_ if no region was defined. `beacon` and `region` have the form as defined above.                                                                                            |
| **beaconsDidUpdate**      | iBeacon     | Sends `{ beacons, region }` if some property of beacons in that `region` changed. `beacons` is an array of beacons (with its `length` >= `1`) which changed in that `region`. Each `beacon` in that array has the form as described above. Sends multiple events if changes occur for beacons of different regions, one event for each region.                                                   |
| **regionDidEnter**        | iBeacon     | Sends `{ region }`, the beacon region which was just entered (i.e. at least one beacon of that region was detected). `region` has the form as described above                                                                                                                                                                                                                                    |
| **regionDidExit**         | iBeacon     | Sends `{ region }`, the beacon region which was just lost (i.e. the last remaining beacon of that region was not anymore in range and the time for keeping the beacon in the internal cache ran out as set with `activeCheckConfiguration`, i.e. never removed from cache with `DISABLED`, `3` seconds with `MINIMAL` and `10` seconds with `DEFAULT`). `region` has the form as described above |
| **eddystoneDidAppear**    | Eddystone   | Sends `{ eddystone, namespace }`                                                                                                                                                                                                                                                                                                                                                                 |
| **eddystoneDidDisappear** | Eddystone   | Sends `{ eddystone, namespace }`                                                                                                                                                                                                                                                                                                                                                                 |
| **eddystonesDidUpdate**   | Eddystone   | Sends `{ eddystones, namespace }`                                                                                                                                                                                                                                                                                                                                                                |
| **namespaceDidEnter**     | Eddystone   | Sends `{ namespace }`                                                                                                                                                                                                                                                                                                                                                                            |
| **namespaceDidExit**      | Eddystone   | Sends `{ namespace }`                                                                                                                                                                                                                                                                                                                                                                            |
| **scanStatus**            | General     | Sends `{ status }` where `status` is either `START`, `STOP` or `ERROR` depending on whether the scan for beacons started, stopped or a sudden error occurred while scanning                                                                                                                                                                                                                      |
| **monitoringCycle**       | General     | Sends `{ status }` where `status` is either `START` `STOP` depending on whether a scan cycle just started or stopped. The active period of a monitoring scan cycle is 8 seconds, the inactive (passive) period is 30 seconds long. Attention: Only sends events if `scanMode` is set to `MONITORING`                                                                                             |
| **beaconInitStatus**       | General     | Sends the object `{ isReady }` when the beacon service is ready to scan for beacons, in fact, when the `connect()` call was successful. This way it serves as an alternative to evaluating the Promise returned by `connect()`.                                                                                               |

#### Methods

##### General information

- All are part of the global import (i.e. `import Kontakt from 'react-native-kontaktio`)
- All methods return a **Promise** which returns an error statement in case something went wrong. If available the native error messages of the SDK are returned. Care was taken to include useful error messages.
- The best way to explore the usage of these methods is to take a look at the example in [Example/src/Example.android.js](/Example/src/Example.android.js).

##### Method overview

| Method                                             | Description                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    |
| :------------------------------------------------- | :----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **connect('KontaktAPIKey', [IBEACON, EDDYSTONE, SECURE_PROFILE])** | (_mandatory_) Initialize scanning for beacons. The first argument is your `Kontakt.io` API-Key as a string. It's not needed for regular beacon scanning, but if you e.g. want the battery level of a beacon to be sent to your Konakt.io web panel in regular intervals (every 10 seconds). The second argument is an array of the beacon types you want to scan for. Three options are possible, the provided constants `IBEACON`, `EDDYSTONE` or `SECURE_PROFILE`. Just calling `connect()` only ranges for `IBEACON`s by default. If you add `SECURE_PROFILE`, make sure it is the last element in the array. Scanning for `SECURE_PROFILE` [only works with Beacon Pros](https://support.kontakt.io/hc/en-gb/articles/206543744-Kontakt-io-Secure-Profile-packet-structure) for now |
| **configure({ ... })**                             | (_optional_) Configure scanning with the configuration options described below                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 |
| **setBeaconRegion(region)**                        | (_optional_) Only beacons which fall into the provided `region` will be scanned and returned with the events described above.                                                                                                                                                                                                                                                                                                                                                                                                                                                  |
| **setBeaconRegions([region1, region2, ... ])**     | (_optional_) Only beacons which fall into one of the provided regions in the array `regions` will be scanned and returned with the events described above. _Note_: In case you want to dynamically add or remove regions after scanning started you have call `restartScanning` right after `setBeaconRegions` for the change of regions to take effect. That is, first call `setBeaconRegions` with the changed array of regions (i.e. with the additional region you want to add or without the region you want to remove) and then call `restartScanning` right thereafter. |
| **getBeaconRegions**                               | Returns an array of currently set iBeacon regions if the promise resolves.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     |
| **setEddystoneNamespace(namespace)**               | (_optional_) Only eddystone beacons which match the provided `namespace` will be scanned and returned with the events described above.                                                                                                                                                                                                                                                                                                                                                                                                                                         |
| **startScanning**                                  | starts scanning of beacons with given configuration and provided regions. At the first call it connects the set regions and configurations which is a prerequisite for scanning                                                                                                                                                                                                                                                                                                                                                                                                |
| **stopScanning**                                   | stops scanning for all provided regions                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        |
| **restartScanning**                                | stops and starts scanning again. In case device was not scanning before, scanning is just started.                                                                                                                                                                                                                                                                                                                                                                                                                                                                             |
| **isScanning**                                     | fulfills the Promise with _true_ if scanning is currently in progress.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         |
| **disconnect**                                     | disconnects the Kontakt.io beacon scanner (can be thought of the oppostive of `connect`) and sets it to `null`                                                                                                                                                                                                                                                                                                                                                                                                                                                                 |
| **isConnected**                                    | fulfills the Promise with _true_ if device is ready to scan (i.e. after `connect` is called).                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  |

#### Configuration

A config object can be passed with the following options (see the [Kontakt.io quickstart guide](https://developer.kontakt.io/android-sdk/quickstart/#basic-usage-configuration) and [SDK docs](http://kontaktio.github.io/kontakt-android-sdk/3.2.1/Javadoc/) for more information about the possible configurations):

| Configuration                  | Description                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           |
| :----------------------------- | :------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| **scanMode**                   | Possible values: `scanMode.LOW_POWER`, `scanMode.BALANCED` or `scanMode.LOW_LATENCY`. <br> Tipp: `BALANCED` is the default value and mostly the best trade-off between scan frequency (i.e. signal quality) and power consumption. Use `LOW_LATENCY` only when running the app in the foreground.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     |
| **scanPeriod**                 | Possible values: `scanPeriod.RANGING`, `scanPeriod.MONITORING` or `create({ activePeriod: Integer (time in ms), passivePeriod: Integer (time in ms) })`. <br> `RANGING` scans beacons all the time, `MONITORING` operates in scan-cycles; it scans for **8** seconds, then pauses scanning for **30** seconds, then scans for **8** seconds again and so forth.                                                                                                                                                                                                                                                                                                                                                                                                                       |
| **activityCheckConfiguration** | Possible values: `activityCheckConfiguration.DISABLED`, `activityCheckConfiguration.MINIMAL`, `activityCheckConfiguration.DEFAULT` or `create({ inactivityTimeout: Integer (time in ms), checkPeriod: Integer (time in ms) })`. <br> It sets the time the device should wait until it "forgets" a formerly scanned beacon when it can't detect it anymore (`inactivityTimeout`) and the time period it searches for inactive beacons (`checkPeriod`). I didn't play around with the latter value a lot. <br> The `inactivityTimeout` has the following logic: Once a beacon was successfully scanned it remains in the internal cache and is never removed from there (`DISABLED`), removed after not being detected for `3` seconds (`MINIMAL`) or not for `10` seconds (`DEFAULT`). |
| **forceScanConfiguration**     | Possible values: `forceScanConfiguration.DISABLED`, `forceScanConfiguration.MINIMAL` or `create({ forceScanActivePeriod: Integer (time in ms), forceScanPassivePeriod: Integer (time in ms) })`. <br> Used to circumvent some buggy behavior which may be found on a few Android devices.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             |
| **monitoringEnabled**          | Possible values: `monitoringEnabled.TRUE` or `monitoringEnabled.FALSE`. <br> Attention: This is not the same "monitoring" as the **scanPeriod** with the same name. This is to set whether some data (e.g. the battery power shell be sent to the Kontakt.io web panel.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               |
| **monitoringSyncInterval**     | Possible values: `monitoringSyncInterval.DEFAULT` (which is equal to `10` seconds or any other integer value. <br> Denotes the time interval in which data is sent to the Kontakt.io web panel (as described at point **monitoringEnabled**.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          |

**Attention**: When changing configurations after starting scanning, you have to call the method `restartScanning` for the new configurations to take effect.

##### Default values

When not calling `configure()`, the following default values are used:

```js
{
  scanMode: scanMode.BALANCED,
  scanPeriod: scanPeriod.RANGING, // activePeriod = 60000ms, passivePeriod = 0ms
  activeCheckConfiguration: activeCheckConfiguration.DEFAULT,
  forceScanConfiguration: forceScanConfiguration.MINIMAL, // forceScanActivePeriod = 1000ms, forceScanPassivePeriod = 500ms
  deviceUpdateCallbackInterval: deviceUpdateCallbackInterval.DEFAULT // 3000ms,
  monitoringEnabled: monitoringEnabled.TRUE,
  monitoringSyncInterval: monitoringSyncInterval.DEFAULT, // 10sec,
}
```

#### Constants

Some constants are provided which may be used while creating a `region`. These are the default values if the corresponding fields are not provided, but may be used for a more declarative api call.

The other two constants are the two different beacon types.

| Constant                                  | Where to use?          |
| :---------------------------------------- | :--------------------- |
| **DEFAULT_KONTAKT_BEACON_PROXIMITY_UUID** | uuid (region)          |
| **BEACON_REGION_ANY_MAJOR**               | major (region)         |
| **BEACON_REGION_ANY_MINOR**               | minor (region)         |
| **DEFAULT_KONTAKT_NAMESPACE_ID**          | namespace (region)     |
| **IBEACON**                               | init (second argument) |
| **EDDYSTONE**                             | init (second argument) |
| **SECURE_PROFILE**                        | init (second argument) |

## Further notes

- Beacons support is part of Android versions 4.3 and up. \* So far the lowest Android version this library was tested on was a device with Android 4.4.2.

## ToDo:

- Update Android Eddystone feature:
  - Add _multiple_ Eddystone namespaces, i.e. add function `setEddystoneNamespaces`
  - Add Eddystone Frames Selection configuration option
