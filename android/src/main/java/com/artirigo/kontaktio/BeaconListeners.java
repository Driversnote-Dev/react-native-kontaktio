package com.artirigo.kontaktio;

import android.util.Log;

import com.facebook.react.bridge.Arguments;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.WritableArray;
import com.facebook.react.bridge.WritableMap;
import com.facebook.react.bridge.WritableNativeArray;
import com.facebook.react.bridge.WritableNativeMap;

import com.kontakt.sdk.android.ble.exception.ScanError;
import com.kontakt.sdk.android.ble.manager.listeners.EddystoneListener;
import com.kontakt.sdk.android.ble.manager.listeners.IBeaconListener;
import com.kontakt.sdk.android.ble.manager.listeners.ScanStatusListener;
import com.kontakt.sdk.android.ble.manager.listeners.SpaceListener;
import com.kontakt.sdk.android.ble.spec.Telemetry;
import com.kontakt.sdk.android.common.profile.IBeaconDevice;
import com.kontakt.sdk.android.common.profile.IBeaconRegion;
import com.kontakt.sdk.android.common.profile.IEddystoneDevice;
import com.kontakt.sdk.android.common.profile.IEddystoneNamespace;
import com.kontakt.sdk.android.common.profile.RemoteBluetoothDevice;

import java.util.List;

import static com.artirigo.kontaktio.ReactUtils.sendEvent;

/**
 * Add Listeners to a ProximityManager
 */
final class BeaconListeners {

    private final ReactApplicationContext reactAppContext;
    private WritableMap outputMap;

    BeaconListeners(ReactApplicationContext reactAppContext) {
        this.reactAppContext = reactAppContext;
        this.outputMap = Arguments.createMap();
    }

    IBeaconListener createIBeaconListener() {
        return new IBeaconListener() {
            @Override
            public void onIBeaconDiscovered(IBeaconDevice iBeacon, IBeaconRegion region) {
                //Beacon discovered
                Log.i("IBeaconListener", "IBeacon discovered: " + iBeacon.toString() + ", belongs to region " + region.toString());
                outputMap = Arguments.createMap();
                outputMap.putMap("beacon", createMapWithIBeacon(iBeacon));
                outputMap.putMap("region", createMapWithRegion(region));
                sendEvent(reactAppContext, "beaconDidAppear", outputMap);
            }

            @Override
            public void onIBeaconsUpdated(List<IBeaconDevice> iBeacons, IBeaconRegion region) {
                //Beacons updated
                Log.i("IBeaconListener", "IBeacons updated: " + iBeacons.toString() + ", belongs to region " + region.toString());
                outputMap = Arguments.createMap();
                outputMap.putArray("beacons", createArrayWithIBeacons(iBeacons));
                outputMap.putMap("region", createMapWithRegion(region));
                sendEvent(reactAppContext, "beaconsDidRange", outputMap);
            }

            @Override
            public void onIBeaconLost(IBeaconDevice iBeacon, IBeaconRegion region) {
                //Beacon lost
                Log.i("IBeaconListener", "IBeacon lost: " + iBeacon.toString() + ", belongs to region " + region.toString());
                outputMap = Arguments.createMap();
                outputMap.putMap("beacon", createMapWithIBeacon(iBeacon));
                outputMap.putMap("region", createMapWithRegion(region));
                sendEvent(reactAppContext, "beaconDidDisappear", outputMap);
            }
        };
    }

    EddystoneListener createEddystoneListener() {
        return new EddystoneListener() {
            @Override
            public void onEddystoneDiscovered(IEddystoneDevice eddystone, IEddystoneNamespace namespace) {
                //Eddystone discovered
                Log.i("EddystoneListener", "Eddystone discovered: " + eddystone.toString());
                outputMap = Arguments.createMap();
                outputMap.putMap("eddystone", createMapWithEddystone(eddystone));
                outputMap.putMap("namespace", createMapWithNamespace(namespace));
                sendEvent(reactAppContext, "eddystoneDidAppear", outputMap);
            }

            @Override
            public void onEddystonesUpdated(List<IEddystoneDevice> eddystones, IEddystoneNamespace namespace) {
                //Eddystone updated
                Log.i("EddystoneListener", "Eddystones updated: " + eddystones.toString());
                outputMap = Arguments.createMap();
                outputMap.putArray("eddystones", createArrayWithEddystones(eddystones));
                outputMap.putMap("namespace", createMapWithNamespace(namespace));
                sendEvent(reactAppContext, "eddystoneDidRange", outputMap);
            }

            @Override
            public void onEddystoneLost(IEddystoneDevice eddystone, IEddystoneNamespace namespace) {
                //Eddystone lost
                Log.i("EddystoneListener", "Eddystone lost: " + eddystone.toString());
                outputMap = Arguments.createMap();
                outputMap.putMap("eddystone", createMapWithEddystone(eddystone));
                outputMap.putMap("namespace", createMapWithNamespace(namespace));
                sendEvent(reactAppContext, "eddystoneDidDisappear", outputMap);
            }
        };
    }

    SpaceListener createSpaceListener() {
        return new SpaceListener() {
            @Override
            public void onRegionEntered(IBeaconRegion region) {
                //IBeacon region has been entered
                Log.i("SpaceListener", "region entered: " + region.toString());
                outputMap = Arguments.createMap();
                outputMap.putMap("region", createMapWithRegion(region));
                sendEvent(reactAppContext, "regionDidEnter", outputMap);
            }

            @Override
            public void onRegionAbandoned(IBeaconRegion region) {
                //IBeacon region has been abandoned
                Log.i("SpaceListener", "region abandoned: " + region.toString());
                outputMap = Arguments.createMap();
                outputMap.putMap("region", createMapWithRegion(region));
                sendEvent(reactAppContext, "regionDidExit", outputMap);
            }

            @Override
            public void onNamespaceEntered(IEddystoneNamespace namespace) {
                //Eddystone namespace has been entered
                Log.i("SpaceListener", "namespace entered: " + namespace.toString());
                outputMap = Arguments.createMap();
                outputMap.putMap("namespace", createMapWithNamespace(namespace));
                sendEvent(reactAppContext, "namespaceDidEnter", outputMap);
            }

            @Override
            public void onNamespaceAbandoned(IEddystoneNamespace namespace) {
                //Eddystone namespace has been abandoned
                Log.i("SpaceListener", "namespace abandoned: " + namespace.toString());
                outputMap = Arguments.createMap();
                outputMap.putMap("namespace", createMapWithNamespace(namespace));
                sendEvent(reactAppContext, "namespaceDidExit", outputMap);
            }
        };
    }

    ScanStatusListener createScanStatusListener() {
        return new ScanStatusListener() {
            @Override
            public void onScanStart() {
                //Scan started
                Log.i("ScanStatusListener", "scan started");
                WritableMap map = Arguments.createMap();
                map.putString("status", "START");
                sendEvent(reactAppContext, "scanStatus", map);
            }

            @Override
            public void onScanStop() {
                //Scan stopped
                // THIS IS NOT TRIGGERED!
                Log.i("ScanStatusListener", "scan stopped");
                WritableMap map = Arguments.createMap();
                map.putString("status", "STOP");
                sendEvent(reactAppContext, "scanStatus", map);
            }

            @Override
            public void onScanError(ScanError error) {
                //Error occured
                // Invoked if an error occurs during a scan or scan initialization.
                Log.i("ScanStatusListener", "scan error occured: " + error);
                WritableMap map = Arguments.createMap();
                map.putString("status", "ERROR");
                sendEvent(reactAppContext, "scanStatus", map);
            }

            /**
             * THIS IS THE REAL BEACON MONITORING
             */

            @Override
            public void onMonitoringCycleStart() {
                //Monitoring cycle started
                Log.i("ScanStatusListener", "monitoring cycle started");
                WritableMap map = Arguments.createMap();
                map.putString("status", "START");
                sendEvent(reactAppContext, "monitoringCycle", map);
            }

            @Override
            public void onMonitoringCycleStop() {
                //Monitoring cycle finished
                Log.i("ScanStatusListener", "monitoring cycle finished");
                WritableMap map = Arguments.createMap();
                map.putString("status", "STOP");
                sendEvent(reactAppContext, "monitoringCycle", map);
            }
        };
    }


    /*
     * Helpers
     */

    /**
     * Creates a map with parameters to send to JS
     * @param beacon iBeaconDevice
     * @return
     */
    private WritableMap createMapWithIBeacon(IBeaconDevice beacon) {
        WritableMap b = new WritableNativeMap();
        b.putString("name", beacon.getName());
        b.putString("address", beacon.getAddress());
        b.putDouble("rssi", beacon.getRssi());
        b.putString("proximity", String.valueOf(beacon.getProximity()));

        // iBeacon
        b.putString("uuid", String.valueOf(beacon.getProximityUUID()));
        b.putInt("major", beacon.getMajor());
        b.putInt("minor", beacon.getMinor());

        // Kontakt.io specific
        b.putDouble("accuracy", beacon.getDistance());
        b.putInt("batteryPower", beacon.getBatteryPower());
        b.putInt("txPower", beacon.getTxPower());
        b.putString("firmwareVersion", beacon.getFirmwareVersion());
        b.putString("uniqueId", beacon.getUniqueId());  // unique 4-digit code on backside of beacon
        b.putBoolean("isShuffled", beacon.isShuffled());

        return b;
    }

    /**
     * Creates a map with parameters to send to JS
     * @param eddystone IEddystoneDevice
     * @return
     */
    private WritableMap createMapWithEddystone(IEddystoneDevice eddystone) {
        WritableMap b = new WritableNativeMap();
        b.putString("name", eddystone.getName());
        b.putString("address", eddystone.getAddress());
        b.putDouble("rssi", eddystone.getRssi());
        b.putString("proximity", String.valueOf(eddystone.getProximity()));

        // Eddystone
        b.putString("namespace", eddystone.getNamespace());
        b.putString("instanceId", eddystone.getInstanceId());
        b.putString("url", eddystone.getUrl());
        b.putString("eid", eddystone.getEid());
        b.putString("encryptedTelemetry", eddystone.getEncryptedTelemetry());
        // Telemetry
        Telemetry telemetry = eddystone.getTelemetry();
        WritableMap t = new WritableNativeMap();
        t.putDouble("batteryVoltage", telemetry.getBatteryVoltage());
        t.putDouble("temperature", telemetry.getTemperature());
        t.putInt("pduCount", telemetry.getPduCount());
        t.putInt("timeSincePowerUp", telemetry.getTimeSincePowerUp());
        t.putInt("version", telemetry.getVersion());
        b.putMap("telemetry", t);

        // Kontakt.io specific
        b.putDouble("accuracy", eddystone.getDistance());
        b.putInt("batteryPower", eddystone.getBatteryPower());
        b.putInt("txPower", eddystone.getTxPower());
        b.putString("firmwareVersion", eddystone.getFirmwareVersion());
        b.putString("uniqueId", eddystone.getUniqueId());  // unique 4-digit code on backside of beacon
        b.putBoolean("isShuffled", eddystone.isShuffled());

        return b;
    }

    /**
     * Creates a map with parameters to send to JS
     * @param region iBeaconRegion
     * @return
     */
    private WritableMap createMapWithRegion(IBeaconRegion region) {
        WritableMap regionMap = Arguments.createMap();
        regionMap.putString("identifier", region.getIdentifier());
        regionMap.putString("uuid", String.valueOf(region.getProximity()));
        regionMap.putString("secureUuid", String.valueOf(region.getSecureProximity()));
        regionMap.putInt("major", region.getMajor());
        regionMap.putInt("minor", region.getMinor());

        return regionMap;
    }

    /**
     * Creates a map with parameters to send to JS
     * @param region IEddystoneNamespace
     * @return
     */
    private WritableMap createMapWithNamespace(IEddystoneNamespace namespace) {
        WritableMap namespaceMap = Arguments.createMap();
        namespaceMap.putString("identifier", namespace.getIdentifier());
        namespaceMap.putString("namespace", namespace.getNamespace());
        namespaceMap.putString("secureNamespace", namespace.getSecureNamespace());
        namespaceMap.putString("instanceId", namespace.getInstanceId());

        return namespaceMap;
    }

    /**
     * Creates an array with all beacons in iBeaconDeviceList
     * @param iBeaconDeviceList List of beacons
     * @return
     */
    private WritableArray createArrayWithIBeacons(List<IBeaconDevice> iBeaconDeviceList) {
        WritableArray beaconArray = new WritableNativeArray();
        for (IBeaconDevice beacon : iBeaconDeviceList) {
            beaconArray.pushMap(createMapWithIBeacon(beacon));
        }

        return beaconArray;
    }

    /**
     * Creates an array with all eddystones in iEddystoneDeviceList
     * @param iEddystoneDeviceList List of eddystones
     * @return
     */
    private WritableArray createArrayWithEddystones(List<IEddystoneDevice> iEddystoneDeviceList) {
        WritableArray beaconArray = new WritableNativeArray();
        for (IEddystoneDevice eddystone : iEddystoneDeviceList) {
            beaconArray.pushMap(createMapWithEddystone(eddystone));
        }

        return beaconArray;
    }


//    private WritableMap createMapWithBeacon(RemoteBluetoothDevice beacon, DeviceProfile deviceProfile) {
//
//        WritableMap b = new WritableNativeMap();
//
//        // general
//        b.putString("name", beacon.getName());
//        b.putString("address", beacon.getAddress());
//        b.putDouble("rssi", beacon.getRssi());
//        b.putString("proximity", String.valueOf(beacon.getProximity()));
//
//        // Kontakt.io beacon stuff
//        b.putDouble("accuracy", beacon.getDistance());
//        b.putInt("batteryPower", beacon.getBatteryPower());
//        b.putInt("txPower", beacon.getTxPower());
//        b.putString("firmwareVersion", beacon.getFirmwareVersion());
//        b.putString("uniqueID", beacon.getUniqueId());  // unique 4-digit code on backside of beacon
////        b.putInt("password", beacon.getPassword());
//
//        // only iBeacon
//        if (DeviceProfile.IBEACON == deviceProfile) {
//            IBeaconDevice iBeacon = (IBeaconDevice) beacon;
//
//            b.putString("uuid", String.valueOf(iBeacon.getProximityUUID()));
//            b.putInt("major", iBeacon.getMajor());
//            b.putInt("minor", iBeacon.getMinor());
//        }
//        // only Eddystone
//        else if (DeviceProfile.EDDYSTONE == deviceProfile) {
//            EddystoneDevice eddystoneBeacon = (EddystoneDevice) beacon;
//
//            b.putString("instanceId", eddystoneBeacon.getInstanceId());
//            b.putString("namespaceId", eddystoneBeacon.getNamespaceId());
//            b.putString("url", eddystoneBeacon.getUrl());
//
//            b.putDouble("temperature", eddystoneBeacon.getTemperature());
//            b.putInt("telemetryVersion", eddystoneBeacon.getTelemetryVersion());
//            b.putInt("batteryVoltage", eddystoneBeacon.getBatteryVoltage());
//            b.putInt("timeSincePowerUp", eddystoneBeacon.getTimeSincePowerUp());
//        }
//
//        return b;
//    }

//    private WritableArray createArrayWithBeacons(List<? extends RemoteBluetoothDevice> beaconDeviceList, DeviceProfile deviceProfile) {
//        WritableArray beaconArray = new WritableNativeArray();
//        for (RemoteBluetoothDevice beacon : beaconDeviceList) {
//            beaconArray.pushMap(createMapWithBeacon(beacon, deviceProfile));
//        }
//
//        return beaconArray;
//    }

}
