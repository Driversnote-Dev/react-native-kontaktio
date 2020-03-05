# react-native-kontaktio [![npm version](https://badge.fury.io/js/react-native-kontaktio.svg)](https://badge.fury.io/js/react-native-kontaktio)

Cross-platform React Native module for detecting beacons with **Android** and **iOS** devices.

Kontakt.io SDK Versions of newest release:

| OS          | SDK Version                                                                                              |
| :---------- | :------------------------------------------------------------------------------------------------------- |
| **Android** | [4.0.1](http://kontaktio.github.io/kontakt-android-sdk/4.0.2/Javadoc/) (Documentation points to `4.0.2`) |
| **iOS**     | [1.5.1](http://kontaktio.github.io/kontakt-ios-sdk/Documentation/html/)                                  |

The documentation points to `4.0.2` because there is none specifically for `4.0.1`. The Android SDK Version `4.0.2` [could not be installed](https://github.com/kontaktio/kontakt-android-sdk/issues/186).

## Advantages

- Works with any beacon (becquse the Kontakt.io SDK wraps the native beacon libraries (while adding more) - no Kontakt.io SDK API key is necessary.
- Especially useful with [Kontakt.io](http://kontakt.io/) beacons because additional information like the **unique id** (on the back of each beacon), the **battery power level** and others are available and get synchronized with your Kontakt.io online panel.
- Highly customizable configurations (e.g. for setting arbitrary monitoring intervals on Android)

## Setup

- [Android Setup](/docs/setup.android.md)
- [iOS Setup](/docs/setup.ios.md)

## API Documentation

- [Android Documentation](/docs/api.android.md)
- [iOS Documentation](/docs/api.ios.md)

## Examples

### Extensive Example

- [Android extensive Example](/Example/src/Example.android.js)
- [iOS extensive Example](/Example/src/Example.ios.js)

### Minimal Example

A minimal example (created with [React Native v0.61](https://github.com/facebook/react-native/releases/tag/v0.61.0))
with the default configuration and no specifically set regions. Thus, the default region `everywhere` (i.e. all beacons) is automatically used.
Make sure to follow the setup instructions carefully for `iOS` and `Android` and
check the React Native logs to see console statements containing incoming beacon signals.

```js
import React, {useEffect} from 'react';
import {
  Alert,
  DeviceEventEmitter,
  NativeEventEmitter,
  Platform,
  PermissionsAndroid,
  SafeAreaView,
  StatusBar,
  Text,
} from 'react-native';

import Kontakt, {KontaktModule} from 'react-native-kontaktio';
const {connect, init, startDiscovery, startScanning} = Kontakt;

const kontaktEmitter = new NativeEventEmitter(KontaktModule);

const isAndroid = Platform.OS === 'android';

/**
 * Android Marshmallow (6.0) and above need to ask the user to grant certain permissions.
 * This function does just that.
 */
const requestLocationPermission = async () => {
  try {
    const granted = await PermissionsAndroid.request(
      PermissionsAndroid.PERMISSIONS.ACCESS_COARSE_LOCATION,
      {
        title: 'Location Permission',
        message:
          'This example app needs to access your location in order to use bluetooth beacons.',
        buttonNeutral: 'Ask Me Later',
        buttonNegative: 'Cancel',
        buttonPositive: 'OK',
      },
    );
    if (granted === PermissionsAndroid.RESULTS.GRANTED) {
      return true;
    } else {
      // permission denied
      return false;
    }
  } catch (err) {
    console.warn(err);
    return false;
  }
};

const beaconSetup = async () => {
  if (isAndroid) {
    // Android
    const granted = await requestLocationPermission();
    if (granted) {
      await connect();
      await startScanning();
    } else {
      Alert.alert(
        'Permission error',
        'Location permission not granted. Cannot scan for beacons',
        [{text: 'OK', onPress: () => console.log('OK Pressed')}],
        {cancelable: false},
      );
    }
  } else {
    // iOS
    await init();
    await startDiscovery();
  }

  // Add beacon listener
  if (isAndroid) {
    DeviceEventEmitter.addListener('beaconsDidUpdate', ({beacons, region}) => {
      console.log('beaconsDidUpdate', beacons, region);
    });
  } else {
    kontaktEmitter.addListener('didDiscoverDevices', ({beacons}) => {
      console.log('didDiscoverDevices', beacons);
    });
  }
};

const App: () => React$Node = () => {
  useEffect(() => {
    beaconSetup();
  }, []);

  return (
    <>
      <StatusBar barStyle="dark-content" />
      <SafeAreaView>
        <Text>react-native-kontaktio Example</Text>
      </SafeAreaView>
    </>
  );
};

export default App;
```

## Run Example to test the module

1. Go to the [Getting Started section](https://reactnative.dev/docs/getting-started.html) of the React Native docs and select the `React Native CLI Quickstart` tab (bluetooth is not yet supported by Expo).
2. Run the app to verify everything works (`react-native run-android` or `react-native run-ios`)
3. Copy the Minimal Example code from above into the `App.js` file which got created.

---

**Note (March 2020)**: The example in the `Example/` folder is a bit outdated. If you want to try to run the example app anyway, here are some instructions to do so:

1.  Clone this repository, connect an Android and/or Apple device to your computer and have some (Kontakt.io) beacons nearby.

2.  Open a terminal window, bash to the `Example/` folder, run `npm install` and start the react-native server

    ```bash
    $ cd react-native-kontaktio/Example
    $ npm install
    $ npm start
    ```

3.  Build the example and run it on your device. The app will appear under the name `KontaktIoSimpleTest`:

    - Android:

      	```bash
      $ react-native run-android
      ```

    - iOS

      	```bash
      $ react-native run-ios
      ```

## Further notes

- Beacons support is part of Android versions 4.3 and up. \* So far the lowest Android version this library was tested on was a device with Android 4.4.2.
- A physical device must be used for testing, at best some Kontakt.io beacons.

## ToDo:

- Update Android Eddystone feature:

  - Add _multiple_ Eddystone namespaces, i.e. add function `setEddystoneNamespaces`
  - Add Eddystone Frames Selection configuration option

