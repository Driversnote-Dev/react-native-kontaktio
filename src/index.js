// @flow

// $FlowFixMe  - react-native is a peer-dependency and therefore not in node_modules folder.
import { NativeModules, Platform } from 'react-native';

import type {
  RegionAndroid,
  RegionIos,
  NamespaceAndroid,
  ConfigurationAndroid,
  ConfigurationIos,
} from './types';

import {
  IBEACON,
  EDDYSTONE,
  SECURE_PROFILE,
  scanMode,
  scanPeriod,
  activityCheckConfiguration,
  forceScanConfiguration,
  monitoringEnabled,
  monitoringSyncInterval,
} from './configurations';


// If the native module (i.e. Java module) is prefixed with "RCT",
// the NativeModules name does not include "RCT".
export const KontaktModule = NativeModules.KontaktBeacons;

/**
 * Methods shared in android and iOS
 */

// eslint-disable-next-line import/no-mutable-exports
let Kontakt = {};

/**
 * Android
 */
type BeaconTypes = typeof IBEACON | typeof EDDYSTONE | typeof SECURE_PROFILE;

if (Platform.OS === 'android') {
  const connect = (apiKey: ?string = null, beaconTypes: ?Array<BeaconTypes> = null) =>
    KontaktModule.connect(
      apiKey,
      beaconTypes,
    );
  /**
   * @deprecated
   * 'init' was renamed to 'connect' - please use 'connect'
   */
  const init = (apiKey: ?string = null, beaconTypes: ?Array<BeaconTypes> = null) =>
    KontaktModule.connect(
      apiKey,
      beaconTypes,
    );

  const configure = (params?: ?ConfigurationAndroid = null) => KontaktModule.configure(params);

  const {
    disconnect,
    isConnected,
    startScanning,
    stopScanning,
    restartScanning,
    isScanning,
    getBeaconRegions,
    DEFAULT_KONTAKT_BEACON_PROXIMITY_UUID,
    DEFAULT_KONTAKT_NAMESPACE_ID,
    ANY_MINOR,
    ANY_MAJOR,
  } = KontaktModule;

  const setBeaconRegion = (region: ?RegionAndroid = null) => KontaktModule.setBeaconRegion(region);
  const setBeaconRegions = (regionsArray: ?Array<RegionAndroid> = null) => KontaktModule.setBeaconRegions(regionsArray);

  const setEddystoneNamespace = (namespace: ?NamespaceAndroid = null) =>
    KontaktModule.setEddystoneNamespace(namespace);

  Kontakt = {
    connect,
    configure,
    disconnect,
    isConnected,
    startScanning,
    stopScanning,
    restartScanning,
    isScanning,
    setBeaconRegion,
    setBeaconRegions,
    getBeaconRegions,
    setEddystoneNamespace,
    // Constants
    IBEACON,
    EDDYSTONE,
    SECURE_PROFILE,
    DEFAULT_KONTAKT_BEACON_PROXIMITY_UUID,
    DEFAULT_KONTAKT_NAMESPACE_ID,
    ANY_MAJOR,
    ANY_MINOR,
    // Configurations
    scanMode,
    scanPeriod,
    activityCheckConfiguration,
    forceScanConfiguration,
    monitoringEnabled,
    monitoringSyncInterval,
    init, // @deprecated
  };
}

/**
 * iOS
 */
type IntervalSetting = { interval: number };

if (Platform.OS === 'ios') {
  const init = (apiKey: ?string = null) => KontaktModule.init(apiKey);
  const startDiscovery = (interval: ?IntervalSetting = null) => KontaktModule.startDiscovery(interval);

  const configure = (params?: ?ConfigurationIos = null) => KontaktModule.configure(params);

  const {
    stopDiscovery,
    restartDiscovery,
    isDiscovering,
    getAuthorizationStatus,
    requestWhenInUseAuthorization,
    requestAlwaysAuthorization,
    startRangingBeaconsInRegion,
    stopRangingBeaconsInRegion,
    stopRangingBeaconsInAllRegions,
    getRangedRegions,
    startMonitoringForRegion,
    stopMonitoringForRegion,
    stopMonitoringForAllRegions,
    getMonitoredRegions,
  } = KontaktModule;

  Kontakt = {
    init,
    configure,
    // authorization
    getAuthorizationStatus,
    requestWhenInUseAuthorization,
    requestAlwaysAuthorization,
    // discovery
    startDiscovery,
    stopDiscovery,
    restartDiscovery,
    isDiscovering,
    // ranging
    startRangingBeaconsInRegion,
    stopRangingBeaconsInRegion,
    stopRangingBeaconsInAllRegions,
    getRangedRegions,
    // monitoring
    startMonitoringForRegion,
    stopMonitoringForRegion,
    stopMonitoringForAllRegions,
    getMonitoredRegions,
  };
}

export default Kontakt;
