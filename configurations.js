export const IBEACON = "IBEACON";
export const EDDYSTONE = "EDDYSTONE";

export const scanMode = {
  LOW_POWER: 0,
  BALANCED: 1,
  LOW_LATENCY: 2,
};

export const scanPeriod = {
  RANGING: "RANGING",
  MONITORING: "MONITORING",
  // NB: Disabled for now, see https://github.com/Artirigo/react-native-kontaktio/issues/11
  // custom: (activePeriod = 8000, passivePeriod = 30000) => ({
  //   activePeriod,
  //   passivePeriod,
  // }),
};

export const activityCheckConfiguration = {
  DISABLED: "DISABLED",
  MINIMAL: "MINIMAL",
  DEFAULT: "DEFAULT",
};
