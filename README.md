# react-native-kontaktio [![npm version](https://badge.fury.io/js/react-native-kontaktio.svg)](https://badge.fury.io/js/react-native-kontaktio)

Cross-platform React Native module for detecting beacons with **Android** and **iOS** devices.

Kontakt.io SDK Versions:

| OS             | SDK Version           |
|:---------------|:----------------------|
| **Android**    | [3.3.3](http://kontaktio.github.io/kontakt-android-sdk/3.3.3/Javadoc/) |
| **iOS**        | [1.4.3](http://kontaktio.github.io/kontakt-ios-sdk/Documentation/html/) |

## Advantages

* Works with any beacon (because the Kontakt.io SDK wraps the native beacon libraries (while adding more) - no Kontakt.io SDK API key is necessary.
* Especially useful with [Kontakt.io](http://kontakt.io/) beacons because additional information like the **unique id** (on the back of each beacon), the **battery power level** and others are available and get synchronized with your Kontakt.io online panel.
* Highly customizable configurations (e.g. for setting arbitrary monitoring intervals on Android)


## Setup

* [Android Setup](/docs/setup.android.md)
* [iOS Setup](/docs/setup.ios.md)

## API Documentation

* [Android Documentation](/docs/api.android.md)
* [iOS Documentation](/docs/api.ios.md)

## Examples

### Extensive Example

* [Android extensive Example](/Example/src/Example.android.js)
* [iOS extensive Example](/Example/src/Example.ios.js)

### Minimal Example

A minimal example with the default configuration and no specifically set regions. Thus, the default region `everywhere` (i.e. all beacons) is automatically used.

#### Android

[Example/src/MinimalExample.android.js](/Example/src/MinimalExample.android.js):

```js
import React, { Component } from 'react';
import { View, DeviceEventEmitter } from 'react-native';

import Kontakt from 'react-native-kontaktio';
const { connect, startScanning } = Kontakt;

export default class MinimalExample extends Component {
  componentDidMount() {
    connect()
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

#### iOS

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
      .then(() => startDiscovery())
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

## Further notes

* Beacons support is part of Android versions 4.3 and up.
	* So far the lowest Android version this library was tested on was a device with Android 4.4.2.
* A physical device must be used for testing, at best some Kontakt.io beacons.

## ToDo:

* Update Android Eddystone feature:
	* Add *multiple* Eddystone namespaces, i.e. add function `setEddystoneNamespaces`
	* Add Eddystone Frames Selection configuration option

* iOS: Eddystone support