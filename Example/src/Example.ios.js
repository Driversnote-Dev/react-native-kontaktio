import React, { Component } from 'react';
import {
  StyleSheet,
  Text,
  View,
  // DeviceEventEmitter,
  NativeEventEmitter,
} from 'react-native';

import Kontakt, {
  KontaktModule,
  ANDRE_CONSTANT,
} from 'react-native-kontaktio';

const kontaktEmitter = new NativeEventEmitter(KontaktModule);

export default class IBeaconExample extends Component {
  state = {
    initText: '',
  };

  componentDidMount() {
    // Initialization, configuration and adding of beacon regions
    Kontakt.initBeacons()
      .then(text => this.setState({ initText: text }))
      .catch(error => this.setState({ initText: error }));

    const subscription = kontaktEmitter.addListener(
      'didEnterRegion',
      (region) => console.log('subscription result', region),
    );

    console.log("andre constant", ANDRE_CONSTANT);
  }

  componentWillUnmount() {
    subscription.remove();
  }

  render() {
    const { initText } = this.state;

    return (
      <View style={styles.container}>
        <Text>Welcome</Text>
        <Text style={styles.text}>
          {initText}
        </Text>
      </View>
    );
  }
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
  },
  text: {
    fontSize: 18,
    fontWeight: 'bold',
  },
});
