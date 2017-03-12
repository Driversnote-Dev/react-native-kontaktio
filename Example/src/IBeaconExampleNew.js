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
  // setBeaconRegion,
  setBeaconRegions,
  IBEACON,
  EDDYSTONE,
  ScanMode,
  ScanPeriod,
  ActivityCheckConfiguration,
} from 'react-native-kontaktio';

const region1 = {
  identifier: 'Test beacons 1',
  uuid: 'B0702880-A295-A8AB-F734-031A98A512D3',
  major: 1,
  // no minor provided: will detect all minors
};

const region2 = {
  identifier: 'Test beacons 2',
  uuid: 'B0702880-A295-A8AB-F734-031A98A512D3',
  major: 2,
  // no minor provided: will detect all minors
};

/**
 * Monitors beacons in two regions and sorts them by proximity,
 * color-coded by minors with values 1 through 5.
 */
export default class IBeaconExampleNew extends Component {
  state = {
    scanning: false,
    beacons: [],
  };

  componentDidMount() {
    init(
      'MY_KONTAKTIO_API_KEY',
      [IBEACON, EDDYSTONE],
    )
      .then(() => configure({
        scanMode: ScanMode.BALANCED.getConfig(),
        scanPeriod: ScanPeriod.MONITORING.getConfig(),
        activityCheckConfiguration: ActivityCheckConfiguration.MINIMAL.getConfig(),
      }))
      .then(() => setBeaconRegions([region1, region2]))
      .catch(error => alert('error', error));

    // Add beacon listeners

    DeviceEventEmitter.addListener(
      'beaconDidAppear',
      ({ beacon: newBeacon, region }) => {
        console.log('beaconDidAppear', newBeacon, region);
        this.setState({
          beacons: this.state.beacons.concat(newBeacon)
        });
      }
    );
    DeviceEventEmitter.addListener(
      'beaconDidDisappear',
      ({ beacon: lostBeacon, region }) => {
        console.log('beaconDidDisappear', lostBeacon, region);
        const { beacons } = this.state;
        const index = beacons.findIndex(beacon =>
          this._isIdenticalBeacon(lostBeacon, beacon)
        );
        this.setState({
          beacons: beacons.reduce((result, val, ind) =>
            ind === index ? result : result.push(val), []
          )
        });
      }
    );
    DeviceEventEmitter.addListener(
      'beaconsDidUpdate',
      ({ beacons: updatedBeacons, region }) => {
        const { beacons } = this.state;
        updatedBeacons.forEach(updatedBeacon => {
          const index = beacons.findIndex(beacon =>
            this._isIdenticalBeacon(updatedBeacon, beacon)
          );
          this.setState({
            beacons: beacons.reduce((result, val, ind) =>
              ind === index ? result.push(updatedBeacon) : result.push(val), []
            )
          })
        });
        console.log('beaconsDidUpdate', beacons, region);
      }
    );

    // Add region listeners

    DeviceEventEmitter.addListener(
      'regionDidEnter',
      ({ region }) => {
        console.log('regionDidEnter', region);
      }
    );
    DeviceEventEmitter.addListener(
      'regionDidExit',
      ({ region }) => {
        console.log('regionDidExit', region);
      }
    );

    // Add beacon monitoring listener

    DeviceEventEmitter.addListener(
      'monitoringCycle',
      ({ status }) => {
        console.log('monitoringCycle', status);
      }
    );

  }

  _startScanning = () => {
    startScanning()
      .then(() => this.setState({ scanning: true }))
      .then(() => console.log('started scanning'))
      .catch(error => console.log('[startScanning]', error));
  };
  _stopScanning = () => {
    stopScanning()
      .then(() => this.setState({ scanning: false, beacons: [] }))
      .then(() => console.log('stopped scanning'))
      .catch(error => console.log('[stopScanning]', error));
  };
  _restartScanning = () => {
    restartScanning()
      .then(() => this.setState({ scanning: true }))
      .then(() => console.log('restarted scanning'))
      .catch(error => console.log('[restartScanning]', error));
  };

  _isIdenticalBeacon = (b1, b2) => (
    (b1.identifier === b2.identifier) &&
    (b1.uuid === b2.uuid) &&
    (b1.major === b2.major) &&
    (b1.minor === b2.minor)
  );

  _renderBeacons = () => {
    const colors = ['#F7C376', '#EFF7B7', '#F4CDED', '#A2C8F9', '#AAF7AF'];

    return this.state.beacons.sort((a, b) => (-1 * (a.rssi - b.rssi))).map((beacon, ind) => (
      <View key={ind} style={[styles.beacon, {backgroundColor: colors[beacon.minor - 1]}]}>
        <Text style={{fontWeight: 'bold'}}>{beacon.uniqueId}</Text>
        <Text>Major: {beacon.major}, Minor: {beacon.minor}</Text>
        <Text>Distance: {beacon.accuracy}, Proximity: {beacon.proximity}</Text>
        <Text>Battery Power: {beacon.batteryPower}, TxPower: {beacon.txPower}</Text>
        <Text>FirmwareVersion: {beacon.firmwareVersion}, Address: {beacon.uniqueID}</Text>
      </View>
    ), this);
  };

  _renderEmpty = () => {
    const { scanning, beacons } = this.state;
    let text;
    if (!scanning) text = "Start scanning to listen to beacon signals!";
    if (scanning && !beacons.length) text = "No beacons detected yet...";
    return (
      <View style={styles.textContainer}>
        <Text style={styles.text}>{text}</Text>
      </View>
    );
  };

  _renderButton = (text, onPress) => (
    <TouchableOpacity style={styles.button} onPress={onPress}>
      <Text>{text}</Text>
    </TouchableOpacity>
  );

  render() {
    const { scanning, beacons } = this.state;

    return (
      <View style={styles.container}>
        <View style={styles.buttonContainer}>
          {this._renderButton('Start scan', this._startScanning)}
          {this._renderButton('Stop scan', this._stopScanning)}
          {this._renderButton('Restart scan', this._restartScanning)}
        </View>

        <ScrollView>
          {scanning && beacons.length ? this._renderBeacons() : this._renderEmpty()}
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
  textContainer: {
    alignItems: 'center',
  },
  text: {
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
    backgroundColor: '#84e2f9',
    borderRadius: 10,
  },
});
