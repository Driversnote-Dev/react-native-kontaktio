import React, { Component } from 'react';
import { View, DeviceEventEmitter } from 'react-native';

import Kontakt from 'react-native-kontaktio';

const { init, startScanning } = Kontakt;

/**
 * Minimal example of react-native-kontaktio
 */
export default class MinimalExample extends Component {
  componentDidMount() {
    init()
      .then(() => startScanning())
      .catch(error => alert('error', error));

    // Add beacon listener
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
