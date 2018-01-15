import React, { Component } from 'react';
import {
  StyleSheet,
  Text,
  View,
  DeviceEventEmitter,
  ScrollView,
  TouchableOpacity,
} from 'react-native';

import Kontakt from 'react-native-kontaktio';

const {
  connect,
  configure,
  disconnect,
  isConnected,
  startScanning,
  stopScanning,
  restartScanning,
  isScanning,
  // setBeaconRegion,
  setBeaconRegions,
  getBeaconRegions,
  setEddystoneNamespace,
  IBEACON,
  EDDYSTONE,
  // Configurations
  scanMode,
  scanPeriod,
  activityCheckConfiguration,
  forceScanConfiguration,
  monitoringEnabled,
  monitoringSyncInterval,
} = Kontakt;

let TfLNamespace = '953e1199a959b67221bd'
let TfLBeacon1 = 'fc8e38ee0e8a'
let TfLBeacon2 = 'fbe12d00add2'
var numberOfTfLBeacons = 0

//const region1 = {
//  identifier: 'Test beacons 1',
//  uuid: 'B0702880-A295-A8AB-F734-031A98A512D3',
//  major: 1,
//  // no minor provided: will detect all minors
//};
//
//const region2 = {
//  identifier: 'Test beacons 2',
//  uuid: 'B0702880-A295-A8AB-F734-031A98A512D3',
//  major: 2,
//  // no minor provided: will detect all minors
//};

/**
 * Monitors beacons in two regions and sorts them by proximity,
 * color-coded by minors with values 1 through 5.
 *
 * Just change the values in the regions to work with your beacons.
 * Then press `Start scanning` and you should very soon see your beacons
 * in a ScrollView sorted by their 'accuracy' which reflects a measure of
 * distance from the beacons to your mobile phone in meters.
 *
 * This example makes use of regions to limit scanning to beacons
 * belonging to one of these two regions.
 * Of course regions can also be used to separately process the data later.
 * Such logic may be built inside the listeners.
 *
 * Press `Start scanning` and you should very soon see your beacons in a ScrollView
 * sorted by their RSSI which reflects a measure of distance from the beacons
 * to your mobile phone.
 */
export default class IBeaconExample extends Component {
  state = {
    scanning: false,
    beacons: [],
    eddystones: [],
    statusText: null,
  };

  componentDidMount() {
    // Initialization, configuration and adding of beacon regions
    connect(
      'MY_KONTAKTIO_API_KEY',
      [IBEACON, EDDYSTONE],
    )
      .then(() => configure({
        scanMode: scanMode.BALANCED,

            // Set Scan Period
//        scanPeriod: scanPeriod.create({
//          activePeriod: 6000,
//          passivePeriod: 20000,
//        }),
        scanPeriod: scanPeriod.RANGING,
        activityCheckConfiguration: activityCheckConfiguration.DEFAULT,
        forceScanConfiguration: forceScanConfiguration.MINIMAL,
        monitoringEnabled: monitoringEnabled.TRUE,
        monitoringSyncInterval: monitoringSyncInterval.DEFAULT,
      }))
      .then(() => setBeaconRegions([region1, region2]))
      .then(() => setEddystoneNamespace())
      .catch(error => console.log('error', error));

//    // Beacon listeners
//    DeviceEventEmitter.addListener(
//      'beaconDidAppear',
//      ({ beacon: newBeacon, region }) => {
//        console.log('beaconDidAppear', newBeacon, region);
//
//        this.setState({
//          beacons: this.state.beacons.concat(newBeacon)
//        });
//      }
//    );
//    DeviceEventEmitter.addListener(
//      'beaconDidDisappear',
//      ({ beacon: lostBeacon, region }) => {
//        console.log('beaconDidDisappear', lostBeacon, region);
//
//        const { beacons } = this.state;
//        const index = beacons.findIndex(beacon =>
//          this._isIdenticalBeacon(lostBeacon, beacon)
//        );
//        this.setState({
//          beacons: beacons.reduce((result, val, ind) => {
//            // don't add disappeared beacon to array
//            if (ind === index) return result;
//            // add all other beacons to array
//            else {
//              result.push(val);
//              return result;
//            }
//          }, [])
//        });
//      }
//    );
//    DeviceEventEmitter.addListener(
//      'beaconsDidUpdate',
//      ({ beacons: updatedBeacons, region }) => {
//        console.log('beaconsDidUpdate', updatedBeacons, region);
//
//        const { beacons } = this.state;
//        updatedBeacons.forEach(updatedBeacon => {
//          const index = beacons.findIndex(beacon =>
//            this._isIdenticalBeacon(updatedBeacon, beacon)
//          );
//          this.setState({
//            beacons: beacons.reduce((result, val, ind) => {
//              // replace current beacon values for updatedBeacon, keep current value for others
//              ind === index ? result.push(updatedBeacon) : result.push(val);
//              return result;
//            }, [])
//          })
//        });
//      }
//    );
//
//    // Region listeners
//    DeviceEventEmitter.addListener(
//      'regionDidEnter',
//      ({ region }) => {
//        console.log('regionDidEnter', region);
//      }
//    );
//    DeviceEventEmitter.addListener(
//      'regionDidExit',
//      ({ region }) => {
//        console.log('regionDidExit', region);
//      }
//    );

    // Beacon monitoring listener
    DeviceEventEmitter.addListener(
      'monitoringCycle',
      ({ status }) => {
        console.log('monitoringCycle', status);
      }
    );

    /*
     * Eddystone
     */

    DeviceEventEmitter.addListener(
      'eddystoneDidAppear',
      ({ eddystone, namespace }) => {
        console.log('eddystoneDidAppear', eddystone.namespace, eddystone.instanceId, eddystone, namespace);


        if ( eddystone.instanceId == TfLBeacon1 ){
        this.setState({ statusText: "TfLBeacon1 " + eddystone.proximity + " instanceId: " + eddystone.instanceId });
        console.log('TfLBeacon1')
        }

        if ( eddystone.instanceId == TfLBeacon2 ){
        this.setState({ statusText2: "Found TfLBeacon2 " + "instanceId: " + eddystone.instanceId });
        console.log('TfLBeacon2')
        }

        if ( eddystone.namespace == TfLNamespace ){
        this.setState({ numberOfTfLBeacons: "Found " + numberOfTfLBeacons + " TfL Beacons" });
            numberOfTfLBeacons++
            console.log(numberOfTfLBeacons)
        };


        this.setState({
          eddystones: this.state.eddystones.concat(eddystone)
        });
      }
    );

    DeviceEventEmitter.addListener(
      'namespaceDidEnter',
      ({ status }) => {
        console.log('namespaceDidEnter', status);
      }
    );

    DeviceEventEmitter.addListener(
      'namespaceDidExit',
      ({ status }) => {
        console.log('namespaceDidExit', status);
      }
    );

  DeviceEventEmitter.addListener(
        'eddystonesDidUpdate',
        ({ status }) => {
          console.log('eddystonesDidUpdate', status);
        }
      );

  }

  componentWillUnmount() {
    // Disconnect beaconManager and set to it to null
    disconnect();
    DeviceEventEmitter.removeAllListeners();
  }

  _startScanning = () => {
    startScanning()
      .then(() => this.setState({ scanning: true, statusText: null, statusText2: null }))
      .then(() => console.log('started scanning'))
      // Reset beacon count to 0
      .then(() => numberOfTfLBeacons = 0)
      .catch(error => console.log('[startScanning]', error));
  };

  _stopScanning = () => {
    stopScanning()
      .then(() => this.setState({ scanning: false, beacons: [], statusText: null, statusText2: null}))
      .then(() => console.log('stopped scanning'))
      .catch(error => console.log('[stopScanning]', error));
  };

  _restartScanning = () => {
    restartScanning()
      .then(() => this.setState({ scanning: true, beacons: [], statusText: null, statusText2: null }))
      .then(() => console.log('restarted scanning'))
      .catch(error => console.log('[restartScanning]', error));
  };

  _isScanning = () => {
    isScanning()
      .then(result => {
        this.setState({ statusText: `Device is currently ${result ? '' : 'NOT '}scanning.` });
        console.log('Is device scanning?', result);
      })
      .catch(error => console.log('[isScanning]', error));
  };
  _isConnected = () => {
    isConnected()
      .then(result => {
        this.setState({ statusText: `Device is ${result ? '' : 'NOT '}ready to scan beacons.` });
        console.log('Is device connected?', result);
      })
      .catch(error => console.log('[isConnected]', error));
  };
  _getBeaconRegions = () => {
    getBeaconRegions()
      .then(regions => console.log('regions', regions))
      .catch(error => console.log('[getBeaconRegions]', error));
  };

  /**
   * Helper function used to identify equal beacons
   */
  _isIdenticalBeacon = (b1, b2) => (
    (b1.identifier === b2.identifier) &&
    (b1.uuid === b2.uuid) &&
    (b1.major === b2.major) &&
    (b1.minor === b2.minor)
  );

  _renderBeacons = () => {
    const colors = ['#F7C376', '#EFF7B7', '#F4CDED', '#A2C8F9', '#AAF7AF'];

    return this.state.beacons.sort((a, b) => a.accuracy - b.accuracy).map((beacon, ind) => (

      <View key={ind} style={[styles.beacon, {backgroundColor: colors[beacon.minor - 1]}]}>

        <Text style={{fontWeight: 'bold'}}>{beacon.uniqueId}</Text>
        <Text>Major: {beacon.major}, Minor: {beacon.minor}</Text>
        <Text>Distance: {beacon.accuracy}, Proximity: {beacon.proximity}</Text>
        <Text>Battery Power: {beacon.batteryPower}, TxPower: {beacon.txPower}</Text>
        <Text>FirmwareVersion: {beacon.firmwareVersion}, Address: {beacon.uniqueId}</Text>

      </View>
    ), this);
  };

  _renderEddystones = () => {
      const colors = ['#F7C376', '#EFF7B7', '#F4CDED', '#A2C8F9', '#AAF7AF'];

      return this.state.eddystones.sort((a, b) => a.accuracy - b.accuracy).map((eddystone, ind) => (

        <View key={ind} style={[styles.beacon, {backgroundColor: '#AAF7AF'}]}>
          <Text style={{fontWeight: 'bold'}}>{eddystone.instanceId}</Text>
        </View>
      ), this);
    };

  _renderEmpty = () => {
    const { scanning, beacons } = this.state;
    let text;
    if (!scanning) text = "Start scanning to listen for beacon signals!";
    if (scanning && !beacons.length) text = "No beacons detected yet...";
    return (
      <View style={styles.textContainer}>
        <Text style={styles.text}>{text}</Text>
      </View>
    );
  };

  _renderStatusText = () => {
    const { statusText } = this.state;
    return statusText ? (
      <View style={styles.textContainer}>
        <Text style={[styles.text, { color: 'red' }]}>{statusText}</Text>
      </View>
    ) : null;
  };

    _renderStatusText2 = () => {
      const { statusText2 } = this.state;
      return statusText2 ? (
        <View style={styles.textContainer}>
          <Text style={[styles.text, { color: 'red' }]}>{statusText2}</Text>
        </View>
      ) : null;
    };

    _renderBeaconCountText = () => {
      const { numberOfTfLBeacons } = this.state;
      return numberOfTfLBeacons ? (
        <View style={styles.textContainer}>
          <Text style={[styles.text, { color: 'red' }]}>{ numberOfTfLBeacons }</Text>
        </View>
      ) : null;
    };

  _renderButton = (text, onPress, backgroundColor) => (
    <TouchableOpacity style={[styles.button, { backgroundColor }]} onPress={onPress}>
      <Text>{text}</Text>
    </TouchableOpacity>
  );

  _renderClosestBeacon = () => {



  };

  render() {
    const { scanning, beacons } = this.state;

    return (
      <View style={styles.container}>
        <View style={styles.buttonContainer}>
          {this._renderButton('Start scan', this._startScanning, '#84e2f9')}
          {this._renderButton('Stop scan', this._stopScanning, '#84e2f9')}
          {this._renderButton('Restart scan', this._restartScanning, '#84e2f9')}
        </View>
        {this._renderStatusText()}
        {this._renderStatusText2()}
        <ScrollView>
          {this._renderBeaconCountText()}
          {scanning && beacons.length ? this._renderBeacons() : this._renderEmpty()}
          {this._renderEddystones()}
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
    borderRadius: 10,
  },
});
