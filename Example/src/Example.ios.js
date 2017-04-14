import React, { Component } from 'react';
import {
  StyleSheet,
  Text,
  View,
  // DeviceEventEmitter,
  NativeEventEmitter,
  NativeModules,
} from 'react-native';

import Kontakt, { KontaktModule } from 'react-native-kontaktio';

const kontaktEmitter = new NativeEventEmitter(KontaktModule);

export default class IBeaconExample extends Component {
  state = {
    initText: '',
  };

  componentDidMount() {
    // Initialization, configuration and adding of beacon regions
    KontaktModule.initBeacons()
      .then(text => this.setState({ initText: text }))
      .catch(error => this.setState({ initText: error }));

    const subscription = kontaktEmitter.addListener(
      // 'didEnterRegion',
      'EventReminder',
      (region) => console.log('subscription result', region),
    );

    Kontakt.test();
    console.log("andre constant", Kontakt.ANDRE_CONSTANT);

    /**
     * Test function with promise
     */
    async function updateEvents() {
      try {
        const events = await KontaktModule.findEvents();

        console.log('events', events );
      } catch (e) {
        console.error(e);
      }
    }

    updateEvents();

  }

  componentWillUnmount() {
    // Don't forget to unsubscribe, typically in componentWillUnmount
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
    justifyContent: 'center',
    alignItems: 'center',
  },
  text: {
    fontSize: 18,
    fontWeight: 'bold',
    color: 'blue',
  },
});
