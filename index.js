import { NativeModules } from 'react-native';
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
const KontaktModule = NativeModules.KontaktBeacons;

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

export default Kontakt = {
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
  // Configurations
  scanMode,
  scanPeriod,
  activityCheckConfiguration,
  forceScanConfiguration,
  monitoringEnabled,
  monitoringSyncInterval,
};

export {
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
  // Configurations
  scanMode,
  scanPeriod,
  activityCheckConfiguration,
  forceScanConfiguration,
  monitoringEnabled,
  monitoringSyncInterval,
}
