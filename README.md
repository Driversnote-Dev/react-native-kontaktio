# react-native-kontaktio

React-native module for detecting [Kontakt.io](http://kontakt.io/) beacons. You have to be in possession of Kontakt.io beacons, configure them via their management console and have your api-key handy.

With the Kontakt.io SDK (which this module is accessing in native Android) you have access to more values than a generic beacon library like e.g. [altBeacon](http://altbeacon.org/) can offer, e.g. `batteryPower` or `txPower`.

Parts of the code and namings of output have been based on and influenced by the projects [react-native-alt-beacon](https://github.com/octavioturra/react-native-alt-beacon) and [react-native-ibeacon](https://github.com/frostney/react-native-ibeacon).

## Some notes

* Only supports **Android** so far. 
* This library works perfectly well in unison with [react-native-ibeacon](https://github.com/frostney/react-native-ibeacon) to deal with the **iOS** part because most of the events and output values are named the same.
* Own regions can be defined for iBeacons, Eddystone beacons can only range beacons in the hard-coded namespace `abcdef1234567890abcd` so far.
* Beacons support Android versions 4.3 and up.
	* So far the lowest Android version this library was tested on was a device with Android 4.4.2.
* A physical device has to be used for testing
* This module uses the Kontakt.io `ProximityManager` class.

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


*index.android.js*

```js
import React, { Component } from 'react';
import {
  AppRegistry,
  StyleSheet,
  Text,
  View,
  DeviceEventEmitter,
  Dimensions,
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

KontaktBeacons.initKontaktSDKWithApiKey('MY_KONTAKTIO_API_KEY');

/**
 * Ranges beacons and sorts them by proximity
 */
class KontaktTest extends Component {

  constructor(props) {
    super(props);
    this.state = {
      scanStatus: '',
      scanInitStatus: '',
      beacons: [],
    };
  }

  componentDidMount() {
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
        this.setState({
          scanInitStatus: data.status,
        });
      }
    );
    DeviceEventEmitter.addListener(
      'scanStatus',
      (data) => {
        this.setState({
          scanStatus: data.scanStatus,
        });
      }
    );
  }

  
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

  _renderWaitingForBeacons = () => {
    return (
      <View style={styles.container}>
        <Text style={styles.loadingText}>Searching for BEACONS in your vicinity...</Text>
      </View>
    )
  }

  _startScanning = () => {
    KontaktBeacons.startRangingBeaconsInRegion(region, scanContext);
  };

  _stopScanning = () => {
    KontaktBeacons.stopRangingBeaconsInRegion();
  };

  _restartScanning = () => {
    KontaktBeacons.restartRangingBeaconsInRegion(region, scanContext);
  };

  render() {
    return (
      <View style={styles.container}>               
        <View style={styles.scanStatus}>
          <Text>Scan status: {this.state.scanStatus}</Text>
          <Text>ScanInit status: {this.state.scanInitStatus}</Text>
        </View>

        <ScrollView style={styles.scrollView}>
          { this.state.beacons.length > 0 ? this._renderBeacons() : this._renderWaitingForBeacons() }
        </ScrollView>

        <View style={styles.buttonContainer}>
          <TouchableOpacity style={styles.button} onPress={this._startScanning}>
            <Text>Start scan</Text>
          </TouchableOpacity>
              
          <TouchableOpacity style={styles.button} onPress={this._stopScanning}>
            <Text>Stop scan</Text>
          </TouchableOpacity>
              
          <TouchableOpacity style={styles.button} onPress={this._restartScanning}>
            <Text>Restart scan</Text>
          </TouchableOpacity>
        </View>
      </View>
    );
  }
}

const totalWidth = Dimensions.get('window').width;

const styles = StyleSheet.create({
  container: {
    flex: 1,
    alignItems: 'stretch',
  },

  beacon: {
    flex: 1,
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

  scrollView: {
    flex: 6,
  },

  scanStatus: {
    flex: 1,
    padding: 10,
  },

  buttonContainer: {
    flex: 1,
    flexDirection: 'row',
    alignItems: 'center',
    justifyContent: 'space-around',
    margin: 10,
  },
  button: {
    padding: 10,
    backgroundColor: '#5db34b',
    borderRadius: 10,
  },
});

AppRegistry.registerComponent('BeaconBasics', () => KontaktTest);
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
			.uniqueID
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