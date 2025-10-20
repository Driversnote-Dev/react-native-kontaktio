//
//  KontaktSDK
//  Version: 3.1.0
//
//  Copyright © 2017 Kontakt.io. All rights reserved.
//

@import Foundation;

#import "KTKDeviceDefinitions.h"
#import "KTKPersonPosition.h"

typedef NS_OPTIONS(uint16_t, KTKNearbyDeviceTelemetryError) {
    /**
     *  No Internet Connection
     */
    KTKNearbyDeviceTelemetryErrorNoInternet    = 1 << 15
};

typedef NS_ENUM(uint8_t, KTKDeviceDataLoggerStatus) {
    KTKDeviceDataLoggerStatusUnavailable = 0,
    KTKDeviceDataLoggerStatusDisabled,
    KTKDeviceDataLoggerStatusEnabled,
};

/**
 *  A device gas typ fields.
 */
typedef NS_OPTIONS(uint8_t, KTKDeviceGasTypFields) {
    KTKDeviceGasTypGenericPPM                           = 0x00,
    KTKDeviceGasTypCarbonMonoxide                       = 0x01,
    KTKDeviceGasTypEthanol                              = 0x02,
    KTKDeviceGasTypVolatileOrganicCompounds             = 0x03,
    KTKDeviceGasTypPM1_0                                = 0x04,
    KTKDeviceGasTypPM2_5                                = 0x05,
    KTKDeviceGasTypPM10_0                               = 0x06,
    KTKDeviceGasTypCarbonDioxide                        = 0x07,
    KTKDeviceGasTypGasResistance                        = 0x08
};

/**
 *  A device Status Soapfields.
 */
typedef NS_OPTIONS(uint8_t, KTKDeviceStatusSoapFields) {
    KTKDeviceStatusSoapFieldsNoEOS                  = 1 << 0,
    KTKDeviceStatusSoapFieldsNoEkeyCommunication    = 1 << 1,
    KTKDeviceStatusSoapFieldsWrongEkey              = 1 << 2,
    KTKDeviceStatusSoapFieldsIncomplete             = 1 << 3,
    KTKDeviceStatusSoapFieldsLowBackupBattery       = 1 << 4,
    KTKDeviceStatusSoapFieldsFaultDue               = 1 << 5,
    KTKDeviceStatusSoapFieldsLowRefill              = 1 << 6,
    KTKDeviceStatusSoapFieldsLockoutStatus          = 1 << 7,
};


NS_ASSUME_NONNULL_BEGIN

#pragma mark - KTKNearbyDeviceTelemetry (Interface)
@interface KTKNearbyDeviceTelemetry : NSObject <NSCopying>

#pragma mark - Identification
///--------------------------------------------------------------------
/// @name Identification
///--------------------------------------------------------------------

@property (nonatomic, readonly, copy) NSString * _Nullable uniqueID;


@property (nonatomic, readonly, copy) NSNumber * _Nullable channel;

#pragma mark - Basic System Health
///--------------------------------------------------------------------
/// @name Basic System Health
///--------------------------------------------------------------------

/**
 *  Current RSSI value for the device. (read-only)
 */
@property (nonatomic, readonly, copy) NSNumber * _Nullable RSSI;

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
@property (nonatomic, readonly, assign) KTKDeviceAcceleration acceleration;

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

/**
 *  Index of current event. Wraps around. Used to identify each threshold event
 */
@property (nonatomic, readonly, copy) NSNumber * _Nullable movementID;

/**
 *  A Boolean moving or not. (read-only)
 */
@property (nonatomic, readonly, assign, getter=isMoving) BOOL moving;

#pragma mark - Vendor
///--------------------------------------------------------------------
/// @name Vendor
///--------------------------------------------------------------------

/**
 *  Index of current roomNumber. Detected room number via IR detector. 0xFFFF means unknown. After 60s from last detection
 *
 *  becomes again 0xFFFF
 */
@property (nonatomic, readonly, copy) NSNumber * _Nullable roomNumber;

/**
 *  Detected number of people in the room. 0xFF means invalid / unknown
 */
@property (nonatomic, readonly, copy) NSNumber * _Nullable occupancy;

/**
 *  Time since last detection. Saturates at 0xFFFF
 */
@property (nonatomic, readonly, copy) NSNumber * _Nullable detectionTime;

/**
 *  Index of the measurement/frame, starting at 0 0xFFFFFFFF means invalid / unknown
 */
@property (nonatomic, readonly, copy) NSNumber * _Nullable frameCount;

/**
 *  Detected number of people in Place the room. 0xFFFF means invalid / unknown
 */
@property (nonatomic, readonly, copy) NSNumber * _Nullable inCount;

/**
 *  Detected number of people out Place the room. 0xFFFF means invalid / unknown
 */
@property (nonatomic, readonly, copy) NSNumber * _Nullable outCount;

/**
 *  Detected number of people in the room for PDF. 0xFF means invalid / unknown
 */
@property (nonatomic, readonly, copy) NSNumber * _Nullable occupancyPDF;

/**
 *  Time since last detection for PDF. Saturates at 0xFFFF
 */
@property (nonatomic, readonly, copy) NSNumber * _Nullable detectionTimePDF;

/**
 *  Position in  Pixels of persons. (read-only)
 */
@property (nonatomic, readonly, copy) NSArray <KTKPersonPosition*>  * _Nullable personPositions;

#pragma mark - Button
///--------------------------------------------------------------------
/// @name Button
///--------------------------------------------------------------------

/**
 * Seconds since last Click event. Click event is specified in Button Specification Behavior. (read-only)
 *
 *  Saturates on 65535 (0xFFFF) value. 65535 (0xFFFF) default value when button click is disabled.
 */
@property (nonatomic, readonly, copy) NSNumber * _Nullable lastSingleClick;

/**
 * A number of Click events. Click event is specified in Button Specification Behavior. (read-only)
 */
@property (nonatomic, readonly, copy) NSNumber * _Nullable singleClickCount;

/**
 * A number of Click events. Click event is specified in Button id 1. (read-only)
 */
@property (nonatomic, readonly, copy) NSNumber * _Nullable clickId1Count;

/**
 * A number of Click events. Click event is specified in Button id 2. (read-only)
 */
@property (nonatomic, readonly, copy) NSNumber * _Nullable clickId2Count;

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

/**
 *  Relative Humidity Percentage (0-100). (read-only)
 */
@property (nonatomic, readonly, copy) NSNumber * _Nullable humidity;

/**
 *  States of GPIOs. (read-only)
 */
@property (nonatomic, readonly, assign) struct KTKNearbyDeviceGPIOStates GPIOStates;

/**
 *  Pressure in mBar. (read-only)
 */
@property (nonatomic, readonly, copy) NSNumber * _Nullable airPressuer;

/**
 *  Seconds since last PIR detection. Saturates at 0xFFFF. (read-only)
 */
@property (nonatomic, readonly, copy) NSNumber * _Nullable pirDetection;

/**
 *  Air quality, 0 for good - 255 bad. (read-only)
 */
@property (nonatomic, readonly, copy) NSNumber * _Nullable airQuality;

/**
 *  Measured distance in [cm]. (read-only)
 */
@property (nonatomic, readonly, copy) NSNumber * _Nullable distance;

/**
 *  Accurancy 0-100%. (read-only)
 */
@property (nonatomic, readonly, copy) NSNumber * _Nullable accuracy;

/**
 *  Gas type. (read-only)
 *  
 *  0x00 Generic ppm
 *  0x01 Carbon Monoxide ppm
 *  0x02 Ethanol Monoxide ppm
 *  0x03 Volatile Organic Compounds ppm
 *  0x04 PM 1.0 ug/m3
 *  0x05 PM 2.5 ug/m3
 *  0x06 PM 10.0 ug/m3
 *  0x07 Carbon Dioxide ppm
 *  0x08 Gas resistance kOhm
 */

@property (nonatomic, readonly, assign) KTKDeviceGasTypFields gasTypeFields;

/**
 *  Signed, 16-bit PPM concentration, can be a positive PPM, or a difference from baseline. (read-only)
 */
@property (nonatomic, readonly, copy) NSNumber * _Nullable gasPPM;

/**
 *  Unsigned, 16-bit light level measured in lux. (read-only)
 */
@property (nonatomic, readonly, copy) NSNumber * _Nullable lightLevelLux;


// Soap Dispenser
/**
 *  Serial number
 */
@property (nonatomic, readonly, copy) NSNumber * _Nullable serialNumber;

/**
 *  Charge
 */
@property (nonatomic, readonly, copy) NSNumber * _Nullable charge;

/**
 *  Activations (/1k)
 */
@property (nonatomic, readonly, copy) NSNumber * _Nullable activationsCount;

/**
 *  Activations (kontakt)
 */
@property (nonatomic, readonly, copy) NSNumber * _Nullable activationsKontakt;

/**
 *  Refills
 */
@property (nonatomic, readonly, copy) NSNumber * _Nullable refills;

/**
 *  Status
 */
@property (nonatomic, readonly, copy) NSNumber * _Nullable statusSoap;

/**
 *  Status Soap Fields (read-only)
 */
@property (nonatomic, readonly, assign) KTKDeviceStatusSoapFields statusSoapFields;

/**
 *  Config
 */
@property (nonatomic, readonly, copy) NSNumber * _Nullable configSoap;

/**
 *  Distributor
 */
@property (nonatomic, readonly, copy) NSNumber * _Nullable distributor;


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

///--------------------------------------------------------------------
/// @name RSSI scan
///--------------------------------------------------------------------

/**
 *  Scan ID - counter that identifies the current scan from the previous ones. (read-only)
 */
@property (nonatomic, readonly, copy) NSNumber * _Nullable scanID;

/**
 *  MAC address. (read-only)
 */
@property (nonatomic, readonly, copy) NSString * _Nullable mac;

/**
 *  RSSI values. Zero (0x00) if not present. The values are in chronological order, as they are scanned. Above 6 values, they are discarded.
 */
@property (nonatomic, readonly, copy) NSArray <NSNumber*>  * _Nullable rssiValues;



#pragma mark - Data Logger
///--------------------------------------------------------------------
/// @name Data Logger
///--------------------------------------------------------------------

/**
 *  A Boolean value indicating whether the data logger functionality is turned `ON`.
 */
@property (nonatomic, readonly, assign) KTKDeviceDataLoggerStatus dataLoggerStatus;


@end

NS_ASSUME_NONNULL_END
