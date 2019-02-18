package com.artirigo.kontaktio;

import com.facebook.react.bridge.Promise;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReadableArray;

import com.kontakt.sdk.android.ble.manager.ProximityManager;
import com.kontakt.sdk.android.ble.manager.ProximityManagerFactory;
import com.kontakt.sdk.android.common.KontaktSDK;

/**
 * Set up and initialize a ProximityManager
 */
class BeaconProximityManager {
    private final static String IBEACON = "IBEACON";
    private final static String EDDYSTONE = "EDDYSTONE";
    private final static String SECURE_PROFILE = "SECURE_PROFILE";

    private final ReactApplicationContext reactAppContext;
    private String kontaktApiKey;

    private ProximityManager proximityManager;

    private BeaconListeners beaconListeners;
    private ScanManager scanManager;
    private RegionManager regionManager;
    private Configuration configuration;

    BeaconProximityManager(ReactApplicationContext reactAppContext, String kontaktApiKey) {
        this.reactAppContext = reactAppContext;
        this.kontaktApiKey = (kontaktApiKey == null) || kontaktApiKey.isEmpty() ? "NO_API_KEY" : kontaktApiKey;
    }

    ProximityManager init(ReadableArray beaconTypes) throws Exception {
        // init
        KontaktSDK.initialize(kontaktApiKey);

        // create manager
        proximityManager = ProximityManagerFactory.create(reactAppContext);

        // Instantiate helpers
        beaconListeners = new BeaconListeners(reactAppContext);
        scanManager = new ScanManager(proximityManager);
        regionManager = new RegionManager(proximityManager);
        configuration = new Configuration(proximityManager);

        // Add beacon listener(s)
        if (beaconTypes == null || beaconTypes.size() == 0) {
            proximityManager.setIBeaconListener(beaconListeners.createIBeaconListener());
        } else if (beaconTypes.size() == 1) {
            if (beaconTypes.getString(0).equals(IBEACON)) {
                proximityManager.setIBeaconListener(beaconListeners.createIBeaconListener());
            } else if (beaconTypes.getString(0).equals(EDDYSTONE)) {
                proximityManager.setEddystoneListener(beaconListeners.createEddystoneListener());
            } else if (beaconTypes.getString(0).equals(SECURE_PROFILE)) {
                proximityManager.setSecureProfileListener(beaconListeners.createSecureProfileListener());
            } else {
                throw new Exception(
                        "The value of the beaconType(s) has to be either IBEACON, EDDYSTONE or SECURE_PROFILE");
            }
        } else if (beaconTypes.size() == 2) {
            if ((beaconTypes.getString(0).equals(IBEACON) && beaconTypes.getString(1).equals(EDDYSTONE))
                    || (beaconTypes.getString(0).equals(EDDYSTONE) && beaconTypes.getString(1).equals(IBEACON))) {
                proximityManager.setIBeaconListener(beaconListeners.createIBeaconListener());
                proximityManager.setEddystoneListener(beaconListeners.createEddystoneListener());
            } else if (beaconTypes.getString(0).equals(IBEACON) && beaconTypes.getString(1).equals(SECURE_PROFILE)) {
                proximityManager.setIBeaconListener(beaconListeners.createIBeaconListener());
                proximityManager.setSecureProfileListener(beaconListeners.createSecureProfileListener());
            } else if (beaconTypes.getString(0).equals(EDDYSTONE) && beaconTypes.getString(1).equals(SECURE_PROFILE)) {
                proximityManager.setEddystoneListener(beaconListeners.createEddystoneListener());
                proximityManager.setSecureProfileListener(beaconListeners.createSecureProfileListener());
            } else {
                throw new Exception(
                        "The beaconTypes values have to be IBEACON, EDDYSTONE or SECURE_PROFILE. If added, SECURE_PROFILE has to go last.");
            }
        } else if (beaconTypes.size() == 3) {
            if ((beaconTypes.getString(0).equals(IBEACON) && beaconTypes.getString(1).equals(EDDYSTONE)
                    && beaconTypes.getString(2).equals(SECURE_PROFILE))
                    || (beaconTypes.getString(0).equals(EDDYSTONE) && beaconTypes.getString(1).equals(IBEACON)
                            && beaconTypes.getString(2).equals(SECURE_PROFILE))) {
                proximityManager.setIBeaconListener(beaconListeners.createIBeaconListener());
                proximityManager.setSecureProfileListener(beaconListeners.createSecureProfileListener());
                proximityManager.setEddystoneListener(beaconListeners.createEddystoneListener());
            } else {
                throw new Exception(
                        "The beaconTypes values have to be IBEACON, EDDYSTONE or SECURE_PROFILE. If added, SECURE_PROFILE has to go last.");
            }
        } else {
            throw new Exception("beaconTypes array has to have less than 3 arguments or be empty");
        }

        // Add further listeners
        proximityManager.setSpaceListener(beaconListeners.createSpaceListener());
        proximityManager.setScanStatusListener(beaconListeners.createScanStatusListener());

        return proximityManager;
    }

    void disconnect(Promise promise) {
        try {
            proximityManager.disconnect();
            proximityManager = null;
            promise.resolve(null);
        } catch (Exception e) {
            promise.reject(Constants.EXCEPTION, e);
        }
    }

    void isConnected(Promise promise) {
        try {
            boolean isConnected = proximityManager.isConnected();
            promise.resolve(isConnected);
        } catch (Exception e) {
            promise.reject(Constants.EXCEPTION, e);
        }
    }

    /*
     * Getter
     */

    public ProximityManager getProximityManager() {
        return proximityManager;
    }

    public BeaconListeners getBeaconListeners() {
        return beaconListeners;
    }

    public ScanManager getScanManager() {
        return scanManager;
    }

    public RegionManager getRegionManager() {
        return regionManager;
    }

    public Configuration getConfiguration() {
        return configuration;
    }
}
