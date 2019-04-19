package com.artirigo.kontaktio;

import com.facebook.react.bridge.Promise;
import com.facebook.react.bridge.ReactMethod;

import com.kontakt.sdk.android.ble.manager.ProximityManager;

public class ScanManager {
    private ProximityManager proximityManager;

    ScanManager(ProximityManager proximityManager) {
        this.proximityManager = proximityManager;
    }

    void startScanning(Promise promise) {
        try {
            if (proximityManager.isConnected()) {
                proximityManager.startScanning();
            } else {
                promise.reject("Did you forget to call connect() or did the connect() call fail? The beacon manager is not connected.");
            }
            promise.resolve(null);
        } catch (Exception e) {
            promise.reject(Constants.EXCEPTION, e);
        }
    }

    void stopScanning(Promise promise) {
        try {
            if (proximityManager.isScanning()) {
                proximityManager.stopScanning();
                promise.resolve(null);
            } else {
                promise.reject("Cannot stop scanning because device is currently not scanning.");
            }
        } catch (Exception e) {
            promise.reject(Constants.EXCEPTION, e);
        }
    }

    void restartScanning(Promise promise) {
        try {
            if (proximityManager.isScanning()) {
                proximityManager.restartScanning();
            } else {
                if (proximityManager.isConnected()) {
                    proximityManager.startScanning();
                } else {
                    promise.reject("Did you forget to call connect() or did the connect() call fail? The beacon manager is not connected.");
                }
            }
            promise.resolve(null);
        } catch (Exception e) {
            promise.reject(Constants.EXCEPTION, e);
        }
    }

    void isScanning(Promise promise) {
        try {
            if (proximityManager != null) {
                boolean isScanning = proximityManager.isScanning();
                promise.resolve(isScanning);
            } else {
                promise.resolve(false);
            }
        } catch (Exception e) {
            promise.reject(Constants.EXCEPTION, e);
        }
    }
}
