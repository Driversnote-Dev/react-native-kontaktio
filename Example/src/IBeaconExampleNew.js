import React, { Component } from 'react';
import {
  StyleSheet,
  Text,
  View,
  DeviceEventEmitter,
  ScrollView,
  TouchableOpacity,
} from 'react-native';

import {
  init,
  configure,
  startScanning,
  stopScanning,
  restartScanning,
  setBeaconRegion,
  setBeaconRegions,
  IBEACON,
  EDDYSTONE,
  ScanMode,
  ScanPeriod,
  ActivityCheckConfiguration,
} from 'react-native-kontaktio';

const region1 = {
  identifier: 'Andre beacons',
  uuid: 'B0702880-A295-A8AB-F734-031A98A512D3',
  major: 2,
};

const region2 = {
  identifier: 'Andre beacons',
  uuid: 'B0702880-A295-A8AB-F734-031A98A512D3',
  major: 4,
};

/**
 * Ranges beacons and sorts them by proximity
 */
export default class IBeaconExampleNew extends Component {
  constructor(props, context) {
    super(props, context);
    this.state = {
      scanning: false,
      beacons: [],
    };
  }

  componentDidMount() {
    init(
      'MY_KONTAKTIO_API_KEY',
      [IBEACON, EDDYSTONE],
    )
      .then(() => console.log('init was successful'))
      .then(() => configure({
        scanMode: ScanMode.BALANCED.getConfig(),
        scanPeriod: ScanPeriod.RANGING.getConfig(),
        activityCheckConfiguration: ActivityCheckConfiguration.DEFAULT.getConfig(),
      }))
      .then(() => console.log('config was successful'))
      .then(() => setBeaconRegions([region1, region2]))
      .then(() => console.log('region setting was successful'))
      .catch(error => console.log('init or config had error', error));

    DeviceEventEmitter.addListener(
      'beaconDidAppear',
      (data) => {
        console.log('beacondidAppear', data);
      }
    );
    DeviceEventEmitter.addListener(
      'beaconsDidRange',
      (data) => {
        console.log('beaconsDidRange', data);
        this.setState({
          beacons: data.beacons.filter(beacon => beacon.rssi < 0),
        });
      }
    );
    DeviceEventEmitter.addListener(
      'regionDidEnter',
      (data) => {
        console.log('regionDidEnter', data);
      }
    );
  }

  _startScanning = () => {
    startScanning()
      .then(() => this.setState({ scanning: true }))
      .then(() => console.log('started scanning'))
      .catch(error => console.log('error while starting to scan', error));
  };
  _stopScanning = () => {
    stopScanning()
      .then(() =>
        this.setState({
          scanning: false,
          beacons: [],
        })
      )
      .then(() => console.log('stopped scanning'))
      .catch(error => console.log('error while stopping to scan', error));
  };
  _restartScanning = () => {
    restartScanning()
      .then(() => this.setState({ scanning: true }))
      .then(() => console.log('restarted scanning'));

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
