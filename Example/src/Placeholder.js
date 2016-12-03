import React from 'react';
import {
  View,
  Text,
  StyleSheet,
} from 'react-native';

const Placeholder = () => (
  <View style={styles.container}>
    <Text style={styles.text}>Currently there's no iOS version.</Text>
    <Text style={styles.text}>Please check out the Android version.</Text>
  </View>
);

const styles = StyleSheet.create({
  container: {
    flex: 1,
    alignItems: 'center',
    justifyContent: 'center',
  },
  text: {
    fontSize: 16,
    marginBottom: 10,
  },
});

export default Placeholder;
