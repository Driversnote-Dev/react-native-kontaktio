import { NativeModules } from "react-native";
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

export type IBeaconMinimum = {
  major: number;
  minor: number;
};
export type IBeaconBase = {
  uuid: string;
  major: number;
  minor: number;
  uniqueId?: string;
};

export type Proximity = "IMMEDIATE" | "NEAR" | "FAR" | "UNKNOWN";

/**
 * Beacon response while scanning on Android
 */
export type IBeaconAndroid = {
  // IBeaconBase
  major: number;
  minor: number;
  uuid: string;
  // BeaconAndroid
  name: string;
  uniqueId: string;
  firmwareVersion: string;
  address: string;
  rssi: number;
  proximity: Proximity;
  accuracy: string;
  // Distance in meters
  batteryPower: number;
  // Percentage as int
  txPower: number;
  isShuffled: string;
};

export type SecureProfileAndroid = {
  name?: string;
  uniqueId: string;
  firmwareRevision: string;
  macAddress: string;
  rssi: number;
  batteryLevel: number;
  isShuffled: boolean;
  txPower: number;
  telemetry?: any;
};

/**
 * Beacon response while ranging or monitoring on iOS
 */
export type IBeaconIos = {
  // IBeaconBase
  major: number;
  minor: number;
  uuid: string;
  //
  rssi: number;
  proximity: Proximity;
  accuracy: string; // Distance in meters (if Kontakt.io Beacon)
};

/**
 * Beacon response while discovering
 */
export type IBeaconIosDiscovery = {
  name?: string;
  // 'Kontakt' by default for Kontakt.io beacons
  uniqueId: string;
  firmwareVersion: string;
  /**
   * percentage as integer (same as 'batteryPower' for Android)
   */
  batteryLevel: number;
  batteryPowered: boolean;
  /**
   * same as 'txPower' for Android
   */
  transmissionPower: number;
  hasConfigurationProfile: boolean;
  shuffled: boolean;
  locked: boolean;
  model: string;
  peripheral: string;
  rssi: number;
  updatedAt: number;
};

export type IBeaconIosDiscoveryWithMajorMinor = IBeaconIosDiscovery & {
  major?: number;
  minor?: number;
};

export type IBeaconWithUniqueId =
  | IBeaconAndroid
  | IBeaconIosDiscoveryWithMajorMinor;

export type IBeacon = IBeaconAndroid | IBeaconIos | IBeaconIosDiscovery;

export type BeaconType =
  | typeof IBEACON
  | typeof EDDYSTONE
  | typeof SECURE_PROFILE;

export type RegionBase = {
  uuid: string;
  identifier: string;
  major?: number;
  minor?: number;
  uniqueId?: string;
};

export type RegionAndroid = RegionBase & { secureUuid?: string };

export type RegionIos = RegionBase;

export type RegionType = RegionAndroid | RegionIos;

/**
 * beacon scanning configuration
 */
export type ConfigType = {
  scanMode?:
    | typeof scanMode.LOW_POWER
    | typeof scanMode.BALANCED
    | typeof scanMode.LOW_LATENCY;
  scanPeriod?:
    | typeof scanPeriod.MONITORING
    | typeof scanPeriod.RANGING
    | ReturnType<typeof scanPeriod.create>;
  activityCheckConfiguration?:
    | typeof activityCheckConfiguration.DISABLED
    | typeof activityCheckConfiguration.MINIMAL
    | typeof activityCheckConfiguration.DEFAULT
    | ReturnType<typeof activityCheckConfiguration.create>;
  forceScanConfiguration?:
    | typeof activityCheckConfiguration.DISABLED
    | typeof activityCheckConfiguration.MINIMAL
    | ReturnType<typeof forceScanConfiguration.create>;
  dropEmptyRanges?: boolean;
  invalidationAge?: number;
  monitoringEnabled?:
    | typeof monitoringEnabled.TRUE
    | typeof monitoringEnabled.FALSE;
  monitoringSyncInterval?: typeof monitoringSyncInterval.DEFAULT;
};

type KontaktBaseType = {
  configure: (config: ConfigType | undefined) => Promise<void>;
};

export type KontaktAndroidType = KontaktBaseType & {
  connect: (
    /**
     * Kontakt.io API key
     */
    key?: string,
    /**
     * which beacon types to scan for
     */
    beaconTypes?: Array<BeaconType> | undefined
  ) => Promise<void>;
  disconnect: () => Promise<void>;
  isConnected: () => Promise<boolean>;

  startScanning: () => Promise<void>;
  stopScanning: () => Promise<void>;
  restartScanning: () => Promise<void>;
  isScanning: () => Promise<boolean>;

  setBeaconRegion: (region: RegionType) => void;
  setBeaconRegions: (regions: Array<RegionType>) => void;
  getBeaconRegions: () => Promise<Array<RegionType>>;
  setEddystoneNamespace: (namespace: any) => void;

  // Constants
  IBEACON: typeof IBEACON;
  EDDYSTONE: typeof EDDYSTONE;
  SECURE_PROFILE: typeof SECURE_PROFILE;
  DEFAULT_KONTAKT_BEACON_PROXIMITY_UUID: string;
  DEFAULT_KONTAKT_NAMESPACE_ID: string;
  ANY_MAJOR: number;
  ANY_MINOR: number;
  // Configurations
  scanMode: typeof scanMode;
  scanPeriod: typeof scanPeriod;
  activityCheckConfiguration: typeof activityCheckConfiguration;
  forceScanConfiguration: typeof forceScanConfiguration;
  monitoringEnabled: typeof monitoringEnabled;
  monitoringSyncInterval: typeof monitoringSyncInterval;

  /**
   * @deprecated Please use 'connect' instead
   */
  init?: (
    apiKey: string | undefined,
    beaconTypes: Array<BeaconType> | undefined
  ) => Promise<void>;
};

export type KontaktiOSType = KontaktBaseType & {
  init: (apiKey?: string | undefined) => Promise<void>;

  isDiscovering: () => Promise<boolean>;
  startDiscovery: (config?: { interval: number }) => Promise<void>;
  stopDiscovery: () => Promise<void>;
  restartDiscovery: () => Promise<void>;

  getAuthorizationStatus: () => Promise<string>;
  requestWhenInUseAuthorization: () => Promise<void>;
  requestAlwaysAuthorization: () => Promise<void>;

  startRangingBeaconsInRegion: (region: RegionType) => Promise<void>;
  stopRangingBeaconsInRegion: (region: RegionType) => Promise<void>;
  stopRangingBeaconsInAllRegions: () => Promise<void>;
  getRangedRegions: () => Promise<Array<RegionType>>;

  startMonitoringForRegion: (region: RegionType) => Promise<void>;
  stopMonitoringForRegion: (region: RegionType) => Promise<void>;
  stopMonitoringForAllRegions: () => Promise<void>;
  getMonitoredRegions: () => Promise<Array<RegionType>>;
  requestStateForRegion: (region: RegionType) => Promise<void>;

  startEddystoneDiscovery: (namespace: any) => Promise<void>;
  stopEddystoneDiscoveryInRegion: (region: RegionType) => Promise<void>;
  stopEddystoneDiscoveryInAllRegions: () => Promise<void>;
};

export const KontaktModule = NativeModules.KontaktBeacons;

export type KontaktType = KontaktAndroidType & KontaktiOSType;

declare const module: KontaktType;

export default module;
