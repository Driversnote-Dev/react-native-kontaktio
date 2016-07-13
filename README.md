# react-native-kontaktio

Tested on Android 4.4.2 and 5.1.1.

Beacons are supported from Android 4.3 Jelly Bean (API level 18) and up.

Crashes on Android version 4.1.2. Samsung Galaxy Fame S6810

TODO: Test on a 4.3 device


React-native module for detecting [Kontakt.io](http://kontakt.io/) beacons. You have to own some Kontakt.io beacons, configure them via their managment console and have your api-key handy.

With the Kontakt.io SDK (which this module is accessing in native Android) you have access to more values than a generic beacon library can offer, e.g. `batteryPower` or `txPower`.

Parts of the code and namings of output have been based on and influenced by the projects [react-native-alt-beacon](https://github.com/octavioturra/react-native-alt-beacon) and [react-native-ibeacon](https://github.com/frostney/react-native-ibeacon).

## Some notes

* Only supports **Android** so far. For **iOS** please use [react-native-ibeacon](https://github.com/frostney/react-native-ibeacon) until iOS support is added.
* Own regions can be defined for iBeacons, Eddystone beacons can only range beacons in the hard-coded namespace `abcdef1234567890abcd` so far.
* Supports Android versions 5.0.1. and up
* A physical device has to be used for testing
* Using the Kontakt.io `ProximityManager` class.

## Setup

Some [prerequisites](http://developer.kontakt.io/android-sdk/2.1.0/quickstart/#setup) have to be met.

For react-native 0.19.0 and higher:

	$ rnvm install --save react-native-kontaktio

### Manual setup

#### Android

see [the official kontakt.io Android SDK quick start guide](http://developer.kontakt.io/android-sdk/2.1.0/quickstart/)

Do the following in `Android Studio`:

##### Set gradle dependency with Android Studio

in `android/build.gradle`:

Add maven link and packagingOptions

```
...
android {
	...
    packagingOptions {
        exclude 'main/AndroidManifest.xml'
    }
}
...
allprojects {
    repositories {
    	...
       maven { url "http://repo.kontakt.io/repository/internal/" }
    }
}

```

in `android/app/build.gradle`:

Add dependency

```
dependencies {
...
	compile "com.kontakt.sdk.android:kontakt.io-android-sdk:2.1.0"
}
```

No **sync** gradle file changes

##### Set permissions

in `android/app/src/main/AndroidManifest.xml`:

Add service and permissions

```
...
		<service android:name="com.kontakt.sdk.android.ble.service.ProximityService" android:exported="false"/>
	</application>
	
	<!-- Ranging/monitoring beacons -->
    <uses-permission android:name="android.permission.BLUETOOTH"/>

    <!-- Connecting to beacons -->
    <uses-permission android:name="android.permission.BLUETOOTH_ADMIN"/>

    <!-- Communicating with the Kontakt.io Proximity REST API -->
    <uses-permission android:name="android.permission.INTERNET" />
    <uses-permission android:name="android.permission.ACCESS_NETWORK_STATE"/>

    <!-- Since Marshmallow -->
    <uses-permission android:name="android.permission.ACCESS_COARSE_LOCATION" />
    <!-- or -->
    <!-- <uses-permission android:name="android.permission.ACCESS_FINE_LOCATION" /> -->

</manifest>
```

##### Proguard

in `android/app/proguard-rules.pro`:

Add the following:

```
# Kontakt.io

-keep class com.squareup.okhttp.** { *; }
-keep interface com.squareup.okhttp.** { *; }
-dontwarn com.squareup.okhttp.**
-dontwarn okio.**

-keep class com.kontakt.sdk.** { *; }
-keep interface com.kontakt.sdk.** { *; }
```


## Usage

Basic example which you can put into your `index.android.js`. Just replace `MY_KONTAKTIO_API_KEY `, `MY_UUID`, major and minor values with the values you need and you should be able to range beacons in your specified region.

```js
import React, {
  ...
  DeviceEventEmitter,
} from 'react-native';

import Beacons from 'react-native-kontaktio';

// Define beacon region
const region = {
  identifier: 'MY_BEACON_REGION',
  uuid: 'MY_UUID',
  major: 123,
  minor: null,
};

Beacons.initKontaktSDK("MY_KONTAKTIO_API_KEY");

class testBeacons extends Component {

  constructor(props) {
    super(props);
    Beacons.startRangingBeaconsInRegion(region); 
    this.state = {
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
  }

  _renderBeacons = () => {
    return this.state.beacons.sort((a, b) => (-1 * (a.rssi - b.rssi))).map((beacon, ind) => (
        <View key={ind}>
          <Text>Minor: {beacon.minor}, RSSI: {beacon.rssi}</Text>
        </View>
    ), this);
  };

  render() {
    return (
      <ScrollView>
        { this._renderBeacons() }
      </ScrollView>
    );
  }
}

AppRegistry.registerComponent('testBeacons', () => testBeacons);
```

## Events

* `scanStatus`

	```js
	data
		.status
	```
	`data.status` may have the following values:
	
	* `START` or `STOP` reflecting whether the beacon scan started or stopped

* `scanInitStatus`

	```js
	data
		.status
	```
	`data.status` may have the following values:
	
	* `SUCCESS` or `FAILURE` reflecting the state of the initialization of the beacon scan.

#### Data structure of beacon events

```js
data
	.timestamp  	// timestamp of event
	.region		// region in which event occured
		.identifier
		.uuid
		.major
		.minor
```

#### Event specific response

returns an array of beacons with updated information

* `beaconsDidRange`

	```js
	...
	.beacons  // Array of all beacons
		// each beacon contains
		.name
		.address
		.rssi
		.proximity  // either IMMEDIATE, NEAR, FAR or UNKNOWN
		.distance
		.batteryPower
		.txPower
		.firmwareVersion
		.uniqueID
		// if iBeacon additionally
		.uuid
		.major
		.minor
		// if Eddystone additionally
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

## Methods

* `initKontaktSDKWithApiKey`

	Call this method before starting to range for beacons.

	```js
	Beacons.initKontaktSDKWithApiKey("MY_KONTAKTIO_API_KEY")
	```

* `startRangingBeaconsInRegion`

	Example: Range for beacons in the provided `region` with parameters provided in `scanContext`.

	```js
	const region = {
	  identifier: 'Living Room',
	  uuid: 'YOUR_UUID_HERE',
	  major: 123,
	  minor: BEACONS.ANY_MINOR,
	};
	
	const scanContext = {
	  devicesUpdateCallbackInterval: 3000,
	  distanceSort: BEACONS.SORT_DESC,
	}
	
	Beacons.startRangingBeaconsInRegion(region, scanContext)
	```

	


## Constants

#### Usage

If the module is importet as 

```js
import Beacons from 'react-native-kontaktio';
```

constants may be called as:

```js
Beacons.PROXIMITY_FAR
```

#### Definitions

Defining a region:

* `DEFAULT_KONTAKT_BEACON_PROXIMITY_UUID`
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

Here's an incomplete list of todos for this project which I am planing to work on in the future. Help via pull-requests are welcome!

* Define multiple regions
* Customize `ScanContext`
* Set permissions
* Error handling
* Example app
* Include new security feature, i.e. use KontaktProximityManager with Shuffling
* Support custom eddystone namespaces, i.e. implement `startRangingBeaconsInNamespace` function and adapt other parts in code
* Monitoring beacons
* iOS version