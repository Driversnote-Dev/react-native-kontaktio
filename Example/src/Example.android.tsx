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
import type { ColorValue } from 'react-native';
import type {
  ConfigType,
  RegionType,
  IBeaconAndroid,
} from 'react-native-kontaktio';

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

const region1: RegionType = {
  identifier: 'Test beacons 1',
  uuid: 'B0702880-A295-A8AB-F734-031A98A512D3',
  major: 1,
  // no minor provided: will detect all minors
};

const region2: RegionType = {
  identifier: 'Test beacons 2',
  uuid: 'B0702880-A295-A8AB-F734-031A98A512D3',
  major: 2,
  // no minor provided: will detect all minors
};

type State = {
  scanning: boolean;
  beacons: Array<IBeaconAndroid>;
  eddystones: Array<IBeaconAndroid>;
  statusText: string | null;
};

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
export default class IBeaconExample extends Component<{}, State> {
  state: State = {
    scanning: false,
    beacons: [],
    eddystones: [],
    statusText: null,
  };

  componentDidMount() {
    // Initialization, configuration and adding of beacon regions
    const config: ConfigType = {
      scanMode: scanMode.BALANCED,
      scanPeriod: scanPeriod.create({
        activePeriod: 6000,
        passivePeriod: 20000,
      }),
      activityCheckConfiguration: activityCheckConfiguration.DEFAULT,
      forceScanConfiguration: forceScanConfiguration.MINIMAL,
      monitoringEnabled: monitoringEnabled.TRUE,
      monitoringSyncInterval: monitoringSyncInterval.DEFAULT,
    };

    connect('MY_KONTAKTIO_API_KEY', [IBEACON, EDDYSTONE])
      .then(() => configure(config))
      .then(() => setBeaconRegions([region1, region2]))
      .then(() => setEddystoneNamespace(null))
      .catch((error) => console.log('error', error));

    // Beacon listeners
    DeviceEventEmitter.addListener(
      'beaconDidAppear',
      ({ beacon: newBeacon, region }) => {
        console.log('beaconDidAppear', newBeacon, region);

        this.setState({
          beacons: this.state.beacons.concat(newBeacon),
        });
      }
    );
    DeviceEventEmitter.addListener(
      'beaconDidDisappear',
      ({ beacon: lostBeacon, region }) => {
        console.log('beaconDidDisappear', lostBeacon, region);

        const { beacons } = this.state;
        const index = beacons.findIndex((beacon) =>
          this._isIdenticalBeacon(lostBeacon, beacon)
        );
        this.setState({
          beacons: beacons.reduce((result: Array<IBeaconAndroid>, val, ind) => {
            // don't add disappeared beacon to array
            if (ind === index) return result;
            // add all other beacons to array
            else {
              result.push(val);
              return result;
            }
          }, []),
        });
      }
    );
    DeviceEventEmitter.addListener(
      'beaconsDidUpdate',
      ({
        beacons: updatedBeacons,
        region,
      }: {
        beacons: Array<IBeaconAndroid>;
        region: RegionType;
      }) => {
        console.log('beaconsDidUpdate', updatedBeacons, region);

        const { beacons } = this.state;
        updatedBeacons.forEach((updatedBeacon) => {
          const index = beacons.findIndex((beacon) =>
            this._isIdenticalBeacon(updatedBeacon, beacon)
          );
          this.setState({
            beacons: beacons.reduce(
              (result: Array<IBeaconAndroid>, val, ind) => {
                // replace current beacon values for updatedBeacon, keep current value for others
                ind === index ? result.push(updatedBeacon) : result.push(val);
                return result;
              },
              []
            ),
          });
        });
      }
    );

    // Region listeners
    DeviceEventEmitter.addListener('regionDidEnter', ({ region }) => {
      console.log('regionDidEnter', region);
    });
    DeviceEventEmitter.addListener('regionDidExit', ({ region }) => {
      console.log('regionDidExit', region);
    });

    // Beacon monitoring listener
    DeviceEventEmitter.addListener('monitoringCycle', ({ status }) => {
      console.log('monitoringCycle', status);
    });

    /*
     * Eddystone
     */

    DeviceEventEmitter.addListener(
      'eddystoneDidAppear',
      ({ eddystone, namespace }) => {
        console.log('eddystoneDidAppear', eddystone, namespace);

        this.setState({
          eddystones: this.state.eddystones.concat(eddystone),
        });
      }
    );

    DeviceEventEmitter.addListener('namespaceDidEnter', ({ status }) => {
      console.log('namespaceDidEnter', status);
    });

    DeviceEventEmitter.addListener('namespaceDidExit', ({ status }) => {
      console.log('namespaceDidExit', status);
    });
  }

  componentWillUnmount() {
    // Disconnect beaconManager and set to it to null
    disconnect();
    DeviceEventEmitter.removeAllListeners();
  }

  _startScanning = () => {
    startScanning()
      .then(() => this.setState({ scanning: true, statusText: null }))
      .then(() => console.log('started scanning'))
      .catch((error) => console.log('[startScanning]', error));
  };
  _stopScanning = () => {
    stopScanning()
      .then(() =>
        this.setState({ scanning: false, beacons: [], statusText: null })
      )
      .then(() => console.log('stopped scanning'))
      .catch((error) => console.log('[stopScanning]', error));
  };
  _restartScanning = () => {
    restartScanning()
      .then(() =>
        this.setState({ scanning: true, beacons: [], statusText: null })
      )
      .then(() => console.log('restarted scanning'))
      .catch((error) => console.log('[restartScanning]', error));
  };
  _isScanning = () => {
    isScanning()
      .then((result) => {
        this.setState({
          statusText: `Device is currently ${result ? '' : 'NOT '}scanning.`,
        });
        console.log('Is device scanning?', result);
      })
      .catch((error) => console.log('[isScanning]', error));
  };
  _isConnected = () => {
    isConnected()
      .then((result) => {
        this.setState({
          statusText: `Device is ${result ? '' : 'NOT '}ready to scan beacons.`,
        });
        console.log('Is device connected?', result);
      })
      .catch((error) => console.log('[isConnected]', error));
  };
  _getBeaconRegions = () => {
    getBeaconRegions()
      .then((regions) => console.log('regions', regions))
      .catch((error) => console.log('[getBeaconRegions]', error));
  };

  /**
   * Helper function used to identify equal beacons
   */
  _isIdenticalBeacon = (b1: IBeaconAndroid, b2: IBeaconAndroid) =>
    b1.major === b2.major && b1.minor === b2.minor;

  _renderBeacons = () => {
    const colors = ['#F7C376', '#EFF7B7', '#F4CDED', '#A2C8F9', '#AAF7AF'];

    return this.state.beacons
      .sort(
        (a: IBeaconAndroid, b: IBeaconAndroid) =>
          parseInt(a.accuracy) - parseInt(b.accuracy)
      )
      .map(
        (beacon, ind) => (
          <View
            style={[
              styles.beacon,
              { backgroundColor: colors[beacon.minor - 1] },
            ]}
          >
            <Text style={{ fontWeight: 'bold' }}>{beacon.uniqueId}</Text>
            <Text>
              Major: {beacon.major}, Minor: {beacon.minor}
            </Text>
            <Text>
              Distance: {beacon.accuracy}, Proximity: {beacon.proximity}
            </Text>
            <Text>
              Battery Power: {beacon.batteryPower}, TxPower: {beacon.txPower}
            </Text>
            <Text>
              FirmwareVersion: {beacon.firmwareVersion}, Address:{' '}
              {beacon.uniqueId}
            </Text>
          </View>
        ),
        this
      );
  };

  _renderEmpty = () => {
    const { scanning, beacons } = this.state;
    let text;
    if (!scanning) text = 'Start scanning to listen for beacon signals!';
    if (scanning && !beacons.length) text = 'No beacons detected yet...';
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

  _renderButton = (
    text: string,
    onPress: () => void,
    backgroundColor: ColorValue
  ) => (
    <TouchableOpacity
      style={[styles.button, { backgroundColor }]}
      onPress={onPress}
    >
      <Text>{text}</Text>
    </TouchableOpacity>
  );

  render() {
    const { scanning, beacons } = this.state;

    return (
      <View style={styles.container}>
        <View style={styles.buttonContainer}>
          {this._renderButton('Start scan', this._startScanning, '#84e2f9')}
          {this._renderButton('Stop scan', this._stopScanning, '#84e2f9')}
          {this._renderButton('Restart scan', this._restartScanning, '#84e2f9')}
        </View>
        <View style={styles.buttonContainer}>
          {this._renderButton('Is scanning?', this._isScanning, '#f2a2a2')}
          {this._renderButton('Is connected?', this._isConnected, '#f2a2a2')}
        </View>
        <View style={styles.buttonContainer}>
          {this._renderButton(
            'Beacon regions (log)',
            this._getBeaconRegions,
            '#F4ED5A'
          )}
        </View>
        {this._renderStatusText()}
        <ScrollView>
          {scanning && beacons.length
            ? this._renderBeacons()
            : this._renderEmpty()}
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
