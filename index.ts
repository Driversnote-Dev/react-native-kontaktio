import { NativeModules, Platform } from "react-native";

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
} from "./configurations";
import type { KontaktType, ConfigType, BeaconType, RegionType } from "./types";

// If the native module (i.e. Java module) is prefixed with "RCT",
// the NativeModules name does not include "RCT".
export const KontaktModule = NativeModules.KontaktBeacons;

/**
 * Methods shared in android and iOS
 */
export const configure = (
  /**
   * beacon scanning configuration
   */
  params: ConfigType | undefined | null = null
): Promise<void> => KontaktModule.configure(params);

let Kontakt = {};

/**
 * Android
 */
if (Platform.OS === "android") {
  const connect = (
    apiKey: string | undefined | null = null,
    beaconTypes: Array<BeaconType> | undefined | null = null
  ): Promise<void> => KontaktModule.connect(apiKey, beaconTypes);

  /**
   * @deprecated
   * 'init' was renamed to 'connect' - please use 'connect'
   */
  const init = (
    apiKey: string | undefined | null = null,
    beaconTypes: Array<BeaconType> | undefined | null = null
  ): Promise<void> => KontaktModule.connect(apiKey, beaconTypes);

  const disconnect: () => Promise<void> = KontaktModule.disconnect;
  const isConnected: () => Promise<boolean> = KontaktModule.isConnected;

  const startScanning: () => Promise<void> = KontaktModule.startScanning;
  const stopScanning: () => Promise<void> = KontaktModule.stopScanning;
  const restartScanning: () => Promise<void> = KontaktModule.restartScanning;
  const isScanning: () => Promise<boolean> = KontaktModule.isScanning;

  const setBeaconRegion = (region: RegionType | null = null): void =>
    KontaktModule.setBeaconRegion(region);
  const setBeaconRegions = (
    regionsArray: Array<RegionType> | undefined | null = null
  ): void => KontaktModule.setBeaconRegions(regionsArray);
  const getBeaconRegions: () => Promise<Array<RegionType>> =
    KontaktModule.getBeaconRegions;

  const setEddystoneNamespace = (namespace: any) =>
    KontaktModule.setEddystoneNamespace(namespace);

  const DEFAULT_KONTAKT_BEACON_PROXIMITY_UUID: string =
    KontaktModule.DEFAULT_KONTAKT_BEACON_PROXIMITY_UUID;
  const DEFAULT_KONTAKT_NAMESPACE_ID: string =
    KontaktModule.DEFAULT_KONTAKT_NAMESPACE_ID;
  const ANY_MINOR: number = KontaktModule.ANY_MINOR;
  const ANY_MAJOR: number = KontaktModule.ANY_MAJOR;

  Kontakt = {
    configure,
    connect,
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
if (Platform.OS === "ios") {
  const init = (
    /**
     * Optional Kontakt.io API key
     *
     * May not be provided for scanning and ranging.
     * Necessary for reading out beacon config.
     */
    apiKey: string | undefined | null = null
  ): Promise<void> => KontaktModule.init(apiKey);

  const startDiscovery = (
    config:
      | {
          /**
           * scanning interval in milliseconds
           */
          interval: number;
        }
      | undefined
  ): Promise<void> => KontaktModule.startDiscovery(config);
  const stopDiscovery: () => Promise<void> = KontaktModule.stopDiscovery;
  const restartDiscovery: () => Promise<void> = KontaktModule.restartDiscovery;
  const isDiscovering: () => Promise<boolean> = KontaktModule.isDiscovering;

  const getAuthorizationStatus: () => Promise<string> =
    KontaktModule.getAuthorizationStatus;
  const requestWhenInUseAuthorization: () => Promise<void> =
    KontaktModule.requestWhenInUseAuthorization;
  const requestAlwaysAuthorization: () => Promise<void> =
    KontaktModule.requestAlwaysAuthorization;

  const startRangingBeaconsInRegion = (region: RegionType): Promise<void> =>
    KontaktModule.startRangingBeaconsInRegion(region);
  const stopRangingBeaconsInRegion = (region: RegionType): Promise<void> =>
    KontaktModule.stopRangingBeaconsInRegion(region);
  const stopRangingBeaconsInAllRegions = (): Promise<void> =>
    KontaktModule.stopRangingBeaconsInAllRegions;
  const getRangedRegions: () => Promise<Array<RegionType>> =
    KontaktModule.getRangedRegions;

  const startMonitoringForRegion = (region: RegionType): Promise<void> =>
    KontaktModule.startMonitoringForRegion(region);
  const stopMonitoringForRegion = (region: RegionType): Promise<void> =>
    KontaktModule.stopMonitoringForRegion(region);
  const stopMonitoringForAllRegions: () => Promise<void> =
    KontaktModule.stopMonitoringForAllRegions;
  const getMonitoredRegions: () => Promise<Array<RegionType>> =
    KontaktModule.getMonitoredRegions;

  const requestStateForRegion = (region: RegionType): Promise<void> =>
    KontaktModule.requestStateForRegion(region);

  const startEddystoneDiscovery = (namespace: any): Promise<void> =>
    KontaktModule.startEddystoneDiscovery(namespace);
  const stopEddystoneDiscoveryInRegion = (region: RegionType): Promise<void> =>
    KontaktModule.stopEddystoneDiscoveryInRegion(region);
  const stopEddystoneDiscoveryInAllRegions: () => Promise<void> =
    KontaktModule.stopEddystoneDiscoveryInAllRegions;

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
    requestStateForRegion,
    // eddystone
    startEddystoneDiscovery,
    stopEddystoneDiscoveryInRegion,
    stopEddystoneDiscoveryInAllRegions,
  };
}

export * from "./types";

export default Kontakt as KontaktType;
