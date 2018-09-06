/**
 * @flow
 * Flow type definitions to use in your project
 */
type IBeaconBase = {
  uuid: string,
  major: number,
  minor: number,
}

type Proximity = 'IMMEDIATE' | 'NEAR' | 'FAR' | 'UNKNOWN';

type Telemetry = {
  batteryVoltage: number,
  temperature: number,
  pduCount: number,
  timeSincePowerUp: number,
  version: number,
};

type BeaconAndroid = {
  // each beacon contains:
  name: string,
  address: string,
  rssi: number,
  proximity: Proximity,
  // if Kontakt.io beacon the following values are useful, otherwise they mostly
  // have the value -1 or similar
  accuracy: string, // Distance in meters
  batteryPower: number, // Percentage as int
  txPower: number,
  firmwareVersion: string,
  uniqueId: string,
  isShuffled: string,
}

export type IBeaconAndroid = IBeaconBase & BeaconAndroid;

export type EddystoneAndroid = BeaconAndroid & {
  namespace: string,
  instanceId: string,
  url: string,
  eid: string,
  encryptedTelemetry: string,
  telemetry: Telemetry,
}

export type IBeaconIos = IBeaconBase & {
  rssi: number,
  proximity: Proximity,
  accuracy: number, // Distance in meters (if Kontakt.io beacon)
}

export type IBeaconIosDiscovery = {
  name: string,  // 'Kontakt' by default for Kontakt.io beacons
	uniqueId: string,
	firmwareVersion: string,
	batteryLevel: number, // percentage as int (same as 'batteryPower' for Android)
	batteryPowered: boolean,
	transmissionPower: number,  // same as 'txPower' for Android
	hasConfigurationProfile: boolean,
	shuffled: boolean,
	locked: boolean,
	model: string,
	peripheral: string,
	rssi: number,
	updatedAt: number,
}


/**
 * Regions & Namespaces
 */

export type RegionAndroid = IBeaconBase & {
  identifier: string,
  secureUuid?: string,
};

export type RegionIos = IBeaconBase & {
  identifier: string,
};

export type NamespaceAndroid = {
  identifier: string,
  instanceId: string,
  namespace: string,
  secureNamespace: string,
}

/**
 * Options
 */
export type ScanPeriodLimits = {
  activePeriod?: number,
  passivePeriod?: number,
}

export type ForceScanConfigurationOptions = {
  forceScanActivePeriod?: number,
  forceScanPassivePeriod?: number,
}

export type ActivityCheckConfigurationOptions = {
  inactivityTimeout?: number,
  checkPeriod?: number,
}

export type ConfigurationAndroid = {
  scanMode?: 0 | 1 | 2,
  scanPeriod?: ScanPeriodLimits,
  activeCheckConfiguration?: ActivityCheckConfigurationOptions,
  forceScanConfiguration?: ForceScanConfigurationOptions,
  deviceUpdateCallbackInterval?: number,
  monitoringEnabled?: boolean,
  monitoringSyncInterval?: number,
};

export type ConfigurationIos = {
  dropEmptyRanges: boolean,
  invalidationAge: number,
  connectNearbyBeacons: boolean,
};
