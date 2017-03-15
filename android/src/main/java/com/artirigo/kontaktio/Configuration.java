package com.artirigo.kontaktio;

import com.facebook.react.bridge.Promise;
import com.facebook.react.bridge.ReadableMap;
import com.facebook.react.bridge.ReadableType;

import com.kontakt.sdk.android.ble.configuration.ActivityCheckConfiguration;
import com.kontakt.sdk.android.ble.configuration.ForceScanConfiguration;
import com.kontakt.sdk.android.ble.configuration.ScanContext;
import com.kontakt.sdk.android.ble.configuration.ScanMode;
import com.kontakt.sdk.android.ble.configuration.ScanPeriod;
import com.kontakt.sdk.android.ble.manager.ProximityManager;

/**
 * Configure a ProximityManager with beacon ranging/monitoring details
 */
class Configuration {
    private ProximityManager proximityManager;

    private ScanMode scanMode;
    private ScanPeriod scanPeriod;
    private ActivityCheckConfiguration activityCheckConfiguration;
    private ForceScanConfiguration forceScanConfiguration;
    private long deviceUpdateCallbackInterval;
    private boolean monitoringEnabled;
    private int monitoringSyncInterval;


    Configuration(ProximityManager proximityManager) {
        this.proximityManager = proximityManager;

        // set default values
        this.scanMode = ScanMode.BALANCED;
        this.scanPeriod = ScanPeriod.RANGING;
        this.activityCheckConfiguration = ActivityCheckConfiguration.DEFAULT;
        this.forceScanConfiguration = new ForceScanConfiguration(5000, 1000);
        this.deviceUpdateCallbackInterval = ScanContext.DEFAULT_DEVICES_UPDATE_CALLBACK_INTERVAL; // 3000 ms
        this.monitoringEnabled = ScanContext.DEFAULT_MONITORING_ENABLED; // true
        this.monitoringSyncInterval = ScanContext.DEFAULT_MONITORING_SYNC_INTERVAL; // 10 sec
    }

    void configureProximityManager(ReadableMap params, Promise promise) {
        try {
            // ScanMode (constant ranging or selective monitoring)
            if (params.hasKey("scanMode") && !params.isNull("scanMode")) {
                scanMode = getScanMode(params.getInt("scanMode"));
            }

            // ScanPeriod (active and passive scan periods)
            if (params.hasKey("scanPeriod") && !params.isNull("scanPeriod")) {
                if (params.getType("scanPeriod") == ReadableType.String) {
                    scanPeriod = getScanPeriod(params.getString("scanPeriod"));

                } else if (params.getType("scanPeriod") == ReadableType.Map) {
                    ReadableMap scanPeriodMap = params.getMap("scanPeriod");

                    scanPeriod = ScanPeriod.create(
                            scanPeriodMap.getInt("activePeriod"),
                            scanPeriodMap.getInt("passivePeriod")
                    );
                } else {
                    throw new Exception("scanPeriod has to be a STRING or an OBJECT of INTEGERS");
                }
            }

            // ActivityCheckConfiguration (governs Beacon disappearance)
            if (params.hasKey("activityCheckConfiguration") && !params.isNull("activityCheckConfiguration")) {
                if (params.getType("activityCheckConfiguration") == ReadableType.String) {
                    activityCheckConfiguration = getActivityCheckConfiguration(params.getString("activityCheckConfiguration"));
                } else if (params.getType("activityCheckConfiguration") == ReadableType.Map) {

                    ReadableMap activityCheckConfigurationMap = params.getMap("activityCheckConfiguration");
                    activityCheckConfiguration = ActivityCheckConfiguration.create(
                            activityCheckConfigurationMap.getInt("inactivityTimeout"),
                            activityCheckConfigurationMap.getInt("checkPeriod")
                    );
                } else {
                    throw new Exception("activityCheckConfiguration has to be a STRING or an OBJECT of INTEGERS");
                }
            }

            // After setting ScanPeriod and ActivityCheckConfiguration: Check for faulty configuration
            // Active Scan Period must be bigger than checkPeriod for it to work as documented in
            // https://github.com/Artirigo/react-native-kontaktio/issues/11
            // ScanPeriod.create causes App crash if not in correct range
            if (scanPeriod.getActivePeriod() < activityCheckConfiguration.getCheckPeriod()) {
                throw new Exception("scanPeriod.activePeriod (" + scanPeriod.getActivePeriod() +
                        ") has to be greater than activityCheckConfiguration.checkPeriod (" + activityCheckConfiguration.getCheckPeriod() + ").");
            }

            // ForceScanConfiguration (Concerns a bug on some Android devices)
            if (params.hasKey("forceScanConfiguration") && !params.isNull("forceScanConfiguration")) {
                if (params.getType("forceScanConfiguration") == ReadableType.String) {
                    forceScanConfiguration = getForceScanConfiguration(params.getString("forceScanConfiguration"));
                } else if (params.getType("forceScanConfiguration") == ReadableType.Map) {

                    ReadableMap forceScanConfigurationMap = params.getMap("forceScanConfiguration");
                    int activePeriod = forceScanConfigurationMap.getInt("forceScanActivePeriod");
                    int passivePeriod = forceScanConfigurationMap.getInt("forceScanPassivePeriod");

                    if (activePeriod < 1000) {
                        throw new Exception("forceScanConfiguration.forceScanActivePeriod has to be greater equal 1000ms");
                    }
                    if (passivePeriod < 500) {
                        throw new Exception("forceScanConfiguration.forceScanPassivePeriod has to be greater equal 500ms");
                    }

                    activityCheckConfiguration = ActivityCheckConfiguration.create(
                            activePeriod,
                            passivePeriod
                    );
                } else {
                    throw new Exception("activityCheckConfiguration has to be a STRING or an OBJECT of INTEGERS");
                }
            }

            // monitoringEnabled (send data to Kontakt.io panel)
            if (params.hasKey("monitoringEnabled") && !params.isNull("monitoringEnabled")) {
                if (params.getType("monitoringEnabled") == ReadableType.Boolean) {
                    if (!params.getBoolean("monitoringEnabled")) {
                        monitoringEnabled = false;
                    }
                } else {
                    throw new Exception("monitoringEnabled has to be of type BOOLEAN");
                }
            }

            // monitoringSyncInterval (how often should data be sent to Kontakt.io panel)
            if (params.hasKey("monitoringSyncInterval") && !params.isNull("monitoringSyncInterval")) {
                monitoringSyncInterval = params.getInt("monitoringSyncInterval");
            }


            proximityManager.configuration()
                    .scanMode(scanMode)
                    .scanPeriod(scanPeriod)
                    .activityCheckConfiguration(activityCheckConfiguration)
                    .forceScanConfiguration(forceScanConfiguration)
                    .deviceUpdateCallbackInterval(deviceUpdateCallbackInterval)
                    .monitoringEnabled(monitoringEnabled)
                    .monitoringSyncInterval(monitoringSyncInterval);
            // other values not used in current version
//            .rssiCalculator(RssiCalculators.DEFAULT)
//            .cacheFileName("Example")
//            .resolveShuffledInterval(3)
//            .eddystoneFrameTypes(Arrays.asList(EddystoneFrameType.UID, EddystoneFrameType.URL));

            promise.resolve(null);
        } catch (Exception e) {
            promise.reject(Constants.EXCEPTION, e);
        }
    }

    private ScanMode getScanMode(int mode) throws Exception {
        switch (mode) {
            case 0:
                return ScanMode.LOW_POWER;
            case 1:
                return ScanMode.BALANCED;
            case 2:
                return ScanMode.LOW_LATENCY;
            default:
                throw new Exception("The value of scanMode has to be either LOW_POWER, BALANCED or LOW_LATENCY");
//                return ScanMode.BALANCED;
        }
    }

    private ScanPeriod getScanPeriod(String mode) throws Exception {
        switch (mode) {
            case "RANGING":
                return ScanPeriod.RANGING;
            case "MONITORING":
                return ScanPeriod.MONITORING;
            default:
                throw new Exception("scanPeriod default value has to be either RANGING or MONITORING");
//                return ScanPeriod.RANGING;
        }
    }

    private ActivityCheckConfiguration getActivityCheckConfiguration(String mode) throws Exception {
        switch (mode) {
            case "DISABLED":
                return ActivityCheckConfiguration.DISABLED;
            case "MINIMAL":
                return ActivityCheckConfiguration.MINIMAL;
            case "DEFAULT":
                return ActivityCheckConfiguration.DEFAULT;
            default:
                throw new Exception("activityCheckConfiguration default value has to be either DISABLED, MINIMAL or DEFAULT");
//                return ActivityCheckConfiguration.DEFAULT;
        }
    }

    private ForceScanConfiguration getForceScanConfiguration(String mode) throws Exception {
        switch (mode) {
            case "DISABLED":
                return ForceScanConfiguration.DISABLED;
            case "MINIMAL":
                return ForceScanConfiguration.MINIMAL;
            default:
                throw new Exception("forceScanConfiguration default value has to be either DISABLED or MINIMAL");
//                return ActivityCheckConfiguration.DEFAULT;
        }
    }
}
