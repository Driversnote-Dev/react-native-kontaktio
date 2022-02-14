import React, { Component } from 'react';
import { View, NativeEventEmitter, Alert } from 'react-native';
import Kontakt, { KontaktModule } from 'react-native-kontaktio';

const { init, startDiscovery } = Kontakt;

const kontaktEmitter = new NativeEventEmitter(KontaktModule);

/**
 * Minimal example of react-native-kontaktio
 */
export default class MinimalExample extends Component {
  componentDidMount() {
    init('')
      .then(() => startDiscovery())
      .catch((error: Error) => Alert.alert('error', error.message));

    // Add beacon listener
    kontaktEmitter.addListener('didDiscoverDevices', ({ beacons }) => {
      console.log('didDiscoverDevices', beacons);
    });
  }

  render() {
    return <View />;
  }
}
