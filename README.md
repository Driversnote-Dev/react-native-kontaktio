# react-native-kontaktio [![npm version](https://badge.fury.io/js/react-native-kontaktio.svg)](https://badge.fury.io/js/react-native-kontaktio)

React-native module for detecting [Kontakt.io](http://kontakt.io/) beacons. You have to be in possession of Kontakt.io beacons, configure them via their management console and have your api-key handy.

With the Kontakt.io SDK (which this module is accessing in native Android) you have access to more values than a generic beacon library like e.g. [altBeacon](http://altbeacon.org/) can offer, e.g. `batteryPower` or `txPower`.

Parts of the code and namings of output have been based on and influenced by the projects [react-native-alt-beacon](https://github.com/octavioturra/react-native-alt-beacon) and [react-native-ibeacon](https://github.com/frostney/react-native-ibeacon).

## Run Example

1. Clone this repository
2. Bash to the `Example/` folder, run npm install and start the react-native server

	```bash
	$ cd react-native-kontaktio/Example
	$ npm install
	$ npm start
	```

2. Configure five beacons and enter their UUID and MAJOR values in the `region` in the file `react-native-kontaktio/Example/src/IBeaconExample.js` :

	```js
	...
	const region = {
	  identifier: 'MY_BEACON_REGION',
	  uuid: 'MY_UUID',
	  major: 1,
	  minor: KontaktBeacons.ANY_MINOR,
	};
	...
	```
	
3. Inside the `Example/` folder, start connect a real Android device to your computer, check that it's there with `android adb` and run the Example:

	```bash
	$ adb devices
	$ react-native run-android
	```

## Setup

Some [Kontakt.io beacons prerequisites](http://developer.kontakt.io/android-sdk/2.1.0/quickstart/#setup) have to be met.

#### Android

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

## Usage Example

Basic example with five beacons. Run `react-native init KontaktTest`, install `react-native-kontaktio` as described above and replace the contents of `index.android.js` with the following code. Further replace `MY_KONTAKTIO_API_KEY `, `MY_UUID`, major and minor values with the values of your beacons. If you press on `Start scanning` you should then very soon see your beacons in a ScrollView sorted by their RSSI which reflects a measure of distance from the beacons to your mobile phone.


*Example/src/IBeaconExample.js*

```js
import React, { Component } from 'react';
import {
  StyleSheet,
  Text,
  View,
  DeviceEventEmitter,
  ScrollView,
  TouchableOpacity,
} from 'react-native';

import KontaktBeacons from 'react-native-kontaktio';

// Define iBeacon region
const region = {
  identifier: 'MY_BEACON_REGION',
  uuid: 'MY_UUID',
  major: 1,
  minor: KontaktBeacons.ANY_MINOR,
};

// Define eddystone namespace
const namespace = {
  namespaceId: 'abcdef1234567890abcd',
};

const scanContext = {
  iBeaconDevicesUpdateCallbackInterval: 100,
  eddystoneDevicesUpdateCallbackInterval: 1000,
  iBeaconDistanceSort: KontaktBeacons.SORT_DESC,
  eddystoneDistanceSort: KontaktBeacons.SORT_ASC,
};

/**
 * Ranges beacons and sorts them by proximity
 */
export default class IBeaconExample extends Component {
  constructor(props) {
    super(props);
    this.state = {
      scanStatus: '',
      scanInitStatus: '',
      scanning: false,
      beacons: [],
    };
  }

  componentDidMount() {
    KontaktBeacons.initKontaktSDKWithApiKey('MY_KONTAKTIO_API_KEY');
    DeviceEventEmitter.addListener(
      'beaconsDidRange',
      (data) => {
        this.setState({
          beacons: data.beacons.filter(beacon => beacon.rssi < 0),
        });
        data.beacons.map(beacon => console.log('minor', beacon.minor));
      }
    );
    DeviceEventEmitter.addListener(
      'scanInitStatus',
      (data) => {
        this.setState({ scanInitStatus: data.status });
      }
    );
    DeviceEventEmitter.addListener(
      'scanStatus',
      (data) => {
        this.setState({ scanStatus: data.scanStatus });
      }
    );
  }

  _startScanning = () => {
    KontaktBeacons.startRangingBeaconsInRegion(region, scanContext);
    this.setState({ scanning: true });
  };
  _stopScanning = () => {
    KontaktBeacons.stopRangingBeaconsInRegion();
    this.setState({
      scanning: false,
      beacons: [],
    });
  };
  _restartScanning = () => {
    KontaktBeacons.restartRangingBeaconsInRegion(region, scanContext);
    this.setState({ scanning: true });
  };

  _renderBeacons = () => {
    const colors = ['#F7C376', '#EFF7B7', '#F4CDED', '#A2C8F9', '#AAF7AF'];

    return this.state.beacons.sort((a, b) => (-1 * (a.rssi - b.rssi))).map((beacon, ind) => (
      <View key={ind} style={[styles.beacon, {backgroundColor: colors[beacon.minor - 1]}]}>
        <Text style={{fontWeight: 'bold'}}>{beacon.uniqueID}</Text>
        <Text>Minor: {beacon.minor}, RSSI: {beacon.rssi}</Text>
        <Text>Distance: {beacon.accuracy}, Proximity: {beacon.proximity}</Text>
        <Text>Battery Power: {beacon.batteryPower}, TxPower: {beacon.txPower}</Text>
        <Text>FirmwareVersion: {beacon.firmwareVersion}, UniqueID: {beacon.uniqueID}</Text>
      </View>
    ), this);
  };

  // _renderWaitingForBeacons = () => (
  //   <View>
  //     <Text style={styles.loadingText}>Searching for BEACONS in your vicinity...</Text>
  //   </View>
  // );

  _renderButton = (text, onPress) => (
    <TouchableOpacity style={styles.button} onPress={onPress}>
      <Text>{text}</Text>
    </TouchableOpacity>
  );

  render() {
    return (
      <View style={styles.container}>
        <View style={styles.buttonContainer}>
          {this._renderButton('Start scan', this._startScanning)}
          {this._renderButton('Stop scan', this._stopScanning)}
          {this._renderButton('Restart scan', this._restartScanning)}
        </View>
        <View style={styles.scanStatus}>
          <Text>Scan status: {this.state.scanStatus}</Text>
          <Text>ScanInit status: {this.state.scanInitStatus}</Text>
        </View>

        <ScrollView style={styles.scrollView}>
          {this._renderBeacons()}
        </ScrollView>
      </View>
    );
  }
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
  },
  beacon: {
    justifyContent: 'space-around',
    alignItems: 'center',
    padding: 10,
  },
  loadingText: {
    margin: 10,
    flex: 1,
    fontSize: 18,
    fontWeight: 'bold',
  },
  scanStatus: {
    margin: 10,
  },
  buttonContainer: {
    marginVertical: 20,
    flexDirection: 'row',
    alignItems: 'center',
    justifyContent: 'space-around',
  },
  button: {
    padding: 10,
    backgroundColor: '#5BF759',
    borderRadius: 10,
  },
});
```


## Documentation

### Events

##### Bluetooth initialization and restart events

* `scanStatus`

	```js
	data
		.status	// values: START or STOP
	```
	
	`START` or `STOP` reflect whether the beacon scan started or stopped

* `scanInitStatus`

	```js
	data
		.status	// values: SUCCESS or FAILURE
	```
	
	* `SUCCESS` or `FAILURE` reflect the state of the initialization of the beacon scan.
	* `SUCCESS_RESTART` or `FAILURE_RESTART` reflect the state of the restart of the beacon scan.

##### Beacon events

* `beaconsDidRange`

	returns information about beacons with updated information

	```js
	...
	data
		.timestamp	// timestamp of event
		.region		// region in which event occured
			.identifier
			.uuid
			.major
			.minor
		.beacons		// Array of all beacons
			// each beacon contains:
			.name
			.address
			.rssi
			.proximity	// values: IMMEDIATE, NEAR, FAR or UNKNOWN
			.accuracy		// distance in meters
			.batteryPower
			.txPower
			.firmwareVersion
			.uniqueId
			// if iBeacon additionally:
			.uuid
			.major
			.minor
			// if Eddystone additionally:
			.instanceId
			.namespaceId
			.url
			.temperature
			.telemetryVersion
			.batteryVoltage
			.timeSincePowerUp
	```
* `beaconDidAppear`

	returns data about the beacon if it is in range for the first time
	
	```js
	data
		.timestamp
		.region  // as above
		.beacon  // a single beacon
			// inside structure of beacon as above
	```

* `beaconDidDisappear`

	returns data about the beacon if it is not in range anymore
	
	```js
	data
		.timestamp
		.region  // as above
		.beacon  // a single beacon
			// inside structure of beacon as above
	```

* `regionDidEnter`

	returns the region entered in structure as above
	
	```js
	data
		.timestamp
		.region
			.identifier
			.uuid
			.major
			.minor
	```

* `regionDidExit`

	returns the region abandoned
	
	```js
	data
		.timestamp
		.region
			.identifier
			.uuid
			.major
			.minor
	```

### Methods

* Configuration

	A config object can be passed with the following options (see [](https://developer.kontakt.io/android-sdk/quickstart/#basic-usage-configuration) and [SDK docs](http://kontaktio.github.io/kontakt-android-sdk/3.2.1/Javadoc/) for more information about all possible configurations). When using the first time, you don't have to pass any configuration and can safely use the default values:
	
	Default values:
	
	```js
	{
	  scanMode: BALANCED,
	  scanPeriod: RANGING,
	  activeCheckConfiguration: DEFAULT,
	  forceScanConfiguration: DISABLED,
	  deviceUpdateCallbackInterval: DEFAULT = 3000 MilliSec,
	  monitoringEnabled: true,
	  monitoringSyncInterval: 10 Sec,
	}
	```
	
	Possible values:
	
	```js
	{
	  scanMode: LOW_POWER | BALANCED | LOW_LATENCY,
	  scanPeriod: RANGING | MONITORING | {
	  	  activePeriod: MINIMAL_ACTIVE_SCAN_PERIOD = 3000 | int (MilliSec)
	  	  passivePeriod: MINIMAL_PASSIVE_SCAN_PERIOD = 2000 | int (MilliSec)
	  	},
	  activityCheckConfiguration: DISABLED | MINIMAL | DEFAULT
	  forceScanConfiguration: DISABLED | MINIMAL | {
	  		forceScanActivePeriod: int (MilliSec > 1000)
	  		forceScanPassivePeriod: int (MilliSec > 500)
	  	},
	  deviceUpdateCallbackInterval: DEFAULT = 3000 | int (MilliSec),
	  monitoringEnabled: bool,
	  monitoringSyncInterval: int (Sec),
	}
	```
	
	Notes:
	
	* `monitoringEnabled` here refers to collecting monitoring events e.g. battery level of device.
	* `monitoringSyncInterval`: Interval between next monitoring events sync attempts with Kontakt.io Web Panel
	* Special info for `ForceScanConfiguration`: It is advisable to make SDK-based application configurable per Android device e.g. by allowing changing ForceScanConfiguration parameters in preferences. Ignoring it may cause poor performance of features provided for the SDK.
	* Use `ScanMode = LOW_LATENCY` only when running the app in the foreground.
	* `forceScanConfiguration` causes the app to 
	

* `initKontaktSDKWithApiKey('123456')`

	Call this method before starting to range for beacons.

	```js
	KontaktBeacons.initKontaktSDKWithApiKey('MY_KONTAKTIO_API_KEY')
	```

* `startRangingBeaconsInRegion(region, scanContext)`

	Starts ranging for beacons. Changes the scan status.

	Example: Range for beacons in the provided `region` with parameters provided in `scanContext`.

	```js
	const region = {
	  identifier: 'Living Room',
	  uuid: 'YOUR_UUID_HERE',
	  major: 123,
	  minor: KontaktBeacons.ANY_MINOR,
	};
	
	const scanContext = {
	  devicesUpdateCallbackInterval: 3000,
	  distanceSort: KontaktBeacons.SORT_DESC,
	}
	
	KontaktBeacons.startRangingBeaconsInRegion(region, scanContext)
	```

	Check the Kontakt.io Android SDK docs for further information about how to define the `scanContext`.

* `stopRangingBeaconsInRegion()`

	Stop ranging for beacons. Changes the scan status.

* `restartRangingBeaconsInRegion(region, scanContext)`

	Stop and start ranging for beacons in one command.

* `startRangingBeaconsInNamespace(namespace, scanContext)`

	Not implemented yet.

### Constants

##### Usage

If the module is importet as 

```js
import KontaktBeacons from 'react-native-kontaktio';
```

constants may be called as:

```js
KontaktBeacons.PROXIMITY_FAR
```

##### Definitions

Defining a region:

* `DEFAULT_KONTAKT_BEACON_PROXIMITY_UUID`: A random UUID
* `ANY_MAJOR`
* `ANY_MINOR`

Evaluating proximity:

* `PROXIMITY_IMMEDIATE`
* `PROXIMITY_NEAR`
* `PROXIMITY_FAR`
* `PROXIMITY_UNKNOWN`

Defining sorting of beacon array:

* `SORT_ASC`
* `SORT_DESC`
* `SORT_DISABLED`

## Some notes

* Only supports **Android** so far. 
* This library works perfectly well in unison with [react-native-ibeacon](https://github.com/frostney/react-native-ibeacon) to deal with the **iOS** part because most of the events and output values are named the same.
* Own regions can be defined for iBeacons, Eddystone beacons can only range beacons in the hard-coded namespace `abcdef1234567890abcd` so far.
* Beacons support Android versions 4.3 and up.
	* So far the lowest Android version this library was tested on was a device with Android 4.4.2.
* A physical device has to be used for testing
* This module uses the Kontakt.io `ProximityManager` class.

## TODOs

Here's an incomplete list of todos for this project. Help via pull-requests are welcome!

* Define multiple regions
* Customize `ScanContext`
* Set permissions from JS code
* Error handling
* Include new Kontakt.io security feature, i.e. use KontaktProximityManager with Shuffling
* Support custom eddystone namespaces, i.e. implement `startRangingBeaconsInNamespace` function and adapt other parts in code
* Add monitoring of beacons
* iOS version