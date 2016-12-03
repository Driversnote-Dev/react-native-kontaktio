import React from 'react';
import {
  AppRegistry,
} from 'react-native';

import IBeaconExample from './IBeaconExample';

export default function native() {
  AppRegistry.registerComponent('KontaktIoSimpleTest', () => IBeaconExample);
}
