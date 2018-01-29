//
//  KontaktSDK
//  Version: 1.5.1
//
//  Copyright © 2017 Kontakt.io. All rights reserved.
//

@import Foundation;

#import "KTKDeviceDefinitions.h"

#pragma mark -
typedef struct {
    uint8_t x;
    uint8_t y;
    uint8_t z;
} KTKAcceleration;

typedef NS_OPTIONS(NSUInteger, KTKNearbyDeviceTelemetryError) {
    /**
     *  Internal error, Gateway does not operate correctly, other flags can be cleared despite errors occur.
     */
    KTKNearbyDeviceTelemetryErrorInternal      = 1 << 0,
    /**
     *  No Internet Connection
     */
    KTKNearbyDeviceTelemetryErrorNoInternet    = 1 << 1
};

NS_ASSUME_NONNULL_BEGIN

#pragma mark - KTKNearbyDeviceTelemetry (Interface)
@interface KTKNearbyDeviceTelemetry : NSObject <NSCopying>

#pragma mark - Basic System Health
///--------------------------------------------------------------------
/// @name Basic System Health
///--------------------------------------------------------------------

/**
 *  The current value of real time clock. (read-only)
 */
@property (nonatomic, readonly, copy) NSDate * _Nullable date;

/**
 *  Battery level percentage. (read-only)
 */
@property (nonatomic, readonly, copy) NSNumber * _Nullable batteryLevel;

#pragma mark - More System Health
///--------------------------------------------------------------------
/// @name More System Health
///--------------------------------------------------------------------

/**
 *  Uptime rounded to hours. (read-only)
 */
@property (nonatomic, readonly, copy) NSNumber * _Nullable uptime;

/**
 *  Percentage of system load average over 15 min. (read-only)
 */
@property (nonatomic, readonly, copy) NSNumber * _Nullable systemLoad;

/**
 *  Error Flags. (read-only)
 */
@property (nonatomic, readonly, assign) KTKNearbyDeviceTelemetryError errors;

#pragma mark - Accelerometer
///--------------------------------------------------------------------
/// @name Accelerometer
///--------------------------------------------------------------------

/**
 *  Accelerometer sensitivity. Unit: mg/digit. (read-only)
 */
@property (nonatomic, readonly, copy) NSNumber * _Nullable sensitivity;

/**
 *  Raw Accelerometer data filtered with lowpass filter. (read-only)
 */
@property (nonatomic, readonly, assign) KTKAcceleration acceleration;

/**
 *  Seconds since last doubletap event. Doubletap event occurs when doubletap pattern is detected by accelerometer. (read-only)
 *
 *  Saturates on 65535 (0xFFFF) value. 65535 (0xFFFF) default value when Doubletap is disabled.
 */
@property (nonatomic, readonly, copy) NSNumber * _Nullable lastDoubleTap;

/**
 *  Seconds since last threshold event. Threshold event occurs when acceleration exceeds configured threshold. (read-only)
 *
 *  Saturates on 65535 (0xFFFF) value. 65535 (0xFFFF) default value when Doubletap is disabled.
 */
@property (nonatomic, readonly, copy) NSNumber * _Nullable lastThreshold;

#pragma mark - Sensors
///--------------------------------------------------------------------
/// @name Sensors
///--------------------------------------------------------------------

/**
 *  Light Sensor Percentage (0-100). (read-only)
 */
@property (nonatomic, readonly, copy) NSNumber * _Nullable lightSensor;

/**
 *  Temperature in degree Celsius. (read-only)
 */
@property (nonatomic, readonly, copy) NSNumber * _Nullable temperature;

#pragma mark - Scanning
///--------------------------------------------------------------------
/// @name Scanning
///--------------------------------------------------------------------

/**
 *  0 | Exactly zero scans over last 10 seconds
 *  0-249 | Rounded number of scans/s.
 *  250 | 250 or more scans/s
 *  251 | 0.1 - 0.2 scans/s
 *  252 | 0.3 - 0.4 scans/s
 *  253 | 0.5 - 0.6 scans/s
 *  254 | 0.7 - 0.8 scans/s
 */

/**
 *  BLE scanning statistics. Scans/s, 10 seconds average. (read-only)
 */
@property (nonatomic, readonly, copy) NSNumber * _Nullable bleScans;

/**
 *  Number of scanned BLE devices. 10 seconds average. (read-only)
 */
@property (nonatomic, readonly, copy) NSNumber * _Nullable bleDevices;

/**
 *  WiFi scanning statistics. Scans/s, 10 seconds average. (read-only)
 */
@property (nonatomic, readonly, copy) NSNumber * _Nullable wifiScans;


@end

NS_ASSUME_NONNULL_END
