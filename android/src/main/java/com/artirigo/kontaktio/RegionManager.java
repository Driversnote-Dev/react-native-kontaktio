package com.artirigo.kontaktio;

import com.facebook.react.bridge.Promise;
import com.facebook.react.bridge.ReadableArray;
import com.facebook.react.bridge.ReadableMap;
import com.facebook.react.bridge.ReadableType;

import com.kontakt.sdk.android.ble.device.BeaconRegion;
import com.kontakt.sdk.android.ble.device.EddystoneNamespace;
import com.kontakt.sdk.android.ble.manager.ProximityManager;
import com.kontakt.sdk.android.common.KontaktSDK;
import com.kontakt.sdk.android.common.profile.IBeaconRegion;
import com.kontakt.sdk.android.common.profile.IEddystoneNamespace;


import java.util.ArrayList;
import java.util.Collection;
import java.util.UUID;

/**
 * Add new (sets of) regions/namespaces to a ProximityManager
 */
class RegionManager {

    private ProximityManager proximityManager;

    RegionManager(ProximityManager proximityManager) {
        this.proximityManager = proximityManager;
    }

    void setBeaconRegion(ReadableMap regionParams, Promise promise) {
        try {
            IBeaconRegion region;

            if (regionParams == null) {
                region = BeaconRegion.EVERYWHERE;
            } else {
                region = createRegion(regionParams);
            }

            addBeaconRegion(region);
            promise.resolve(null);
        } catch (Exception e) {
            promise.reject(Constants.EXCEPTION, e);
        }
    }

    void setBeaconRegions(ReadableArray regionsParams, Promise promise) {
        try {
            if (regionsParams == null || regionsParams.size() <= 0) {
                IBeaconRegion region = BeaconRegion.EVERYWHERE;
                addBeaconRegion(region);
                promise.resolve(null);
            } else {
                if (regionsParams.size() == 1 && !regionsParams.isNull(0)) {
                    if (regionsParams.getType(0) == ReadableType.Map) {
                        setBeaconRegion(regionsParams.getMap(0), promise);
                    } else {
                        throw new Exception("The single region in your array of regions is not a proper Javascript object");
                    }
                } else {
                    Collection<IBeaconRegion> beaconRegions = new ArrayList<>();

                    for (int j = 0; j < regionsParams.size(); j++) {
                        if (!regionsParams.isNull(j) && regionsParams.getType(j) == ReadableType.Map) {
                            ReadableMap regionParams = regionsParams.getMap(j);
                            IBeaconRegion region = createRegion(regionParams);
                            beaconRegions.add(region);
                        } else {
                            throw new Exception("At least one region in the array of regions is not a proper Javascript object");
                        }
                    }
                    addBeaconRegions(beaconRegions);
                    promise.resolve(null);
                }
            }
        } catch (Exception e) {
            promise.reject(Constants.EXCEPTION, e);
        }
    }

    /**
      * Build beacon region from incoming data
      * @param regionParams
      * @return
      */
    private IBeaconRegion createRegion(ReadableMap regionParams) throws Exception {
        String identifier = "NO_IDENTIFIER";
        String uuid = String.valueOf(KontaktSDK.DEFAULT_KONTAKT_BEACON_PROXIMITY_UUID);
        int major = BeaconRegion.ANY_MAJOR;
        int minor = BeaconRegion.ANY_MINOR;
        IBeaconRegion region;

        if (regionParams.hasKey("identifier")) {
            if (!regionParams.isNull("identifier") && (regionParams.getType("identifier") == ReadableType.String)) {
                identifier = regionParams.getString("identifier");
            } else {
                throw new Exception("identifier has to be of type String");
            }
        }

        if (regionParams.hasKey("uuid")) {
            if (!regionParams.isNull("uuid") && (regionParams.getType("uuid") == ReadableType.String)) {
                uuid = regionParams.getString("uuid");
            } else {
                throw new Exception("uuid has to be of type String");
            }
        }

        if (regionParams.hasKey("major")) {
            if (!regionParams.isNull("major") && (regionParams.getType("major") == ReadableType.Number)) {
                major = regionParams.getInt("major");
            } else {
                throw new Exception("major has to be of type int");
            }
        }

        if (regionParams.hasKey("minor")) {
            if (!regionParams.isNull("minor") && (regionParams.getType("minor") == ReadableType.Number)) {
                minor = regionParams.getInt("minor");
            } else {
                throw new Exception("minor has to be of type int");
            }
        }

        region = new BeaconRegion.Builder()
                .identifier(identifier)
                .proximity(UUID.fromString(uuid))
                .major(major)
                .minor(minor)
                .build();

        return region;
    }

    private void addBeaconRegion(IBeaconRegion region) {
        proximityManager.spaces().iBeaconRegion(region);
    }

    private void addBeaconRegions(Collection<IBeaconRegion> beaconRegions) {
        proximityManager.spaces().iBeaconRegions(beaconRegions);
    }

    /**
     * Retrive currently scanned regions
     */
    void getBeaconRegions() {
        // The function getIBeaconRegions() in the ScanContext class has to be used
        // but currently the scanContext is not exposed by ProximityManagerImpl class,
        // only the ScanContext.builder exists there as a private field.
    }

    void setEddystoneNamespace(ReadableMap namespaceParams, Promise promise) {
        try {
            IEddystoneNamespace namespace;

            if (namespaceParams == null) {
                namespace = EddystoneNamespace.EVERYWHERE;
            } else {
                namespace = createEddystoneNamespace(namespaceParams);
            }

            addEddystoneNamespace(namespace);
            promise.resolve(null);
        } catch (Exception e) {
            promise.reject(Constants.EXCEPTION, e);
        }
    }

    /*
     * Eddystone namespace creator
     */
    IEddystoneNamespace createEddystoneNamespace(ReadableMap namespaceParams) throws Exception {
        String identifier = "Everywhere";
        String namespaceName = KontaktSDK.DEFAULT_KONTAKT_NAMESPACE_ID;
        String secureNamespace = null;
        String instanceId = EddystoneNamespace.ANY_INSTANCE_ID;
        IEddystoneNamespace namespace;

        if (namespaceParams.hasKey("identifier")) {
            if (!namespaceParams.isNull("identifier") && (namespaceParams.getType("identifier") == ReadableType.String)) {
                identifier = namespaceParams.getString("identifier");
            } else {
                throw new Exception("identifier has to be of type String");
            }
        }

        if (namespaceParams.hasKey("namespace")) {
            if (!namespaceParams.isNull("namespace") && (namespaceParams.getType("namespace") == ReadableType.String)) {
                namespaceName = namespaceParams.getString("namespace");
            } else {
                throw new Exception("namespace has to be of type String");
            }
        }

        if (namespaceParams.hasKey("secureNamespace")) {
            if (!namespaceParams.isNull("secureNamespace") && (namespaceParams.getType("secureNamespace") == ReadableType.String)) {
                secureNamespace = namespaceParams.getString("secureNamespace");
            } else {
                throw new Exception("secureNamespace has to be of type String");
            }
        }

        if (namespaceParams.hasKey("instanceId")) {
            if (!namespaceParams.isNull("instanceId") && (namespaceParams.getType("instanceId") == ReadableType.String)) {
                instanceId = namespaceParams.getString("instanceId");
            } else {
                throw new Exception("instanceId has to be of type String");
            }
        }

        namespace = new EddystoneNamespace.Builder()
                .identifier(identifier)
                .namespace(namespaceName)
                .secureNamespace(secureNamespace)
                .instanceId(instanceId)
                .build();

        return namespace;
    }

    private void addEddystoneNamespace(IEddystoneNamespace namespace) {
        proximityManager.spaces().eddystoneNamespace(namespace);
    }

    private void addEddystoneNamespaces(Collection<IEddystoneNamespace> namespaces) {
        proximityManager.spaces().eddystoneNamespaces(namespaces);
    }
}
