import React, { Component } from 'react';
import { View, DeviceEventEmitter } from 'react-native';

import { init, startScanning } from 'react-native-kontaktio';

/**
 * Minimal example of react-native-kontaktio
 */
export default class MinimalExample extends Component {
  componentDidMount() {
    init()
      .then(() => startScanning())
      .catch(error => alert('error', error));

    // Add beacon listeners
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
