# iOS

SDK Versions: [1.4.3](http://kontaktio.github.io/kontakt-ios-sdk/Documentation/html/)

## API Documentation

#### Main objects: `beacon` and `region`

The following two objects are the main players of this module and will be referred to multiple times throughout this documentation:

##### `beacon`

- In contrast to the _Android_ version the `beacon` object has a different shape depending on whether 1) discovering or 2) ranging/monitoring is used.

1.  While ranging or monitoring

    ```js
    {
    	uuid: string
    	major: number
    	minor: number
    	rssi: number
    	proximity: string (either IMMEDIATE, NEAR, FAR or UNKNOWN)
    	// if Kontakt.io beacon this is useful, otherwise mostly -1 or similar
    	accuracy: string (distance in meters)
    }
    ```

2.  While discovering

    ```js
    {
    	name: string  // 'Kontakt' by default for Kontakt.io beacons
    	uniqueId: string
    	firmwareVersion: string
    	batteryLevel: number (percentage as int) // batteryPower for Android
    	batteryPowered: boolean
    	transmissionPower: number  // txPower for Android
    	hasConfigurationProfile: boolean
    	shuffled: boolean
    	locked: boolean
    	model: string
    	peripheral: string
    	rssi: number
    	updatedAt: number
    }
    ```

##### `region`

```js
{
  identifier
  uuid
  major
  minor
}
```

#### Events

- Ranging, monitoring and discovering are three different processes. In contrast to the _Android_ version they are separated into different events and methods. Pay attention to the type column.
- Discovery (i.e. `didDiscoverDevices`) can only detect Kontakt.io beacons. Ranging and monitoring also works with beacons of other manufacturers.

##### Event overview

| Event                                     | Type          | Description                                                                                                                                                                                                                       |
| :---------------------------------------- | :------------ | :-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **didDiscoverDevices**                    | Discovery     | Sends `{ beacons }` if Kontakt.io beacons are in range. `beacons` and `region` have the form as defined above.                                                                                                                    |
| **devicesManagerDidFailToStartDiscovery** | Discovery     | Sends `{ error }` if scanning can't be started.                                                                                                                                                                                   |
| **didRangeBeacons**                       | Ranging       | Sends `{ beacons, region }` with currently ranged beacons in the region. If the configuration `dropEmptyRanges` is set to `true`, the event is not send if the array of beacons is empty.                                         |
| **didStartMonitoringForRegion**           | Monitoring    | Sends `{ region }`, the beacon region for which monitoring started.                                                                                                                                                               |
| **monitoringDidFailForRegion**            | Monitoring    | Sends `{ region, error }`, the beacon region for which the error `error` occurred.                                                                                                                                                |
| **didEnterRegion**                        | Monitoring    | Sends `{ region }`, the beacon region which was just entered (i.e. at least one beacon of that region was detected).                                                                                                              |
| **didExitRegion**                         | Monitoring    | Sends `{ region }`, the beacon region which was just lost (i.e. the last remaining beacon of that region was not anymore in range and the time for keeping the beacon in the internal cache ran out as set with `invalidationAge` |
| **didChangeLocationAuthorizationStatus**  | Authorization | Sends `{ status }`, the current authorization status.                                                                                                                                                                             |

#### Methods

##### General information

- All methods are properties of the default import (i.e. `import Kontakt from 'react-native-kontaktio`).
- All methods return a **Promise** which returns an error statement in case something went wrong.
- The best way to explore the usage of these methods is to take a look at the example in [Example/src/Example.android.js](/Example/src/Example.android.js).

##### Method overview

| Method                             | Type          | Description                                                                                                                                                                                                                                                                                                                                             |
| :--------------------------------- | :------------ | :------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| **init('KontaktAPIKey')**          | General       | (_mandatory_) Add your `Kontakt.io` API-Key as a string. It's not needed for regular beacon ranging/monitoring/discovery, but for **connecting** to your beacons (i.e. when setting the configuration `connectNearbyBeacons` to true). In case you don't need beacon connections, just call it without an argument as `init()`                          |
| **configure({ ... })**             | General       | (_optional_) Configuration options for beacon ranging/monitoring/discovery. Possible configurations can be found in the section below.                                                                                                                                                                                                                  |
| **startDiscovery({ interval })**   | Discovery     | starts general discovery of beacons not constrained to any region. Optionally an object with the field `interval` with a time in _milliseconds_ may be passed with the method call. Discovery will be paused for the time of the interval. If beacons are discovered in the proximity of your device the **didDiscoverDevices** event will be triggered |
| **stopDiscovery**                  | Discovery     | stops discovery for all provided regions                                                                                                                                                                                                                                                                                                                |
| **restartDiscovery**               | Discovery     | stops and starts discovery again                                                                                                                                                                                                                                                                                                                        |
| **isDiscovering**                  | Discovery     | fulfills the Promise with _true_ if beacon discovery is currently in progress.                                                                                                                                                                                                                                                                          |
| **startRangingBeaconsInRegion**    | Ranging       | starts ranging in provided `region`. If beacons are ranged in the proximity of your device the **didRangeBeacons** event will be triggered                                                                                                                                                                                                              |
| **stopRangingBeaconsInRegion**     | Ranging       | stops ranging for the provided `region`                                                                                                                                                                                                                                                                                                                 |
| **stopRangingBeaconsInAllRegions** | Ranging       | stops ranging for all regions                                                                                                                                                                                                                                                                                                                           |
| **getRangedRegions**               | Ranging       | returns all currently ranged `regions`                                                                                                                                                                                                                                                                                                                  |
| **startMonitoringForRegion**       | Monitoring    | starts monitoring in provided `region`. If beacons of a monitored region appear in the proximity of your device the **didEnterRegion** event will be triggered ,if these beacons are out of proximity for more than **didExitRegion** event .                                                                                                           |
| **stopMonitoringForRegion**        | Monitoring    | stops monitoring for the provided region                                                                                                                                                                                                                                                                                                                |
| **stopMonitoringForAllRegions**    | Monitoring    | stops monitoring for all currently monitored regions                                                                                                                                                                                                                                                                                                    |
| **getMonitoredRegions**            | Monitoring    | Returns all currently monitored `regions`                                                                                                                                                                                                                                                                                                               |
| **getAuthorizationStatus**         | Authorization | returns the authorization `status` (`authorizedAlways` or `authorizedWhenInUse` or `denied` or `notDetermined` or `restricted`)                                                                                                                                                                                                                         |
| **requestAlwaysAuthorization**     | Authorization | prompt the user to give authorization for the app to always scan for beacons, even if app is not in foreground.                                                                                                                                                                                                                                         |
| **requestWhenInUseAuthorization**  | Authorization | prompt the user to give authorization for the app to scan for beacons, if app is in use.                                                                                                                                                                                                                                                                |

#### Configuration

A config object can be passed to the call of the `configure` method with the following fields:

| Configuration            | Description                                                                                                                                                                                                                                                                                                                                       |
| :----------------------- | :------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| **dropEmptyRanges**      | If `true`, `didDiscoverDevices` and `didRangeBeacons` events don't fire if the array of beacons is empty. Default is true                                                                                                                                                                                                                         |
| **invalidationAge**      | In milliseconds. It sets the time the device should wait until it "forgets" a formerly scanned beacon when it can't detect it anymore. The default is `10000` (i.e. 10 seconds).                                                                                                                                                                  |
| **connectNearbyBeacons** | Connect to all discovered beacons in vicinity to get iBeacon values like major, minor and uuid during beacon discovery. Default is false. THIS FEATURE IS NOT FUNCTIONAL. SO FAR ONLY NATIVE LOGS AND ERRORS ARE TRIGGERED. YOU CAN TEST IT FOR EXPERIMENTAL PURPOSES AND ADJUST THE IOS CODE IF YOU KNOW OBJECTIVE C. Pull requests are welcome! |

## ToDo:

- iOS: Eddystone support (PR #31 has to be reviewed)
