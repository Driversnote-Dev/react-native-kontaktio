import React from 'react';
import {
  AppRegistry,
} from 'react-native';

import IBeaconExampleNew from './IBeaconExampleNew';

export default function native() {
  AppRegistry.registerComponent('KontaktIoSimpleTest', () => IBeaconExampleNew);
}
