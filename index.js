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

let Kontakt = {};

if (Platform.OS === "android") {
  const init = (apiKey = null, beaconTypes = null) => (
    KontaktModule.init(apiKey, beaconTypes)
  );
  const configure = KontaktModule.configure;
  const startScanning = KontaktModule.startScanning;
  const stopScanning = KontaktModule.stopScanning;
  const restartScanning = KontaktModule.restartScanning;
  const isScanning = KontaktModule.isScanning;
  const disconnect = KontaktModule.disconnect;
  const isConnected = KontaktModule.isConnected;
  const setBeaconRegion = (region = null) => KontaktModule.setBeaconRegion(region);
  const setBeaconRegions = (regionsArray = null) => KontaktModule.setBeaconRegions(regionsArray);

  const DEFAULT_KONTAKT_BEACON_PROXIMITY_UUID = KontaktModule.DEFAULT_KONTAKT_BEACON_PROXIMITY_UUID;
  const DEFAULT_KONTAKT_NAMESPACE_ID = KontaktModule.DEFAULT_KONTAKT_NAMESPACE_ID;
  const ANY_MINOR = KontaktModule.ANY_MINOR;
  const ANY_MAJOR = KontaktModule.ANY_MAJOR;

  const ANDRE_CONSTANT = KontaktModule.ANDRE_CONSTANT;

  Kontakt = {
    init,
    KontaktModule,
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

if (Platform.OS === "ios") {

  // const initBeacons = KontaktModule.initBeacons;
  const test = KontaktModule.test;

  const ANDRE_CONSTANT = KontaktModule.ANDRE_CONSTANT;

  Kontakt = {
    test,
    ANDRE_CONSTANT,
  };
}

export default Kontakt;
