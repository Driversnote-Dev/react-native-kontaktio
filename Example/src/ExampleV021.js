import React, { Component } from 'react';
import {
  StyleSheet,
  Text,
  View,
  DeviceEventEmitter,
  ScrollView,
  TouchableOpacity,
} from 'react-native';

import KontaktBeacons from 'react-native-kontaktio';

// Define iBeacon region
const region = {
  identifier: 'MY_BEACON_REGION',
  uuid: 'MY_UUID',
  major: 1,
  minor: KontaktBeacons.ANY_MINOR,
};

// Define eddystone namespace
const namespace = {
  namespaceId: 'abcdef1234567890abcd',
};

const scanContext = {
  iBeaconDevicesUpdateCallbackInterval: 100,
  eddystoneDevicesUpdateCallbackInterval: 1000,
  iBeaconDistanceSort: KontaktBeacons.SORT_DESC,
  eddystoneDistanceSort: KontaktBeacons.SORT_ASC,
};

/**
 * NB: Example for an OLD version of this package
 * (for react-native-kontaktio v0.2.1 and below)
 * ---------
 * Ranges beacons and sorts them by proximity
 */
export default class ExampleV021 extends Component {
  constructor(props) {
    super(props);
    this.state = {
      scanStatus: '',
      scanInitStatus: '',
      scanning: false,
      beacons: [],
    };
  }

  componentDidMount() {
    KontaktBeacons.initKontaktSDKWithApiKey('MY_KONTAKTIO_API_KEY');
    DeviceEventEmitter.addListener(
      'beaconsDidRange',
      (data) => {
        this.setState({
          beacons: data.beacons.filter(beacon => beacon.rssi < 0),
        });
        data.beacons.map(beacon => console.log('minor', beacon.minor));
      }
    );
    DeviceEventEmitter.addListener(
      'scanInitStatus',
      (data) => {
        this.setState({ scanInitStatus: data.status });
      }
    );
    DeviceEventEmitter.addListener(
      'scanStatus',
      (data) => {
        this.setState({ scanStatus: data.scanStatus });
      }
    );
  }

  _startScanning = () => {
    KontaktBeacons.startRangingBeaconsInRegion(region, scanContext);
    this.setState({ scanning: true });
  };
  _stopScanning = () => {
    KontaktBeacons.stopRangingBeaconsInRegion();
    this.setState({
      scanning: false,
      beacons: [],
    });
  };
  _restartScanning = () => {
    KontaktBeacons.restartRangingBeaconsInRegion(region, scanContext);
    this.setState({ scanning: true });
  };

  _renderBeacons = () => {
    const colors = ['#F7C376', '#EFF7B7', '#F4CDED', '#A2C8F9', '#AAF7AF'];

    return this.state.beacons.sort((a, b) => (-1 * (a.rssi - b.rssi))).map((beacon, ind) => (
      <View key={ind} style={[styles.beacon, {backgroundColor: colors[beacon.minor - 1]}]}>
        <Text style={{fontWeight: 'bold'}}>{beacon.uniqueID}</Text>
        <Text>Minor: {beacon.minor}, RSSI: {beacon.rssi}</Text>
        <Text>Distance: {beacon.accuracy}, Proximity: {beacon.proximity}</Text>
        <Text>Battery Power: {beacon.batteryPower}, TxPower: {beacon.txPower}</Text>
        <Text>FirmwareVersion: {beacon.firmwareVersion}, UniqueID: {beacon.uniqueID}</Text>
      </View>
    ), this);
  };

  // _renderWaitingForBeacons = () => (
  //   <View>
  //     <Text style={styles.loadingText}>Searching for BEACONS in your vicinity...</Text>
  //   </View>
  // );

  _renderButton = (text, onPress) => (
    <TouchableOpacity style={styles.button} onPress={onPress}>
      <Text>{text}</Text>
    </TouchableOpacity>
  );

  render() {
    return (
      <View style={styles.container}>
        <View style={styles.buttonContainer}>
          {this._renderButton('Start scan', this._startScanning)}
          {this._renderButton('Stop scan', this._stopScanning)}
          {this._renderButton('Restart scan', this._restartScanning)}
        </View>
        <View style={styles.scanStatus}>
          <Text>Scan status: {this.state.scanStatus}</Text>
          <Text>ScanInit status: {this.state.scanInitStatus}</Text>
        </View>

        <ScrollView style={styles.scrollView}>
          {this._renderBeacons()}
        </ScrollView>
      </View>
    );
  }
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
  },
  beacon: {
    justifyContent: 'space-around',
    alignItems: 'center',
    padding: 10,
  },
  loadingText: {
    margin: 10,
    flex: 1,
    fontSize: 18,
    fontWeight: 'bold',
  },
  scanStatus: {
    margin: 10,
  },
  buttonContainer: {
    marginVertical: 20,
    flexDirection: 'row',
    alignItems: 'center',
    justifyContent: 'space-around',
  },
  button: {
    padding: 10,
    backgroundColor: '#5BF759',
    borderRadius: 10,
  },
});
