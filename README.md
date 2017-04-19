# react-native-kontaktio [![npm version](https://badge.fury.io/js/react-native-kontaktio.svg)](https://badge.fury.io/js/react-native-kontaktio)

Cross-platform React Native module for detecting beacons with **Android** and **iOS** devices.
Especially useful with [Kontakt.io](http://kontakt.io/) beacons but may be used with any other beacon.

SDK Versions:

| OS             | SDK Version           |
|:---------------|:----------------------|
| **Android**    | [3.2.3](http://kontaktio.github.io/kontakt-android-sdk/3.2.3/Javadoc/) |
| **iOS**        | [1.4.3](http://kontaktio.github.io/kontakt-ios-sdk/Documentation/html/) |

#### Why should I use this module over other beacon modules?

* With Kontakt.io beacons, you get additional information with each scan, like the **unique id** which is printed on the back of each beacon or the current **battery power level** (`batteryPower`), which is also synchronized with your Kontakt.io online panel.
* APIs offer a wide range of methods and configurations.
* Beacons from other manufacturers can also be ranged, just without that extra information of the Kontakt.io manufacturer. I am happy to add a list of tested compatible beacon manufacturers here. Pull requests are more than welcome!

## Run Example to test the module

1. Clone this repository, connect an Android and/or Apple device to your computer and have some (Kontakt.io) beacons handy

2. Open a terminal window, bash to the `Example/` folder, run `npm install` and start the react-native server

	```bash
	$ cd react-native-kontaktio/Example
	$ npm install
	$ npm start
	```
	
3. Build the example and run it on your device. The app will appear under the name `KontaktIoSimpleTest`:

	* Android:
	
		```bash
		$ react-native run-android
		```
	
	* iOS

		```bash
		$ react-native run-ios
		```

## Setup

Some [Kontakt.io beacons prerequisites](https://developer.kontakt.io/android-sdk/quickstart/#setup) have to be met.

### Android

#### Automatic setup

// UNDER CONSTRUCTION

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
	
### iOS

#### Mostly automatic setup

1. Link module (use `rnpm` for React Native versions older than `0.27`)

		react-native link react-native-kontaktio

2. Manually link kontakt.io SDK

	Select your build target in the **`Project navigator`**. Click **`General`** and then in the **`Embedded Binaries`** section, click the **`+`** button.
	
	- Click **`[Add Other...]`**.
	- Navigate to **`node_modules/react-native-kontaktio/ios`**.
	- Add **`KontaktSDK.framework`**.

	It should now appear in the **`Linked Frameworks and Libraries`** section right below.

3. Add Framework Search paths so that Xcode can find the added framework

    - Go to the **Build Settings** tab and search for **"framework search paths"**.
    - Add the following path (select **recursive [v]**):
    
    	```
    	$(PROJECT_DIR)/../node_modules/react-native-kontaktio/ios
    	```

4. Add run script

	- In the **`Build Phases`** tab, click the **`+`** button at the top and select **`New Run Script Phase`**. Enter the following code into the script text field:

	```
	bash "${BUILT_PRODUCTS_DIR}/${FRAMEWORKS_FOLDER_PATH}/KontaktSDK.framework/strip-frameworks.sh"
	```

5. Add permissions

	Go to the **Info** tab and add in the section **`Custom iOS Target Properties`** add the following the following item:
	
	| Key | Value | Description |
	|---|---|---|
	| NSLocationAlwaysUsageDescription | This app requires background tracking | The value here will be presented to the user when the plugin requests **Background Location** permission |

## Minimal Example

This is a minimal example with the default configuration and no specifically set regions. Thus, the default region `everywhere` (i.e. all beacons) is used.

Please take a look at [Example/src/Example.android.js](/Example/src/Example.android.js) and [Example/src/Example.ios.js](/Example/src/Example.ios.js) for extended usage examples for both platforms.

### Android

[Example/src/MinimalExample.android.js](/Example/src/MinimalExample.android.js):

```js
import React, { Component } from 'react';
import { View, DeviceEventEmitter } from 'react-native';

import { init, startScanning } from 'react-native-kontaktio';

export default class MinimalExample extends Component {
  componentDidMount() {
    init()
      .then(() => startScanning())
      .catch(error => console.log('error', error));

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

### iOS

[Example/src/MinimalExample.ios.js](/Example/src/MinimalExample.ios.js):

```js
import React, { Component } from 'react';
import { View, NativeEventEmitter } from 'react-native';

import Kontakt, { KontaktModule } from 'react-native-kontaktio';

const { init, startScanning } = Kontakt;

const kontaktEmitter = new NativeEventEmitter(KontaktModule);

/**
 * Minimal example of react-native-kontaktio
 */
export default class MinimalExample extends Component {
  componentDidMount() {
    init()
      .then(() => startScanning())
      .catch(error => alert('error', error));

    // Add beacon listener
    kontaktEmitter.addListener(
      'didDiscoverDevices',
      ({ beacons }) => {
        console.log('didDiscoverDevices', beacons);
      }
    );
  }

  render() {
    return <View />;
  }
}
```


## API Documentation

### **Android** API Documentation

#### Main objects: `beacon` and `region`

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
{
	identifier
	uuid
	secureUuid
	major
	minor
}
```

#### Events

##### Event flow

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


##### Event overview

| Event                      | Description                       |
|:---------------------------|:----------------------------------|
| **beaconDidAppear**        | Sends `{ beacon, region }` if a beacon appears for the first time. `region` is one of the regions defined with `setBeaconRegion` or `setBeaconRegions` or the region *everywhere* if no region was defined. `beacon` and `region` have the form as defined above. |
| **beaconDidDisappear**     | Sends `{ beacon, region }` if a beacon which was previously scanned is out of the range of the device. `region` is one of the regions defined with `setBeaconRegion` or `setBeaconRegions` or the region *everywhere* if no region was defined. `beacon` and `region` have the form as defined above. |
| **beaconsDidUpdate**       | Sends `{ beacons, region }` if some property of beacons in that `region` changed. `beacons` is an array of beacons (with its `length` >= `1`) which changed in that `region`. Each `beacon` in that array has the form as described above. |
| **regionDidEnter**         | Sends `{ region }`, the beacon region which was just entered (i.e. at least one beacon of that region was detected). `region` has the form as described above |
| **regionDidExit**          | Sends `{ region }`, the beacon region which was just lost (i.e. the last remaining beacon of that region was not anymore in range and the time for keeping the beacon in the internal cache ran out as set with `activeCheckConfiguration`, i.e. never removed from cache with `DISABLED`, `3` seconds with `MINIMAL` and `10` seconds with `DEFAULT`). `region` has the form as described above |
| **scanStatus**             | Sends `{ status }` where `status` is either `START`, `STOP` or `ERROR` depending on whether the scan for beacons started, stopped or a sudden error occurred while scanning |
| **monitoringCycle**        | Sends `{ status }` where `status` is either `START` `STOP` depending on whether a scan cycle just started or stopped. The active period of a monitoring scan cycle is 8 seconds, the inactive (passive) period is 30 seconds long. Attention: Only sends events if `scanMode` is set to `MONITORING` |

#### Methods

##### General information

* All are part of the global import (i.e. `import Kontakt from 'react-native-kontaktio`)
* All methods return a **Promise** which returns an error statement in case something went wrong. If available the native error messages of the SDK are returned. Care was taken to include useful error messages.
* The best way to explore the usage of these methods is to take a look at the example in [Example/src/Example.android.js](/Example/src/Example.android.js).

##### Method overview

| Method                                          | Description                     |
|:------------------------------------------------|:--------------------------------|
| **init('KontaktAPIKey', [IBEACON, EDDYSTONE])** | (*mandatory*) Initialize scanning for beacons. The first argument is your `Kontakt.io` API-Key as a string. It's not needed for regular beacon scanning, but if you e.g. want the battery level of a beacon to be sent to your Konakt.io web panel in regular intervals (every 10 seconds). The second argument is an array of the beacon types you want to scan for. Two options are possible, the provided constants `IBEACON` or `EDDYSTONE`. The default call `init()`  |
| **configure({ ... })**          | (*optional*) Configure scanning with the configuration options described below |
| **setBeaconRegion(region)**      | (*optional*) Only beacons which fall into the provided `region` will be scanned and returned with the events described above. |
| **setBeaconRegions([region1, region2, ... ])**     | (*optional*) Only beacons which fall into one of the provided regions in the array `regions` will be scanned and returned with the events described above. *Note*: In case you want to dynamically add or remove regions after scanning started you have call `restartScanning` right after `setBeaconRegions` for the change of regions to take effect. That is, first call `setBeaconRegions` with the changed array of regions (i.e. with the additional region you want to add or without the region you want to remove) and then call `restartScanning` right thereafter. |
| **startScanning**        | starts scanning of beacons with given configuration and provided regions. At the first call it connects the set regions and configurations which is a prerequisite for scanning |
| **stopScanning**         | stops scanning for all provided regions |
| **restartScanning**      | stops and starts scanning again. In case device was not scanning before, scanning is just started. |
| **isScanning**      | fulfills the Promise with *true* if scanning is currently in progress. |
| **disconnect**           | disconnect the Kontakt.io beacon scanner and set it to `null` |
| **isConnected**           | fulfills the Promise with *true* if device is ready to scan (i.e. if `startScanning` or `restartScanning` was called at least once. |


#### Configuration

A config object can be passed with the following options (see the [Kontakt.io quickstart guide](https://developer.kontakt.io/android-sdk/quickstart/#basic-usage-configuration) and [SDK docs](http://kontaktio.github.io/kontakt-android-sdk/3.2.1/Javadoc/) for more information about the possible configurations):

| Configuration              | Description                       |
|:---------------------------|:----------------------------------|
| **scanMode**        | Possible values: `scanMode.LOW_POWER`, `scanMode.BALANCED` or `scanMode.LOW_LATENCY`. <br> Tipp: `BALANCED` is the default value and mostly the best trade-off between scan frequency (i.e. signal quality) and power consumption. Use `LOW_LATENCY` only when running the app in the foreground. |
| **scanPeriod**     | Possible values: `scanPeriod.RANGING`, `scanPeriod.MONITORING` or `create({ activePeriod: Integer (time in ms), passivePeriod: Integer (time in ms) })`. <br> `RANGING` scans beacons all the time, `MONITORING` operates in scan-cycles; it scans for **8** seconds, then pauses scanning for **30** seconds, then scans for **8** seconds again and so forth. |
| **activityCheckConfiguration**       | Possible values: `activityCheckConfiguration.DISABLED`, `activityCheckConfiguration.MINIMAL`, `activityCheckConfiguration.DEFAULT` or `create({ inactivityTimeout: Integer (time in ms), checkPeriod: Integer (time in ms) })`. <br> It sets the time the device should wait until it "forgets" a formerly scanned beacon when it can't detect it anymore (`inactivityTimeout`) and the time period it searches for inactive beacons (`checkPeriod`). I didn't play around with the latter value a lot. <br> The `inactivityTimeout` has the following logic: Once a beacon was successfully scanned it remains in the internal cache and is never removed from there (`DISABLED`), removed after not being detected for `3` seconds (`MINIMAL`) or not for `10` seconds (`DEFAULT`). |
| **forceScanConfiguration**        | Possible values: `forceScanConfiguration.DISABLED`, `forceScanConfiguration.MINIMAL` or `create({ forceScanActivePeriod: Integer (time in ms), forceScanPassivePeriod: Integer (time in ms) })`. <br> Used to circumvent some buggy behavior which may be found on a few Android devices. |
| **monitoringEnabled**        | Possible values: `monitoringEnabled.TRUE` or `monitoringEnabled.FALSE`. <br> Attention: This is not the same "monitoring" as the **scanPeriod** with the same name. This is to set whether some data (e.g. the battery power shell be sent to the Kontakt.io web panel. |
| **monitoringSyncInterval**        | Possible values: `monitoringSyncInterval.DEFAULT` (which is equal to `10` seconds or any other integer value. <br> Denotes the time interval in which data is sent to the Kontakt.io web panel (as described at point **monitoringEnabled**. |

**Attention**: When changing configurations after starting scanning, you have to call the method `restartScanning` for the new configurations to take effect.

##### Default values

When just calling `init()` without the object of parameters, the following default values are used:
	
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

| Constant                                    | Where to use?                |
|:--------------------------------------------|:-----------------------------|
| **DEFAULT_KONTAKT_BEACON_PROXIMITY_UUID**   | uuid (region)                |
| **BEACON_REGION_ANY_MAJOR**                 | major (region)               |
| **BEACON_REGION_ANY_MINOR**                 | minor (region)               |
| **DEFAULT_KONTAKT_NAMESPACE_ID**            | namespace (region)           |
| **IBEACON**                                 | init (second argument)       |
| **EDDYSTONE**                               | init  (second argument)      |

### **iOS** API Documentation

#### Main objects: `beacon` and `region`

The following two objects are the main players of this module and will be referred to multiple times throughout this documentation:

##### `beacon`

* In contrast to the *Android* version the `beacon` object has a different shape depending on whether 1) scanning or 2) ranging/monitoring is used.

1. While ranging or monitoring

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

2. While scanning

	```js
	{
		name: string  // 'Kontakt' by default for Kontakt.io beacons
		uniqueId: string
		firmwareVersion: string
		batteryLevel: number (percentage as int) // batteryPower for Android
		batteryPowered: boolean
		hasConfigurationProfile: boolean
		transmissionPower: number  // txPower for Android
		rssi: number
		model: string
		locked: boolean
		shuffled: boolean
	}
	```

##### `region`

```js
{
	identifier
	uuid
}
```

#### Events

* Ranging, monitoring and scanning are three different processes. In contrast to the *Android* version they are separated into different events and methods. Pay attention to the type column.
* Scanning (i.e. `didDiscoverDevices`) can only detect Kontakt.io beacons. Ranging and monitoring also works with beacons of other manufacturers.

##### Event overview

| Event                      | Type | Description                       |
|:---------------------------|:-----|:----------------------------------|
| **didDiscoverDevices**     | Scanning | Sends `{ beacons }` if Kontakt.io beacons are in range. `beacons` and `region` have the form as defined above. |
| **devicesManagerDidFailToStartDiscovery**     | Scanning | Sends `{ error }` if scanning can't be started. |
| **didRangeBeacons**       | Ranging | Sends `{ beacons, region }` with currently ranged beacons in the region. If the configuration `dropEmptyRanges` is set to `true`, the event is not send if the array of beacons is empty. |
| **didStartMonitoringForRegion**         | Monitoring | Sends `{ region }`, the beacon region for which monitoring started. |
| **monitoringDidFailForRegion**         | Monitoring | Sends `{ region, error }`, the beacon region for which the error `error` occurred. |
| **didEnterRegion**         | Monitoring | Sends `{ region }`, the beacon region which was just entered (i.e. at least one beacon of that region was detected). |
| **didExitRegion**          | Monitoring | Sends `{ region }`, the beacon region which was just lost (i.e. the last remaining beacon of that region was not anymore in range and the time for keeping the beacon in the internal cache ran out as set with `invalidationAge` |
| **didChangeLocationAuthorizationStatus**        | Authorization | Sends `{ status }`, the current authorization status. |

#### Methods

##### General information

* All methods are properties of the default import (i.e. `import Kontakt from 'react-native-kontaktio`).
* All methods return a **Promise** which returns an error statement in case something went wrong.
* The best way to explore the usage of these methods is to take a look at the example in [Example/src/Example.android.js](/Example/src/Example.android.js).

##### Method overview

| Method                         | Type |Description                     |
|:-------------------------------|:-----|:--------------------------------|
| **init('KontaktAPIKey')** | General |(*optional*) Add your `Kontakt.io` API-Key as a string. It's not needed for regular beacon scanning, but for **connecting** to your beacons. |
| **configure({ ... })**          | General | (*optional*) Configure scanning with the configuration options described below |
| **startScanning({ interval })**        | Scanning | starts general scanning for the discovery of beacons not constrained to any region. Optionally an object with the field `interval` with a time in milliseconds may be passed with the method call. Scanning will be paused for the time of the interval. If beacons are discovered in the proximity of your device the **didDiscoverDevices** event will be triggered |
| **stopScanning**         | Scanning | stops scanning for all provided regions |
| **restartScanning**      | Scanning | stops and starts scanning again (NOT FULLY TESTED YET). |
| **isScanning**      | Scanning | fulfills the Promise with *true* if scanning is currently in progress. |
| **startRangingBeaconsInRegion**        | Ranging | starts ranging in provided `region`. If beacons are ranged in the proximity of your device the **didRangeBeacons** event will be triggered |
| **stopRangingBeaconsInRegion**         | Ranging | stops ranging for the provided `region` |
| **stopRangingBeaconsInAllRegions**         | Ranging | stops ranging for all regions |
| **getRangedRegions**         | Ranging | returns all currently ranged `regions` |
| **startMonitoringForRegion**        | Monitoring | starts monitoring in provided `region`. If beacons of a monitored region appear in the proximity of your device the **didEnterRegion** event will be triggered. |
| **stopMonitoringForRegion**         | Monitoring | stops monitoring for the  provided region |
| **stopMonitoringForAllRegions**         | Monitoring | stops monitoring for all currently monitored regions |
| **getMonitoredRegions**         | Monitoring | Returns all currently monitored `regions` |
| **getAuthorizationStatus**         | Authorization | returns the authorization `status` (`authorizedAlways` or `authorizedWhenInUse` or `denied` or `notDetermined` or `restricted`) |
| **requestAlwaysAuthorization**         | Authorization | prompt the user to give authorization for the app to always scan for beacons, even if app is not in foreground. |
| **requestWhenInUseAuthorization**         | Authorization | prompt the user to give authorization for the app to scan for beacons, if app is in use. |

#### Configuration

A config object can be passed to the call of the `configure` method with the following fields:

**ATTENTION**: Configurations are not fully tested and don't work properly yet!

| Configuration              | Description                       |
|:---------------------------|:----------------------------------|
| **dropEmptyRanges**        | If `true`, `didDiscoverDevices` and `didRangeBeacons` events don't fire if the array of beacons is empty. Default is true |
| **connectNearbyBeacons**     | Connect to all discovered beacons in vicinity to get iBeacon values like major, minor and uuid while scanning. Default is false. CURRENTLY THIS VALUE HAS NO EFFECT. IN THE CURRENT VERSION beacon connection iS NOT IMPLEMENTED YET. |
| **invalidationAge**       | In milliseconds. It sets the time the device should wait until it "forgets" a formerly scanned beacon when it can't detect it anymore. The default is 10 seconds. |


## Further notes

* Beacons support is part of Android versions 4.3 and up.
	* So far the lowest Android version this library was tested on was a device with Android 4.4.2.
* A physical device must be used for testing, at best you have some Kontakt.io beacons at your disposal, configure them via their management console and have your API-key handy.

## Coming soon:

* Android: Eddystone support (Currently `EDDYSTONE` beacons can be scanned, but the corresponding functions are not yet exposed to the JS side because it wasn't fully tested yet)
