import { AppRegistry } from 'react-native';

import Example from './Example.android';

export default function native() {
  AppRegistry.registerComponent('KontaktIoSimpleTest', () => Example);
}
