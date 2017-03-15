# react-native-kontaktio [![npm version](https://badge.fury.io/js/react-native-kontaktio.svg)](https://badge.fury.io/js/react-native-kontaktio)

React-native module for detecting [Kontakt.io](http://kontakt.io/) beacons.

Only works on **Android** for now. **iOS** version is in development and will be added soon.

Implements version **3.2.3.** of the [Kontakt.io SDK](http://kontaktio.github.io/kontakt-android-sdk/3.2.3/Javadoc/).

#### Why should I use this module and not a generic beacon package?

If you use this module with Kontakt.io beacons, you get additional information with each scan, like the unique id which is printed on the back of each beacon or the current battery level (`batteryPower`), which is also synchronized with your Kontakt.io online panel. Besides, beacons from other manufacturers can also be ranged nevertheless, just without that extra information.

## Run Example to test the module

1. Clone this repository, connect an Android device to your computer and have some beacons handy

2. Bash to the `Example/` folder, run `npm install` and start the react-native server

	```bash
	$ cd react-native-kontaktio/Example
	$ npm install
	$ npm start
	```
	
3. Build the example and run it on your android device. The app will appear under the name `KontaktIoSimpleTest`:

	```bash
	$ react-native run-android
	```

## Setup

Some [Kontakt.io beacons prerequisites](https://developer.kontakt.io/android-sdk/quickstart/#setup) have to be met.

### Android

#### Automatic setup

After the update the manual setup should should be easier when using `react-native link react-native-kontaktio`. However this was not tested yet. Will be tested soon and this section updated. For now, please refer to the manual setup.

#### Manual setup

1. npm install

	```bash
	$ npm install --save react-native-kontaktio
	```

2. In `android/app/src/main/java/.../MainApplication.java` import `KontaktPackage` and add it to the List:

	```java
	import com.artirigo.kontaktio.KontaktPackage;
	...
	return Arrays.<ReactPackage>asList(
		new MainReactPackage(),
		...
		new KontaktPackage()
       );
	```

3. In `android/settings.gradle` add:

	```
	include ':react-native-kontaktio'
	project(':react-native-kontaktio').projectDir = new File(rootProject.projectDir, '../node_modules/react-native-kontaktio/android')
	```

4. In `android/app/src/main/AndroidManifest.xml` inside `<application />` add 

	```xml
	<service android:name="com.kontakt.sdk.android.ble.service.ProximityService" android:exported="false"/>
	```

5. In `android/app/build.gradle` 

	* Add dependency

	```java
	dependencies {
		compile project(':react-native-kontaktio')
		...
	}
	```

	* Add exclusion inside `android`, i.e.

	```java
	android {
		...
		packagingOptions {
			exclude 'main/AndroidManifest.xml'
		}
	}
	```

4. The following step is inside the [Kontakt.io docs](http://developer.kontakt.io/android-sdk/2.1.0/quickstart/) but was not necessary on the devices I tested: In `android/build.gradle` add maven link:
	
	```java
	allprojects {
	    repositories {
	    	...
	    	maven {
	    		// All of React Native (JS, Obj-C sources, Android binaries) is installed from npm
	    		url "$rootDir/../node_modules/react-native/android"
        	}
	       maven { url "http://repo.kontakt.io/repository/internal/" }   // <-- Add this line
	    }
	}
	
	```

## Minimal Example

This is a minimal example with the default configuration and no specifically set regions. Thus, the default region `everywhere` (i.e. all beacons) is used.

Please take a look at *Example/src/Example.js* for an bigger usage example including configuration settings and multiple regions.

*Example/src/MinimalExample.js*

```js
import React, { Component } from 'react';
import { View, DeviceEventEmitter } from 'react-native';

import { init, startScanning } from 'react-native-kontaktio';

/**
 * Minimal example of react-native-kontaktio
 */
export default class MinimalExample extends Component {
  componentDidMount() {
    init()
      .then(() => startScanning())
      .catch(error => alert('error', error));

    // Add beacon listeners
    DeviceEventEmitter.addListener(
      'beaconsDidUpdate',
      ({ beacons, region }) => {
        console.log('beaconsDidUpdate', beacons, region);
      }
    );
  }

  render() {
    return <View />;
  }
}
```


## API Documentation

### Main objects: `beacon` and `region`

The following two objects are the main players of this module and will be referred to multiple times throughout this documentation:

##### `beacon`

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

##### `region`

```js
.region
	.identifier
	.uuid
	.secureUuid
	.major
	.minor
```

### Events

#### Event flow

In case regions are defined, events will commonly occur in this order if 1) a beacon signal is detected, 2) the signal changes and 3) the signal is lost:

1. detected
	* regionDidEnter
	* beaconDidAppear

2. changed
	* beaconsDidRange
		* Sent whenever a change in proximity is detected.
		* This event is sent separately for each currently scanned region if at least one of its beacons has changed.

3. lost
	* beaconDidDisappear
	* regionDidExit


#### Event overview

| Event                      | Description                       |
|:---------------------------|:----------------------------------|
| **beaconDidAppear**        | Sends `{ beacon, region }` if a beacon appears for the first time. `region` is one of the regions defined with `setBeaconRegion` or `setBeaconRegions` or the region *everywhere* if no region was defined. `beacon` and `region` have the form as defined above. |
| **beaconDidDisappear**     | Sends `{ beacon, region }` if a beacon which was previously scanned is out of the range of the device. `region` is one of the regions defined with `setBeaconRegion` or `setBeaconRegions` or the region *everywhere* if no region was defined. `beacon` and `region` have the form as defined above. |
| **beaconsDidUpdate**       | Sends `{ beacons, region }` if some property of beacons in that `region` changed. `beacons` is an array of beacons (with its `length` >= `1`) which changed in that `region`. Each `beacon` in that array has the form as described above. |
| **regionDidEnter**         | Sends `{ region }`, the beacon region which was just entered (i.e. at least one beacon of that region was detected). `region` has the form as described above |
| **regionDidExit**          | Sends `{ region }`, the beacon region which was just lost (i.e. the last remaining beacon of that region was not anymore in range and the time for keeping the beacon in the internal cache ran out as set with `activeCheckConfiguration`, i.e. never removed from cache with `DISABLED`, `3` seconds with `MINIMAL` and `10` seconds with `DEFAULT`). `region` has the form as described above |
| **scanStatus**             | Sends `{ status }` where `status` is either `START`, `STOP` or `ERROR` depending on whether the scan for beacons started, stopped or a sudden error occurred while scanning |
| **monitoringCycle**        | Sends `{ status }` where `status` is either `START` `STOP` depending on whether a scan cycle just started or stopped. The active period of a monitoring scan cycle is 8 seconds, the inactive (passive) period is 30 seconds long. Attention: Only sends events if `scanMode` is set to `MONITORING` |

### Methods

#### Some infos

* All methods may be imported globally (i.e. `import Kontakt from 'react-native-kontaktio`) or one-by-one (i.e. `import { init, startScanning } from 'react-native-kontaktio`).
* All methods return a **Promise** which returns an error statement in case something went wrong. Care was taken to include useful error messages.
* The best way to explore the usage of these methods is to take a look at the example in [Example/src/Example.js](/Example/src/Example.js).

#### Method overview

| Method                                          | Description                     |
|:------------------------------------------------|:--------------------------------|
| **init('KontaktAPIKey', [IBEACON, EDDYSTONE])** | (*mandatory*) Initialize scanning for beacons. The first argument is your `Kontakt.io` API-Key as a string. It's not needed for regular beacon scanning, but if you e.g. want the battery level of a beacon to be sent to your Konakt.io web panel in regular intervals (every 10 seconds). The second argument is an array of the beacon types you want to scan for. Two options are possible, the provided constants `IBEACON` or `EDDYSTONE`. The default call `init()`  |
| **configure({ ... })**          | (*optional*) Configure scanning with the configuration options described below |
| **setBeaconRegion(region)**      | (*optional*) Only beacons which fall into the provided `region` will be scanned and returned with the events described above. |
| **setBeaconRegions([region1, region2, ... ])**     | (*optional*) Only beacons which fall into one of the provided regions in the array `regions` will be scanned and returned with the events described above. *Note*: In case you want to dynamically add or remove regions after scanning started you have call `restartScanning` right after `setBeaconRegions` for the change of regions to take effect. That is, first call `setBeaconRegions` with the changed array of regions (i.e. with the additional region you want to add or without the region you want to remove) and then call `restartScanning` right thereafter. |
| **startScanning**        | starts scanning of beacons with given configuration and provided regions |
| **stopScanning**         | stops scanning for all provided regions |
| **restartScanning**      | stops and starts scanning again. In case device was not scanning before, scanning is just started. |
| **disconnect**           | disconnect the Kontakt.io beacon scanner and set it to `null` |


### Configuration

A config object can be passed with the following options (see the [Kontakt.io quickstart guide](https://developer.kontakt.io/android-sdk/quickstart/#basic-usage-configuration) and [SDK docs](http://kontaktio.github.io/kontakt-android-sdk/3.2.1/Javadoc/) for more information about the possible configurations). Currently not all configurations are available here but will be in the near future:

| Configuration              | Description                       |
|:---------------------------|:----------------------------------|
| **scanMode**        | Possible values: `scanMode.LOW_POWER`, `scanMode.BALANCED` or `scanMode.LOW_LATENCY`. Tipp: `BALANCED` is the default value and mostly the best compromise between battery demand on the device and signal quality. Use `LOW_LATENCY` only when running the app in the foreground. |
| **scanPeriod**     | Possible values: `scanPeriod.RANGING` or `scanPeriod.MONITORING`. `RANGING` scans beacons all the time, `MONITORING` operates in scan-cycles; it scans for **8** seconds, then pauses scanning for **30** seconds, then scans for **8** seconds again and so forth. |
| **activeCheckConfiguration**       | Possible values: `activeCheckConfiguration.DISABLED`, `activeCheckConfiguration.MINIMAL` or `activeCheckConfiguration.DEFAULT`. It sets the time it takes the device to "forget" a formerly scanned beacon when it can't detect it anymore. Once successfully scanned beacons remain in the internal cache and are never removed from the cache (`DISABLED`), removed after not scanning them for `3` seconds (`MINIMAL`) or after `10` seconds (`DEFAULT`). These are the official numbers used in the Kontakt.io SDK documentation. However I found that in each configuration it takes a bit longer than that until the beacons are really removed from the cache. |

### Constants

Some constants are provided which may be used while creating a `region`. These are the default values if the corresponding fields are not provided, but may be used for a more declarative api call.

The other two constants are the two different beacon types.

| Constant                                    | Where to use?                |
|:--------------------------------------------|:-----------------------------|
| **DEFAULT_KONTAKT_BEACON_PROXIMITY_UUID**   | uuid (region)                |
| **BEACON_REGION_ANY_MAJOR**                 | major (region)               |
| **BEACON_REGION_ANY_MINOR**                 | minor (region)               |
| **DEFAULT_KONTAKT_NAMESPACE_ID**            | namespace (region)           |
| **IBEACON**                                 | init (second argument)       |
| **EDDYSTONE**                               | init  (second argument)      |

## Further notes

* Beacons support Android versions 4.3 and up.
	* So far the lowest Android version this library was tested on was a device with Android 4.4.2.
* A physical device must be used for testing, at best you have some Kontakt.io beacons at your disposal, configure them via their management console and have your API-key handy.

## Coming soon:

* iOS version
* Eddystone support (Currently `EDDYSTONE` beacons can be scanned, but the corresponding functions are not yet exposed to the JS side because it wasn't fully tested yet)