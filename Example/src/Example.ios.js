import React, { Component } from 'react';
import {
  StyleSheet,
  Text,
  View,
  NativeEventEmitter,
  ScrollView,
  TouchableOpacity,
} from 'react-native';

import Kontakt, { KontaktModule } from 'react-native-kontaktio';

// const {
//   startScanning,
//   stopScanning,
//   restartScanning,
// } = Kontakt;

const kontaktEmitter = new NativeEventEmitter(KontaktModule);

const region1 = {
  identifier: 'Test beacons 1',
  uuid: 'B0702880-A295-A8AB-F734-031A98A512DE',
  major: 1,
  // no minor provided: will detect all minors
};

const region2 = {
  identifier: 'Test beacons 2',
  uuid: 'B0702880-A295-A8AB-F734-031A98A512DE',
  major: 2,
  // no minor provided: will detect all minors
};

export default class IBeaconExample extends Component {
  state = {
    scanning: false,
    ranging: false,
    monitoring: false,
    discoveredBeacons: [],
    rangedBeacons: [],
    authorizationStatus: '',
  };

  regionEnterSubscription = null;
  regionExitSubscription = null;
  regionRangeSubscription = null;
  authorizationSubscription = null;
  discoverSubscription = null;
  startMonitoringSubscription = null;

  componentDidMount() {
    // Initialization, configuration and adding of beacon regions
    KontaktModule.init('MY_KONTAKTIO_API_KEY')
      .then(() => KontaktModule.configure({
        dropEmptyRanges: true,    // don't trigger beacon events in case beacon array is empty
        connectNearbyBeacons: false,   // true not working yet
        invalidationAge: 5000,   // time to forget lost beacon
      }))
      .then(() => KontaktModule.requestAlwaysAuthorization())
      .then(() => console.log('Successfully initialized beacon ranging, monitoring and scanning'))
      .catch(error => console.log('error', error));

    // Monitoring events
    this.startMonitoringSubscription = kontaktEmitter.addListener(
      'didStartMonitoringForRegion',
      ({ region }) => {
        console.log('didStartMonitoringForRegion', region);
      }
    );
    this.regionEnterSubscription = kontaktEmitter.addListener(
      'didEnterRegion',
      ({ region }) => {
        console.log('didEnterRegion', region);
      }
    );
    this.regionExitSubscription = kontaktEmitter.addListener(
      'didExitRegion',
      ({ region }) => {
        console.log('didExitRegion', region);
      }
    );
    // Ranging event
    this.regionRangeSubscription = kontaktEmitter.addListener(
      'didRangeBeacons',
      ({ beacons: rangedBeacons, region }) => {
        console.log('didRangeBeacons', rangedBeacons, region);
        this.setState({ rangedBeacons });
      }
    );
    // Authorization event
    this.authorizationSubscription = kontaktEmitter.addListener(
      'authorizationStatusDidChange',
      ({ status }) => {
        console.log('authorizationStatusDidChange', status);
        this.setState({ authorizationStatus: status });
      }
    );
    // Discovery event
    this.discoverSubscription = kontaktEmitter.addListener(
      'didDiscoverDevices',
      ({ beacons: discoveredBeacons }) => {
        console.log('didDiscoverDevices', discoveredBeacons);
        this.setState({ discoveredBeacons });
      }
    );
  }

  componentWillUnmount() {
    this.startMonitoringSubscription.remove();
    this.regionEnterSubscription.remove();
    this.regionExitSubscription.remove();
    this.regionRangeSubscription.remove();
    this.authorizationSubscription.remove();
    this.discoverSubscription.remove();
  }

  /* --- Discovering beacons --- */

  _startScanning = () => {
    KontaktModule.startScanning({ interval: 1000 })
      .then(() => this.setState({ scanning: true, discoveredBeacons: [] }))
      .then(() => console.log('started scanning'))
      .catch(error => console.log('[startScanning]', error));
  };
  _stopScanning = () => {
    KontaktModule.stopScanning()
      .then(() => this.setState({ scanning: false, discoveredBeacons: [] }))
      .then(() => console.log('stopped scanning'))
      .catch(error => console.log('[stopScanning]', error));
  };
  _restartScanning = () => {
    KontaktModule.restartScanning()
      .then(() => this.setState({ scanning: true, discoveredBeacons: [] }))
      .then(() => console.log('restarted scanning'))
      .catch(error => console.log('[restartScanning]', error));
  };

  /* --- Ranging beacons --- */

  _startRanging = () => {
    KontaktModule.startRangingBeaconsInRegion(region1)
      .then(() => this.setState({ ranging: true, rangedBeacons: [] }))
      .then(() => console.log('started ranging'))
      .catch(error => console.log('[startRanging]', error));
  };
  _stopRanging = () => {
    KontaktModule.stopRangingBeaconsInRegion(region1)
      .then(() => this.setState({ ranging: false, rangedBeacons: [] }))
      .then(() => console.log('stopped ranging'))
      .catch(error => console.log('[stopRanging]', error));
  };
  _stopAllRanging = () => {
    KontaktModule.stopRangingBeaconsInAllRegions()
      .then(() => this.setState({ ranging: false, rangedBeacons: [] }))
      .then(() => console.log('stopped ranging in all regions'))
      .catch(error => console.log('[stopAllRanging]', error));
  };

  /* --- Monitoring beacons --- */

  _startMonitoring = () => {
    KontaktModule.startMonitoringForRegion(region1)
      .then(() => this.setState({ monitoring: true }))
      .then(() => console.log('started monitoring'))
      .catch(error => console.log('[startMonitoring]', error));
  };
  _stopMonitoring = () => {
    KontaktModule.stopMonitoringForRegion(region1)
      .then(() => this.setState({ monitoring: false }))
      .then(() => console.log('stopped monitoring'))
      .catch(error => console.log('[stopRanging]', error));
  };
  _stopAllMonitoring = () => {
    KontaktModule.stopMonitoringForAllRegions()
      .then(() => this.setState({ monitoring: false }))
      .then(() => console.log('stopped monitoring in all regions'))
      .catch(error => console.log('[stopAllMonitoring]', error));
  };

  /* --- Authorization --- */
  // TODO: Add authorization methods
  /* --- Regions --- */
  // TODO: Add getters for ranged/monitored regions

  _renderDiscoveredBeacons = () => {
    const colors = ['#F7C376', '#EFF7B7', '#F4CDED', '#A2C8F9', '#AAF7AF'];

    return this.state.discoveredBeacons.sort((a, b) => a.accuracy - b.accuracy).map((beacon, ind) => (
      <View key={ind} style={[styles.beacon, {backgroundColor: colors[beacon.minor - 1]}]}>
        <Text style={{fontWeight: 'bold'}}>{beacon.uniqueId}</Text>
        <Text>Locked: {beacon.locked ? 'Yes' : 'No'}, Shuffled: {beacon.shuffled ? 'Yes' : 'No'}</Text>
        <Text>Battery Power: {beacon.batteryLevel}, TxPower: {beacon.transmissionPower}</Text>
        <Text>Model: {beacon.model}, RSSI: {beacon.rssi}</Text>
        <Text>FirmwareVersion: {beacon.firmwareVersion}, Name: {beacon.name}</Text>
        <Text>updatedAt: {beacon.updatedAt}</Text>
      </View>
    ), this);
  };

  _renderRangedBeacons = () => {
    const colors = ['#F7C376', '#EFF7B7', '#F4CDED', '#A2C8F9', '#AAF7AF'];

    return this.state.rangedBeacons.sort((a, b) => a.accuracy - b.accuracy).map((beacon, ind) => (
      <View key={ind} style={[styles.beacon, {backgroundColor: colors[beacon.minor - 1]}]}>
        <Text style={{fontWeight: 'bold'}}>{beacon.uuid}</Text>
        <Text>Major: {beacon.major}, Minor: {beacon.minor}</Text>
        <Text>RSSI: {beacon.rssi}, Proximity: {beacon.proximity}</Text>
        <Text>Distance: {beacon.accuracy}</Text>
      </View>
    ), this);
  };

  _renderEmpty = () => {
    const { scanning, ranging, monitoring, discoveredBeacons, rangedBeacons } = this.state;
    let text = '';
    if (!scanning && !ranging && !monitoring) text = "Start scanning to listen for beacon signals!";
    if (scanning && !discoveredBeacons.length) text = "No beacons discovered yet...";
    if (ranging && !rangedBeacons.length) text = "No beacons ranged yet...";
    return text ? (
      <View style={styles.textContainer}>
        <Text style={styles.text}>{text}</Text>
      </View>) : null;
  };

  _renderAuthorizationStatusText = () => {
    const { authorizationStatus } = this.state;
    return authorizationStatus ? (
        <View style={styles.textContainer}>
          <Text style={[styles.text, { color: 'red' }]}>{authorizationStatus}</Text>
        </View>
      ) : null;
  };

  _renderButton = (text, onPress, backgroundColor) => (
    <TouchableOpacity style={[styles.button, { backgroundColor }]} onPress={onPress}>
      <Text>{text}</Text>
    </TouchableOpacity>
  );

  render() {
    const { scanning, ranging, discoveredBeacons, rangedBeacons } = this.state;

    return (
      <View style={styles.container}>
        <View style={styles.buttonContainer}>
          {this._renderButton('Start scan', this._startScanning, '#84e2f9')}
          {this._renderButton('Stop scan', this._stopScanning, '#84e2f9')}
          {this._renderButton('Restart scan', this._restartScanning, '#84e2f9')}
        </View>
        <View style={styles.buttonContainer}>
          {this._renderButton('Start ranging', this._startRanging, '#ABE88D')}
          {this._renderButton('Stop', this._stopRanging, '#ABE88D')}
          {this._renderButton('Stop all', this._stopAllRanging, '#ABE88D')}
        </View>
        <View style={styles.buttonContainer}>
          {this._renderButton('Start monitoring', this._startMonitoring, '#F48661')}
          {this._renderButton('Stop', this._stopMonitoring, '#F48661')}
          {this._renderButton('Stop all', this._stopAllMonitoring, '#F48661')}
        </View>
        {this._renderAuthorizationStatusText()}
        <ScrollView>
          {this._renderEmpty()}
          {(scanning && discoveredBeacons.length) && this._renderDiscoveredBeacons()}
          {(ranging && rangedBeacons.length) && this._renderRangedBeacons()}
        </ScrollView>
      </View>
    );
  }
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    marginTop: 20, // statusbarHeight
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
    marginVertical: 10,
    flexDirection: 'row',
    alignItems: 'center',
    justifyContent: 'space-around',
  },
  button: {
    padding: 10,
    borderRadius: 10,
  },
});
