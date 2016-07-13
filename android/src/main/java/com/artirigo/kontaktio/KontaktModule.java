package com.artirigo.kontaktio;

import android.support.annotation.Nullable;
import android.util.Log;

import com.facebook.react.bridge.Arguments;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.bridge.ReadableMap;
import com.facebook.react.bridge.WritableArray;
import com.facebook.react.bridge.WritableMap;
import com.facebook.react.bridge.WritableNativeArray;
import com.facebook.react.bridge.WritableNativeMap;
import com.facebook.react.modules.core.DeviceEventManagerModule;

import com.kontakt.sdk.android.ble.configuration.ActivityCheckConfiguration;
import com.kontakt.sdk.android.ble.configuration.ForceScanConfiguration;
import com.kontakt.sdk.android.ble.configuration.ScanPeriod;
import com.kontakt.sdk.android.ble.configuration.scan.EddystoneScanContext;
import com.kontakt.sdk.android.ble.configuration.scan.IBeaconScanContext;
import com.kontakt.sdk.android.ble.configuration.scan.ScanContext;
import com.kontakt.sdk.android.ble.connection.OnServiceReadyListener;
import com.kontakt.sdk.android.ble.device.BeaconRegion;
import com.kontakt.sdk.android.ble.device.EddystoneDevice;
import com.kontakt.sdk.android.ble.device.EddystoneNamespace;
import com.kontakt.sdk.android.ble.discovery.BluetoothDeviceEvent;
import com.kontakt.sdk.android.ble.discovery.DistanceSort;
import com.kontakt.sdk.android.ble.discovery.ibeacon.IBeaconDeviceEvent;
import com.kontakt.sdk.android.ble.manager.ProximityManager;
import com.kontakt.sdk.android.ble.manager.ProximityManagerContract;
import com.kontakt.sdk.android.common.KontaktSDK;
import com.kontakt.sdk.android.common.Proximity;
import com.kontakt.sdk.android.common.log.LogLevel;
import com.kontakt.sdk.android.common.profile.DeviceProfile;
import com.kontakt.sdk.android.common.profile.IBeaconDevice;
import com.kontakt.sdk.android.common.profile.IBeaconRegion;
import com.kontakt.sdk.android.common.profile.IEddystoneNamespace;
import com.kontakt.sdk.android.common.profile.RemoteBluetoothDevice;
import com.kontakt.sdk.android.manager.KontaktProximityManager;

import com.artirigo.kontaktio.BuildConfig;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.UUID;
import java.util.concurrent.TimeUnit;

/**
 * Kontakt.io Documentation: http://kontaktio.github.io/kontakt-android-sdk/2.1.0/Javadoc/overview-summary.html
 *
 * Created by André Kovac on 12/04/16.
 *
 */
public class KontaktModule extends ReactContextBaseJavaModule implements ProximityManager.ProximityListener {
    private static final String TAG = "KontaktModule";

    private static ReactApplicationContext context;
    private static android.content.Context applicationContext;

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

    private ProximityManagerContract proximityManager;
    private ScanContext scanContext;
    private BeaconRegion region;

    public KontaktModule(ReactApplicationContext reactContext) {
        super(reactContext);
        context = reactContext;
        this.applicationContext = reactContext.getApplicationContext();
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
        constants.put(PROXIMITY_IMMEDIATE, String.valueOf(Proximity.IMMEDIATE));
        constants.put(PROXIMITY_NEAR, String.valueOf(Proximity.NEAR));
        constants.put(PROXIMITY_FAR, String.valueOf(Proximity.FAR));
        constants.put(PROXIMITY_UNKNOWN, String.valueOf(Proximity.UNKNOWN));
        constants.put(SORT_ASC, String.valueOf(DistanceSort.ASC));
        constants.put(SORT_DESC, String.valueOf(DistanceSort.DESC));
        constants.put(SORT_DISABLED, String.valueOf(DistanceSort.DISABLED));
        return constants;
    }

    @ReactMethod
    public void initKontaktSDKWithApiKey(String apiKey) {
        KontaktSDK.initialize(apiKey)
                .setDebugLoggingEnabled(BuildConfig.DEBUG)
                .setLogLevelEnabled(LogLevel.DEBUG, true);
        proximityManager = new KontaktProximityManager(context);
    }

    @ReactMethod
    public void startRangingBeaconsInRegion(ReadableMap regionParams, ReadableMap scanContextParams) {

        Collection<IBeaconRegion> beaconRegions = new ArrayList<>();
        beaconRegions.add(_getRegion(regionParams));

        _initializeScan(beaconRegions, scanContextParams);

    }

    @ReactMethod
    public void startRangingBeaconsInNamespace(String namespaceParams, ReadableMap scanContextParams) {
        // TODO: Implement for Eddystone beacons
    }

    private void _initializeScan(Collection<IBeaconRegion> beaconRegions, ReadableMap scanContextParams) {
        final WritableMap map = Arguments.createMap();

        proximityManager.initializeScan(_getScanContext(beaconRegions, scanContextParams), new OnServiceReadyListener() {
            @Override
            public void onServiceReady() {
                proximityManager.attachListener(KontaktModule.this);

//                Toast.makeText(getReactApplicationContext(), "beacon service is ready!", Toast.LENGTH_SHORT).show();

                map.putString("status", "SUCCESS");
                sendEvent(context, "scanInitStatus", map);
            }

            @Override
            public void onConnectionFailure() {
//                Toast.makeText(getReactApplicationContext(), "beacon connection failed", Toast.LENGTH_SHORT).show();

                map.putString("status", "FAILURE");
                sendEvent(context, "scanInitStatus", map);
            }
        });
    }

    /**
     * Build beacon region from incoming data
     * @param regionParams
     * @return
     */
    private BeaconRegion _getRegion(ReadableMap regionParams) {
        if (region == null) {
            String identifier = regionParams.isNull("identifier") ? "default" : regionParams.getString("identifier");
            UUID uuid = regionParams.isNull("uuid") ? KontaktSDK.DEFAULT_KONTAKT_BEACON_PROXIMITY_UUID : UUID.fromString(regionParams.getString("uuid"));
            int major = regionParams.isNull("major") ? BeaconRegion.ANY_MAJOR : regionParams.getInt("major");
            int minor = regionParams.isNull("minor") ? BeaconRegion.ANY_MINOR : regionParams.getInt("minor");

            // Currently only one region supported
            region = new BeaconRegion.Builder()
                    .setIdentifier(identifier)
                    .setProximity(uuid)
                    .setMajor(major)
                    .setMinor(minor)
                    .build();
        }
        return region;
    }

    // Set ScanContext details
    private ScanContext _getScanContext(Collection<IBeaconRegion> beaconRegions, ReadableMap scanContextParams) {

        // TODO: Test the following two values
        long iBeaconTime = scanContextParams.isNull("iBeaconDevicesUpdateCallbackInterval") ? TimeUnit.SECONDS.toMillis(2) : scanContextParams.getInt("iBeaconDevicesUpdateCallbackInterval");
        long eddystoneTime = scanContextParams.isNull("eddystoneDevicesUpdateCallbackInterval") ? TimeUnit.SECONDS.toMillis(2) : scanContextParams.getInt("eddystoneDevicesUpdateCallbackInterval");
        DistanceSort iBeaconSort = scanContextParams.isNull("iBeaconDistanceSort") ? DistanceSort.DISABLED : DistanceSort.valueOf(scanContextParams.getString("iBeaconDistanceSort"));
        DistanceSort eddystoneSort = scanContextParams.isNull("eddystoneDistanceSort") ? DistanceSort.DISABLED : DistanceSort.valueOf(scanContextParams.getString("eddystoneDistanceSort"));

        if (scanContext == null) {
            scanContext = new ScanContext.Builder()
                    .setScanPeriod(ScanPeriod.RANGING) // or for monitoring for 15 seconds scan and 10 seconds waiting:
//                    .setScanPeriod(new ScanPeriod(TimeUnit.SECONDS.toMillis(15), 0))
                    .setScanMode(ProximityManager.SCAN_MODE_BALANCED)
                    .setActivityCheckConfiguration(ActivityCheckConfiguration.MINIMAL)
                    .setForceScanConfiguration(ForceScanConfiguration.MINIMAL)
                    .setIBeaconScanContext(new IBeaconScanContext.Builder()
                                    // .setIBeaconFilters(filterList)
                                    .setDevicesUpdateCallbackInterval(iBeaconTime)
                                    .setDistanceSort(iBeaconSort)
                                    .setIBeaconRegions(beaconRegions)
                                    .build()
                    )
                    .setEddystoneScanContext(new EddystoneScanContext.Builder()
                                    .setDevicesUpdateCallbackInterval(eddystoneTime)
                                    .setDistanceSort(eddystoneSort)
                                    .setEddystoneNamespaces(Collections.<IEddystoneNamespace>singletonList(
                                            new EddystoneNamespace("abcdef1234567890abcd", KontaktSDK.DEFAULT_KONTAKT_NAMESPACE_ID)
                                    ))
                                    .build()
                    )
                    .setForceScanConfiguration(ForceScanConfiguration.MINIMAL)
                    .build();
        }
        return scanContext;
    }

    private void sendEvent(ReactContext reactContext,
                           String eventName,
                           @Nullable WritableMap params) {
        reactContext
                .getJSModule(DeviceEventManagerModule.RCTDeviceEventEmitter.class)
                .emit(eventName, params);
    }

    @Override
    public void onScanStart() {
        Log.d(TAG, "scan started");

        final WritableMap map = Arguments.createMap();
        map.putString("status", "START");
        sendEvent(context, "scanStatus", map);
    }

    @Override
    public void onScanStop() {
        Log.d(TAG, "scan stopped");

        final WritableMap map = Arguments.createMap();
        map.putString("status", "STOP");
        sendEvent(context, "scanStatus", map);
    }

    @Override
    public void onEvent(BluetoothDeviceEvent bluetoothDeviceEvent) {
        // List of devices
        List<? extends RemoteBluetoothDevice> bluetoothDeviceList = bluetoothDeviceEvent.getDeviceList();
        DeviceProfile deviceProfile = bluetoothDeviceEvent.getDeviceProfile();

        // Initialize map to sent to JS
        WritableMap beaconsMap = Arguments.createMap();

        // Add Timestamp to map
        long timestamp = bluetoothDeviceEvent.getTimestamp();
        beaconsMap.putDouble("timestamp", timestamp);

//        Cast bluetoothDeviceEvent to iBeaconDeviceEvent for now (no Eddystone support)
//        List<? extends IBeaconDevice> iBeaconDeviceList;
//        IBeaconDeviceEvent iBeaconDeviceEvent = (IBeaconDeviceEvent) bluetoothDeviceEvent;
//        iBeaconDeviceList = iBeaconDeviceEvent.getDeviceList();


        // Add Region to map - only applicable for iBeacons
        if (DeviceProfile.IBEACON == deviceProfile) {
            IBeaconRegion enteredRegion = ((IBeaconDeviceEvent) bluetoothDeviceEvent).getRegion();
            beaconsMap.putMap("region", _createMapWithRegion(enteredRegion));
        }

        // for details about event types see
        // http://kontaktio.github.io/kontakt-android-sdk/2.1.0/Javadoc/com/kontakt/sdk/android/ble/discovery/EventType.html#DEVICE_DISCOVERED
        switch (bluetoothDeviceEvent.getEventType()) {
            case SPACE_ENTERED:
                Log.d(TAG, "namespace or region entered");

                sendEvent(context, "regionDidEnter", beaconsMap);

                break;
            case DEVICE_DISCOVERED:
                Log.d(TAG, "found new beacon");

                // Array length should be 1 according to Kontakt.io documentation
                if (bluetoothDeviceList.size() > 0) {
//                    beaconsMap.putMap("beacon", _createMapWithIBeacon(iBeaconDeviceList.get(0)));
                    beaconsMap.putMap("beacon", _createMapWithBeacon(bluetoothDeviceList.get(0), deviceProfile));
                    sendEvent(context, "beaconDidAppear", beaconsMap);
                }

                break;
            case DEVICES_UPDATE:
                Log.d(TAG, "updated beacons");

                if (bluetoothDeviceList.size() > 0) {

                    // Beacons
//                    beaconsMap.putArray("beacons", _createArrayWithIBeacons(iBeaconDeviceList));
                    beaconsMap.putArray("beacons", _createArrayWithBeacons(bluetoothDeviceList, deviceProfile));

                    // send Event
                    sendEvent(context, "beaconsDidRange", beaconsMap);

                }

                break;
            case DEVICE_LOST:
                Log.d(TAG, "lost device");

                // Array length should be 1 according to Kontakt.io documentation
                if (bluetoothDeviceList.size() > 0) {
//                    beaconsMap.putMap("beacon", _createMapWithIBeacon(iBeaconDeviceList.get(0)));
                    beaconsMap.putMap("beacon", _createMapWithBeacon(bluetoothDeviceList.get(0), deviceProfile));
                    sendEvent(context, "beaconDidDisappear", beaconsMap);
                }

                break;
            case SPACE_ABANDONED:
                Log.d(TAG, "namespace or region abandoned");

                sendEvent(context, "regionDidExit", beaconsMap);
                break;
        }

    }

    /**
     * Creates an array with all beacons in iBeaconDeviceList
     * @param iBeaconDeviceList List of beacons
     * @return
     */
    private WritableArray _createArrayWithIBeacons(List<? extends IBeaconDevice> iBeaconDeviceList) {
        WritableArray beaconArray = new WritableNativeArray();
        for (IBeaconDevice beacon : iBeaconDeviceList) {
            beaconArray.pushMap(_createMapWithIBeacon(beacon));
        }

        return beaconArray;
    }

    private WritableArray _createArrayWithBeacons(List<? extends RemoteBluetoothDevice> beaconDeviceList, DeviceProfile deviceProfile) {
        WritableArray beaconArray = new WritableNativeArray();
        for (RemoteBluetoothDevice beacon : beaconDeviceList) {
            beaconArray.pushMap(_createMapWithBeacon(beacon, deviceProfile));
        }

        return beaconArray;
    }

    /**
     * Creates a map with parameters to send to JS
     * @param beacon iBeacon device
     * @return
     */
    private WritableMap _createMapWithIBeacon(IBeaconDevice beacon) {
        WritableMap b = new WritableNativeMap();
        b.putString("name", beacon.getName());
        b.putString("uuid", String.valueOf(beacon.getProximityUUID()));
        b.putInt("major", beacon.getMajor());
        b.putInt("minor", beacon.getMinor());
        b.putDouble("rssi", beacon.getRssi());
        b.putString("proximity", String.valueOf(beacon.getProximity()));

        // Kontakt.io beacon stuff
        b.putDouble("distance", beacon.getDistance());
        b.putInt("batteryPower", beacon.getBatteryPower());
        b.putInt("txPower", beacon.getTxPower());
        b.putString("firmwareVersion", beacon.getFirmwareVersion());
        b.putString("uniqueID", beacon.getUniqueId());  // unique 4-digit code on backside of beacon

        return b;
    }

    private WritableMap _createMapWithBeacon(RemoteBluetoothDevice beacon, DeviceProfile deviceProfile) {

        WritableMap b = new WritableNativeMap();

        // general
        b.putString("name", beacon.getName());
        b.putString("address", beacon.getAddress());
        b.putDouble("rssi", beacon.getRssi());
        b.putString("proximity", String.valueOf(beacon.getProximity()));

        // Kontakt.io beacon stuff
        b.putDouble("distance", beacon.getDistance());
        b.putInt("batteryPower", beacon.getBatteryPower());
        b.putInt("txPower", beacon.getTxPower());
        b.putString("firmwareVersion", beacon.getFirmwareVersion());
        b.putString("uniqueID", beacon.getUniqueId());  // unique 4-digit code on backside of beacon
//        b.putInt("password", beacon.getPassword());

        // only iBeacon
        if (DeviceProfile.IBEACON == deviceProfile) {
            IBeaconDevice iBeacon = (IBeaconDevice) beacon;

            b.putString("uuid", String.valueOf(iBeacon.getProximityUUID()));
            b.putInt("major", iBeacon.getMajor());
            b.putInt("minor", iBeacon.getMinor());
        }
        // only Eddystone
        else if (DeviceProfile.EDDYSTONE == deviceProfile) {
            EddystoneDevice eddystoneBeacon = (EddystoneDevice) beacon;

            b.putString("instanceId", eddystoneBeacon.getInstanceId());
            b.putString("namespaceId", eddystoneBeacon.getNamespaceId());
            b.putString("url", eddystoneBeacon.getUrl());

            b.putDouble("temperature", eddystoneBeacon.getTemperature());
            b.putInt("telemetryVersion", eddystoneBeacon.getTelemetryVersion());
            b.putInt("batteryVoltage", eddystoneBeacon.getBatteryVoltage());
            b.putInt("timeSincePowerUp", eddystoneBeacon.getTimeSincePowerUp());
        }

        return b;
    }

    /**
     * Creates a map with parameters to send to JS
     * @param region iBeaconRegion
     * @return
     */
    private WritableMap _createMapWithRegion(IBeaconRegion region) {
        WritableMap regionMap = Arguments.createMap();
        regionMap.putString("identifier", region.getIdentifier());
        regionMap.putString("uuid", String.valueOf(region.getProximity()));
        regionMap.putInt("major", region.getMajor());
        regionMap.putInt("minor", region.getMinor());

        return regionMap;
    }

}
