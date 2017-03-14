class Configuration {
  constructor() {
    this.config = null;
  }

  getConfig() {
    return this.config;
  }
}

export const IBEACON = "IBEACON";
export const EDDYSTONE = "EDDYSTONE";

export class ScanMode extends Configuration {
  static LOW_POWER = new ScanMode(0);
  static BALANCED = new ScanMode(1);
  static LOW_LATENCY = new ScanMode(2);

  constructor(value) {
    super();
    this.config = value;
  }
}

export class ScanPeriod extends Configuration {
  // Kontakt.io SDK defaults
  static RANGING = new ScanPeriod("RANGING");
  static MONITORING = new ScanPeriod("MONITORING");

  constructor(value) {
    super();
    this.config = value;
  }

  // NB: ScanPeriod.create causes App crash in version 3.2.1 of Kontakt.io SDK
  // static RANGING = new ScanPeriod(null, null, "RANGING");
  // static MONITORING = new ScanPeriod(null, null, "MONITORING");
  //
  // // 8 and 30 are default values for MONITORING
  // constructor(activePeriod = 8000, passivePeriod = 30000, defaultType) {
  //   super();
  //   if (defaultType) {
  //     this.config = defaultType;
  //   } else {
  //     this.config = {
  //       activePeriod,
  //       passivePeriod,
  //     }
  //   }
  // }
}

export class ActivityCheckConfiguration extends Configuration {
  static DISABLED = new ActivityCheckConfiguration("DISABLED");
  static MINIMAL = new ActivityCheckConfiguration("MINIMAL");
  static DEFAULT = new ActivityCheckConfiguration("DEFAULT");

  constructor(value) {
    super();
    this.config = value;
  }
}
