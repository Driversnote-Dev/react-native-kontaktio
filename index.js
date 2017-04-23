import {
  NativeModules,
  NativeEventEmitter,
  Platform,
} from 'react-native';

import {
  IBEACON,
  EDDYSTONE,
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
export const configure = (params = null) => (
  KontaktModule.configure(params)
);
export const stopScanning = KontaktModule.stopScanning;
export const restartScanning = KontaktModule.restartScanning;
export const isScanning = KontaktModule.isScanning;


let Kontakt = {};

/**
 * Android
 */
if (Platform.OS === "android") {
  const init = (apiKey = null, beaconTypes = null) => (
    KontaktModule.init(apiKey, beaconTypes)
  );
  const disconnect = KontaktModule.disconnect;
  const isConnected = KontaktModule.isConnected;
  const startScanning = KontaktModule.startScanning;
  const setBeaconRegion = (region = null) => KontaktModule.setBeaconRegion(region);
  const setBeaconRegions = (regionsArray = null) => KontaktModule.setBeaconRegions(regionsArray);

  const DEFAULT_KONTAKT_BEACON_PROXIMITY_UUID = KontaktModule.DEFAULT_KONTAKT_BEACON_PROXIMITY_UUID;
  const DEFAULT_KONTAKT_NAMESPACE_ID = KontaktModule.DEFAULT_KONTAKT_NAMESPACE_ID;
  const ANY_MINOR = KontaktModule.ANY_MINOR;
  const ANY_MAJOR = KontaktModule.ANY_MAJOR;

  Kontakt = {
    init,
    configure,
    disconnect,
    isConnected,
    startScanning,
    stopScanning,
    restartScanning,
    isScanning,
    setBeaconRegion,
    setBeaconRegions,
    // Constants
    IBEACON,
    EDDYSTONE,
    DEFAULT_KONTAKT_BEACON_PROXIMITY_UUID,
    DEFAULT_KONTAKT_NAMESPACE_ID,
    ANY_MAJOR,
    ANY_MINOR,
    ANDRE_CONSTANT,
    // Configurations
    scanMode,
    scanPeriod,
    activityCheckConfiguration,
    forceScanConfiguration,
    monitoringEnabled,
    monitoringSyncInterval,
  };
}

/**
 * iOS
 */
if (Platform.OS === "ios") {

  const init = (apiKey = null) => (
    KontaktModule.init(apiKey)
  );
  const startScanning = (interval = null) => (
    KontaktModule.startScanning(interval)
  );

  const getAuthorizationStatus = KontaktModule.getAuthorizationStatus;
  const requestWhenInUseAuthorization = KontaktModule.requestWhenInUseAuthorization;
  const requestAlwaysAuthorization = KontaktModule.requestAlwaysAuthorization;

  const startRangingBeaconsInRegion = KontaktModule.startRangingBeaconsInRegion;
  const stopRangingBeaconsInRegion = KontaktModule.stopRangingBeaconsInRegion;
  const stopRangingBeaconsInAllRegions = KontaktModule.stopRangingBeaconsInAllRegions;
  const getRangedRegions = KontaktModule.getRangedRegions;

  const startMonitoringForRegion = KontaktModule.startMonitoringForRegion;
  const stopMonitoringForRegion = KontaktModule.stopMonitoringForRegion;
  const stopMonitoringForAllRegions = KontaktModule.stopMonitoringForAllRegions;
  const getMonitoredRegions = KontaktModule.getMonitoredRegions;

  Kontakt = {
    init,
    configure,
    // authorization
    getAuthorizationStatus,
    requestWhenInUseAuthorization,
    requestAlwaysAuthorization,
    // discovery
    startScanning,
    stopScanning,
    restartScanning,
    isScanning,
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
