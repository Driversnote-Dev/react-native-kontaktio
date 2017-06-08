import React from 'react';
import {
  AppRegistry,
} from 'react-native';

import Example from './Example';
// import Example from './MinimalExample';

export default function native() {
  AppRegistry.registerComponent('KontaktIoSimpleTest', () => Example);
}
