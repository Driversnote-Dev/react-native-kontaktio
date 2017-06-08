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
