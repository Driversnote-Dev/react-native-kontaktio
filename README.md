# react-native-kontaktio [![npm version](https://badge.fury.io/js/react-native-kontaktio.svg)](https://badge.fury.io/js/react-native-kontaktio)

Cross-platform React Native module for detecting beacons with **Android** and **iOS** devices.

Kontakt.io SDK Versions of newest release:

| OS          | SDK Version                                                                                          |
| :---------- | :--------------------------------------------------------------------------------------------------- |
| **Android** | [7.0.6](https://kontakt-api-docs.stoplight.io/docs/dev-ctr-sdks/423dcaf4067cc-android-sdk-changelog) |
| **iOS**     | [3.0.4](https://github.com/kontaktio/kontakt-ios-sdk/tree/v3.0.4)                                    |

## Advantages

- Works with any beacon (because the Kontakt.io SDK wraps the native beacon libraries (while adding more) - no Kontakt.io SDK API key is necessary.
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

### Minimal TypeScript Example

A minimal example (created with [React Native v0.69.5](https://github.com/facebook/react-native/releases/tag/v0.69.5) and TypeScript) with the default configuration and no specifically set regions. Thus, the default region `everywhere` (i.e. all beacons) is automatically used.

1. Follow the setup instructions carefully for `iOS` and `Android` to install `react-native-kontaktio` for both platforms.
2. Start a new React Native TypeScript project (`npx react-native init BeaconTest --template react-native-template-typescript`) and replace `App.tsx` with the example code below.
3. Run the app on a real device (`iOS` or `Android` - not a simulator)
4. Check the React Native logs to see console statements containing incoming beacon signals.

```ts
import React, { useEffect } from 'react';
import {
  Alert,
  DeviceEventEmitter,
  NativeEventEmitter,
  PermissionsAndroid,
  Platform,
  SafeAreaView,
  StatusBar,
  StyleSheet,
  Text,
  View,
} from 'react-native';

import Kontakt, { KontaktModule } from 'react-native-kontaktio';
const {
  connect,
  init,
  startDiscovery,
  startRangingBeaconsInRegion,
  startScanning,
} = Kontakt;

const kontaktEmitter = new NativeEventEmitter(KontaktModule);

const isAndroid = Platform.OS === 'android';

/**
 * Android Marshmallow (6.0) and above need to ask the user to grant certain permissions.
 * This function does just that.
 */
const requestLocationPermission = async () => {
  try {
    const granted = await PermissionsAndroid.request(
      PermissionsAndroid.PERMISSIONS.ACCESS_FINE_LOCATION,
      {
        title: 'Location Permission',
        message:
          'This example app needs to access your location in order to use bluetooth beacons.',
        buttonNeutral: 'Ask Me Later',
        buttonNegative: 'Cancel',
        buttonPositive: 'OK',
      }
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
        [{ text: 'OK', onPress: () => console.log('OK Pressed') }],
        { cancelable: false }
      );
    }
  } else {
    // iOS
    await init();

    /**
     * Will discover Kontakt.io beacons only
     */
    await startDiscovery();

    /**
     * Works with any beacon(also virtual beacon, e.g. https://github.com/timd/MactsAsBeacon)
     * Requires user to allow GPS Location (at least while in use)
     *
     * change to match your beacon values
     */
    await startRangingBeaconsInRegion({
      identifier: '',
      uuid: 'A4826DE4-1EA9-4E47-8321-CB7A61E4667E',
      major: 1,
      minor: 34,
    });
  }

  // Add beacon listener
  if (isAndroid) {
    /* works with any beacon */
    DeviceEventEmitter.addListener(
      'beaconsDidUpdate',
      ({ beacons, region }) => {
        console.log('beaconsDidUpdate', { beacons, region });
      },
    );
  } else {
    /* works with Kontakt.io beacons only */
    kontaktEmitter.addListener('didDiscoverDevices', ({ beacons }) => {
      console.log('didDiscoverDevices', { beacons });
    });

    /* works with any beacon */
    kontaktEmitter.addListener('didRangeBeacons', ({ beacons, region }) => {
      console.log('didRangeBeacons', { beacons, region });
    });
  }
};

const App: React.FC = () => {
  useEffect(() => {
    Promise.resolve().then(beaconSetup);

    return () => {
      // remove event listeners
      if (isAndroid) {
        kontaktEmitter.removeAllListeners('beaconsDidUpdate');
      } else {
        kontaktEmitter.removeAllListeners('didDiscoverDevices');
        kontaktEmitter.removeAllListeners('didRangeBeacons');
      }
    };
  }, []);

  return (
    <SafeAreaView>
      <StatusBar barStyle="dark-content" />
      <View style={styles.wrapper}>
        <Text style={styles.title}>react-native-kontaktio Example</Text>
        <Text>Check console.log statements</Text>
      </View>
    </SafeAreaView>
  );
};

const styles = StyleSheet.create({
  wrapper: {
    height: '100%',
    justifyContent: 'center',
    alignItems: 'center',
  },
  title: {
    paddingVertical: 10,
    fontSize: 30,
  },
});

export default App;
```

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
- A physical device must be used for testing and some beacons (Kontakt.io beacons to be able to use all features).

## ToDo:

- Update Android Eddystone feature:

  - Add _multiple_ Eddystone namespaces, i.e. add function `setEddystoneNamespaces`
  - Add Eddystone Frames Selection configuration option

## Contribute

### Test library changes locally

1. Fork and clone this repository
2. Run `yarn` to install the dependencies
3. Make code changes
4. Delete `lib` folder if it exists and run `yarn tsc` to compile the TypeScript files in the the `lib` folder.
5. In the `package.json` file of an example app point to the this directory, e.g.

    ```json
    "dependencies": {
      ...
      "react-native-kontaktio": "../react-native-kontaktio"
    },
    ```
6. Build and run on a real device

### Upgrade Kontakt.io API versions

#### Android

In `build.gradle` file change the version in the following line

```
implementation "io.kontakt.mvn:sdk:7.0.6"
```
