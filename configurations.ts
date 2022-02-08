export const IBEACON = 'IBEACON';
export const EDDYSTONE = 'EDDYSTONE';
export const SECURE_PROFILE = 'SECURE_PROFILE';

export const scanMode = {
  LOW_POWER: 0,
  BALANCED: 1,
  LOW_LATENCY: 2,
};

export const scanPeriod = {
  RANGING: 'RANGING',
  MONITORING: 'MONITORING',
  // Default values equal configuration MONITORING
  create: ({ activePeriod = 8000, passivePeriod = 30000 }) => ({
    activePeriod,
    passivePeriod,
  }),
};

export const activityCheckConfiguration = {
  DISABLED: 'DISABLED',
  MINIMAL: 'MINIMAL',
  DEFAULT: 'DEFAULT',
  // Default values equal configuration MINIMAL
  create: ({ inactivityTimeout = 3000, checkPeriod = 1000 }) => ({
    inactivityTimeout,
    checkPeriod,
  }),
};

export const forceScanConfiguration = {
  DISABLED: 'DISABLED',
  MINIMAL: 'MINIMAL',
  // Default values equal configuration MINIMAL
  create: ({ forceScanActivePeriod = 1000, forceScanPassivePeriod = 500 }) => ({
    forceScanActivePeriod,
    forceScanPassivePeriod,
  }),
};

export const monitoringEnabled = {
  TRUE: true,
  FALSE: false,
};

export const monitoringSyncInterval = {
  DEFAULT: 10, // 10 seconds
};
