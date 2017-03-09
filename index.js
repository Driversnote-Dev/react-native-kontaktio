import { NativeModules } from 'react-native';
import {
  IBEACON,
  EDDYSTONE,
  ScanMode,
  ScanPeriod,
  ActivityCheckConfiguration,
} from './configurations';

// If the native module (i.e. Java module) is prefixed with "RCT", 
// the NativeModules name does not include "RCT".
// NB: Kontakt is not declared as default export because e.g. init wouldn't allow for less arguments
const Kontakt = NativeModules.KontaktBeacons;

const init = (apiKey = null, beaconTypes = null) => (
  Kontakt.init(apiKey, beaconTypes)
);
const configure = Kontakt.configure;
const startScanning = Kontakt.startScanning;
const stopScanning = Kontakt.stopScanning;
const restartScanning = Kontakt.restartScanning;
const disconnect = Kontakt.disconnect;
const setBeaconRegion = (region = null) => Kontakt.setBeaconRegion(region);
const setBeaconRegions = (regionsArray = null) => Kontakt.setBeaconRegions(regionsArray);

const DEFAULT_KONTAKT_BEACON_PROXIMITY_UUID = Kontakt.DEFAULT_KONTAKT_BEACON_PROXIMITY_UUID;
const DEFAULT_KONTAKT_NAMESPACE_ID = Kontakt.DEFAULT_KONTAKT_NAMESPACE_ID;
const ANY_MINOR = Kontakt.ANY_MINOR;
const ANY_MAJOR = Kontakt.ANY_MAJOR;

export {
  init,
  configure,
  disconnect,
  startScanning,
  stopScanning,
  restartScanning,
  setBeaconRegion,
  setBeaconRegions,
  // Constants
  IBEACON,
  EDDYSTONE,
  DEFAULT_KONTAKT_BEACON_PROXIMITY_UUID,
  DEFAULT_KONTAKT_NAMESPACE_ID,
  ANY_MAJOR,
  ANY_MINOR,
  // configurations
  ScanMode,
  ScanPeriod,
  ActivityCheckConfiguration,
}
