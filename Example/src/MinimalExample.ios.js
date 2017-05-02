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
