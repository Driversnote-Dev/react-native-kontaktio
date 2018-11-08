package com.artirigo.kontaktio;

import com.facebook.react.bridge.Promise;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.bridge.ReadableArray;
import com.facebook.react.bridge.ReadableMap;

import com.kontakt.sdk.android.ble.connection.OnServiceReadyListener;
import com.kontakt.sdk.android.ble.device.BeaconRegion;
import com.kontakt.sdk.android.ble.manager.ProximityManager;
import com.kontakt.sdk.android.common.KontaktSDK;

import java.util.HashMap;
import java.util.Map;
import java.util.UUID;

/**
 * Kontakt.io Documentation: http://kontaktio.github.io/kontakt-android-sdk/2.1.0/Javadoc/overview-summary.html
 *
 * Created by André Kovac on 12/04/16.
 *
 */
public class KontaktModule extends ReactContextBaseJavaModule {
    private static final String TAG = "KontaktModule";

    private static ReactApplicationContext reactAppContext;

    private static final String DEFAULT_KONTAKT_BEACON_PROXIMITY_UUID = "DEFAULT_KONTAKT_BEACON_PROXIMITY_UUID";
    private static final String DEFAULT_KONTAKT_NAMESPACE_ID = "DEFAULT_KONTAKT_NAMESPACE_ID";
    private static final String BEACON_REGION_ANY_MAJOR = "ANY_MAJOR";
    private static final String BEACON_REGION_ANY_MINOR = "ANY_MINOR";
    private static final String PROXIMITY_IMMEDIATE = "PROXIMITY_IMMEDIATE";
    private static final String PROXIMITY_NEAR = "PROXIMITY_NEAR";
    private static final String PROXIMITY_FAR = "PROXIMITY_FAR";
    private static final String PROXIMITY_UNKNOWN = "PROXIMITY_UNKNOWN";
    private static final String SORT_ASC = "SORT_ASC";
    private static final String SORT_DESC = "SORT_DESC";
    private static final String SORT_DISABLED = "SORT_DISABLED";

    private ProximityManager proximityManager;
    private BeaconProximityManager beaconProximityManager;
    private Configuration configuration;
    private BeaconListeners beaconListeners;
    private ScanManager scanManager;
    private RegionManager regionManager;

    // Promise used to connect to beacons
    private Promise connectPromise;

    public KontaktModule(ReactApplicationContext reactAppContext) {
        super(reactAppContext);
        this.reactAppContext = reactAppContext;
    }

    @Override
    public String getName() {
        return "KontaktBeacons";
    }

    @Override
    public Map<String, Object> getConstants() {
        final Map<String, Object> constants = new HashMap<>();
        constants.put(DEFAULT_KONTAKT_BEACON_PROXIMITY_UUID, String.valueOf(KontaktSDK.DEFAULT_KONTAKT_BEACON_PROXIMITY_UUID));
        constants.put(DEFAULT_KONTAKT_NAMESPACE_ID, String.valueOf(KontaktSDK.DEFAULT_KONTAKT_NAMESPACE_ID));
        constants.put(BEACON_REGION_ANY_MAJOR, BeaconRegion.ANY_MAJOR);
        constants.put(BEACON_REGION_ANY_MINOR, BeaconRegion.ANY_MINOR);
//        constants.put(PROXIMITY_IMMEDIATE, String.valueOf(Proximity.IMMEDIATE));
//        constants.put(PROXIMITY_NEAR, String.valueOf(Proximity.NEAR));
//        constants.put(PROXIMITY_FAR, String.valueOf(Proximity.FAR));
//        constants.put(PROXIMITY_UNKNOWN, String.valueOf(Proximity.UNKNOWN));
//        constants.put(SORT_ASC, String.valueOf(DistanceSort.ASC));
//        constants.put(SORT_DESC, String.valueOf(DistanceSort.DESC));
//        constants.put(SORT_DISABLED, String.valueOf(DistanceSort.DISABLED));
        return constants;
    }

    // ------------
    // Methods exposed to React Native
    // ------------

    @ReactMethod
    public void connect(String apiKey, ReadableArray beaconTypes, Promise promise) {
        try {
            connectPromise = promise;

            beaconProximityManager = new BeaconProximityManager(reactAppContext, apiKey);
            beaconProximityManager.init(beaconTypes, promise);

            proximityManager = beaconProximityManager.getProximityManager();
            configuration = beaconProximityManager.getConfiguration();
            beaconListeners = beaconProximityManager.getBeaconListeners();
            scanManager = beaconProximityManager.getScanManager();
            regionManager = beaconProximityManager.getRegionManager();

            // connect to beaconManager
            proximityManager.connect(serviceReadyListener);
        } catch (Exception e) {
            connectPromise.reject(Constants.EXCEPTION, e);
        }
    }

    OnServiceReadyListener serviceReadyListener = new OnServiceReadyListener() {
        /**
         * Assuring that the callback is only called once (i.e. connectPromise only resolved once)
         *
         * From http://facebook.github.io/react-native/docs/native-modules-android.html#callbacks :
         * > A native module is supposed to invoke its callback only once. It can, however, store the callback and invoke it later.
         */
        boolean callbackWasCalled = false;

        @Override
        public void onServiceReady() {
            if (callbackWasCalled) return;
            callbackWasCalled = true;

            try {
                connectPromise.resolve(null);
            } catch (Exception e) {
                // Catches the exception: java.lang.RuntimeException·Illegal callback invocation from native module
                connectPromise.reject(Constants.EXCEPTION, e);
            }
        }
    };

    // From BeaconProximityManager
    @ReactMethod
    public void disconnect(Promise promise) {
        if (beaconProximityManager != null) {
            beaconProximityManager.disconnect(promise);
        } else {
            promise.reject("Did you forget to call connect() or did the connect() call fail? The beaconProximityManager object is not defined.");
        }
    }
    @ReactMethod
    public void isConnected(Promise promise) {
        try {
            if (proximityManager != null) {
                boolean isConnected = proximityManager.isConnected();
                promise.resolve(isConnected);
            } else {
                promise.resolve(false);
            }
        } catch (Exception e) {
            promise.reject(Constants.EXCEPTION, e);
        }
    }

    // From ScanManager
    @ReactMethod
    public void startScanning(Promise promise) {
        if (scanManager != null) {
            scanManager.startScanning(promise);
        } else {
            promise.reject("Did you forget to call connect() or did the connect() call fail? The scanManager object is not defined.");
        }
    }
    @ReactMethod
    public void stopScanning(Promise promise) {
        if (scanManager != null) {
            scanManager.stopScanning(promise);
        } else {
            promise.reject("Did you forget to call connect() or did the connect() call fail? The scanManager object is not defined.");
        }
    }
    @ReactMethod
    public void restartScanning(Promise promise) {
        if (scanManager != null) {
            scanManager.restartScanning(promise);
        } else {
            promise.reject("Did you forget to call connect() or did the connect() call fail? The scanManager object is not defined.");
        }
    }
    @ReactMethod
    public void isScanning(Promise promise) {
        if (scanManager != null) {
            scanManager.isScanning(promise);
        } else {
            promise.reject("Did you forget to call connect() or did the connect() call fail? The scanManager object is not defined.");
        }
    }

    // From Configuration
    @ReactMethod
    public void configure(ReadableMap params, Promise promise) {
        if (configuration != null) {
            configuration.configureProximityManager(params, promise);
        } else {
            promise.reject("Did you forget to call connect() or did the connect() call fail? The configuration object is not defined.");
        }
    }

    // From RegionManager
    /**
     * Replaces the currently observed region(s) with the given region
     * If region is null or empty, the default region EVERYWHERE is used.
     *
     * Restart has to be triggered so that region changes take effect when
     * changing regions after scan started.
     *
     * @param region Object with IBeacon region data
     * @param promise
     */
    @ReactMethod
    public void setBeaconRegion(ReadableMap regionParams, Promise promise) {
        if (regionManager != null) {
            regionManager.setBeaconRegion(regionParams, promise);
        } else {
            promise.reject("Did you forget to call connect() or did the connect() call fail? The regionManager object is not defined.");
        }
    }

    @ReactMethod
    public void setBeaconRegions(ReadableArray regionsParams, Promise promise) {
        if (regionManager != null) {
            regionManager.setBeaconRegions(regionsParams, promise);
        } else {
            promise.reject("Did you forget to call connect() or did the connect() call fail? The regionManager object is not defined.");
        }
    }

    @ReactMethod
    public void getBeaconRegions(Promise promise) {
        if (regionManager != null) {
            regionManager.getBeaconRegions(promise);
        } else {
            promise.reject("Did you forget to call connect() or did the connect() call fail? The regionManager object is not defined.");
        }
    }

    @ReactMethod
    public void setEddystoneNamespace(ReadableMap namespaceParams, Promise promise) {
        if (regionManager != null) {
            regionManager.setEddystoneNamespace(namespaceParams, promise);
        } else {
            promise.reject("Did you forget to call connect() or did the connect() call fail? The regionManager object is not defined.");
        }
    }
}
