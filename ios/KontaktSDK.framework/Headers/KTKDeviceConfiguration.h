//
//  KontaktSDK
//  Version: 3.1.0
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

#import "KTKDeviceDefinitions.h"
#import "KTKCloudModel.h"
#import "KTKDevicePowerSaving.h"
#import "KTKDeviceConfigurationGPIO.h"

NS_ASSUME_NONNULL_BEGIN

#pragma mark - KTKDeviceConfiguration (Interface)
@interface KTKDeviceConfiguration : NSObject <KTKCloudModel>

#pragma mark - General Properties
///--------------------------------------------------------------------
/// @name General Properties
///--------------------------------------------------------------------

/**
 *  Kontakt unique identifier. (read-only)
 */
@property (nonatomic, copy, readonly) NSString * _Nullable uniqueID;

/**
 *  Kontakt device local name.
 */
@property (nonatomic, copy, readwrite) NSString * _Nullable name;

/**
 *  Kontakt device's password.
 *
 *  Please note pasword property is nil when accessing it through <code>configuration</code> on <KTKDevice>.
 *  You should only use it to change the device's password.
 */
@property (nonatomic, copy, readwrite) NSString * _Nullable password;

/**
 *  A status indicating whether device is in shuffle mode.
 */
@property (nonatomic, assign, readwrite) KTKDeviceShuffleStatus shuffleStatus;

/**
 *  Transmission power.
 *
 *  @see KTKDeviceTransmissionPower
 */
@property (nonatomic, assign, readwrite) KTKDeviceTransmissionPower transmissionPower;

/**
 *  Advertising profile.
 *
 *  @see KTKDeviceAdvertisingProfile
 */
@property (nonatomic, assign, readwrite) KTKDeviceAdvertisingProfile profile
__attribute__((deprecated("Please use `packets` property instead")));

/**
 *  Advertising packets.
 *
 *  @see KTKDeviceAdvertisingPacket
 */
@property (nonatomic, assign, readwrite) KTKDeviceAdvertisingPackets packets;

/**
 *  Advertising interval in milliseconds.
 *
 *  @see https://support.kontakt.io/hc/en-gb/articles/201567802-Advertising-Interval-best-practise
 */
@property (nonatomic, strong, readwrite) NSNumber * _Nullable advertisingInterval;

/**
 *  Device's power saving configuration.
 *
 *  @see KTKDevicePowerSaving
 */
@property (nonatomic, copy, readwrite) KTKDevicePowerSaving * _Nullable powerSaving;

/**
 *  A Boolean indicating whether any other pending configuration should be overwritten when posting to the cloud API.
 */
@property (nonatomic, assign, readwrite) BOOL forceOverwrite;

/**
 *  Telemetry fields flags.
 *
 *  @see KTKDeviceTelemetryFields
 */
@property (nonatomic, assign, readwrite) KTKDeviceTelemetryFields telemetryFields;


#pragma mark - iBeacon Properties
///--------------------------------------------------------------------
/// @name iBeacon Properties
///--------------------------------------------------------------------

/**
 *  An iBeacon proximity UUID.
 */
@property (nonatomic, copy, readwrite) NSUUID * _Nullable proximityUUID;

/**
 *  An iBeacon major value.
 */
@property (nonatomic, strong, readwrite) NSNumber * _Nullable major;

/**
 *  An iBeacon minor value.
 */
@property (nonatomic, strong, readwrite) NSNumber * _Nullable minor;

/**
 *  A reference transmission power values for iBeacon advertising (measured at 1 meter).
 */
@property (nonatomic, strong, readwrite) NSArray <NSNumber *>* _Nullable rssiAt1Meter;

#pragma mark - Eddystone Properties
///--------------------------------------------------------------------
/// @name Eddystone Properties
///--------------------------------------------------------------------

/**
 *  An Eddystone namespace ID.
 */
@property (nonatomic, copy, readwrite) NSString * _Nullable namespaceID;

/**
 *  An Eddystone instance ID.
 */
@property (nonatomic, copy, readwrite) NSString * _Nullable instanceID;

/**
 *  An Eddystone URL object.
 */
@property (nonatomic, copy, readwrite) NSURL * _Nullable URL;

/**
 *  A reference transmission power values for Eddystone advertising (measured at 0 meters).
 */
@property (nonatomic, strong, readwrite) NSArray <NSNumber *>* _Nullable rssiAt0Meter;

#pragma mark - Telemetry Properties
///--------------------------------------------------------------------
/// @name Telemetry Properties
///--------------------------------------------------------------------

/**
 *  Telemetry temperature offset value. This property is currently available only on NRF52 chipset devices.
 *
 *  This property can be used to calibrate temperature readings.
 */
@property (nonatomic, strong, readwrite) NSNumber * _Nullable temperatureOffset;

#pragma mark - Sensors Config Properties
///--------------------------------------------------------------------
/// @name Sensors Properties
///--------------------------------------------------------------------

/**
 *  This property can be used to set line for footfall.
 */
//@property (nonatomic, strong, readwrite) NSArray <NSNumber *>* _Nullable footfallLine;
@property (nonatomic, copy, readwrite) NSString * _Nullable footfallLine;


/**
 *  Bluetooth blink Interval value.
 *
 *  This property can be used Blink time for IR emitter, in seconds. 0 - disabled. Default: 2 (s)
 */
@property (nonatomic, strong, readwrite) NSNumber * _Nullable blinkInterval;

/**
 *  Bluetooth ir detection interval value.
 *
 *  This property can be used to set seconds to sleep between detection attempts. Default: 5 (s)
 */
@property (nonatomic, strong, readwrite) NSNumber * _Nullable irDetectionInterval;

/**
 *  Bluetooth ir detection duration value.
 *
 *  This property can be used to set seconds to try and detect the IR signal, before going to sleep again. Default: 2 (s)
 */
@property (nonatomic, strong, readwrite) NSNumber * _Nullable irDetectionDuration;

/**
 *  Bluetooth  ir detection sleep value.
 *
 *  This property can be used to set seconds 0: disabled, 1: enabled. Default: 1
 */
@property (nonatomic, strong, readwrite) NSNumber * _Nullable irDetectionSleep;

/**
 *  Bluetooth Scan interval value.
 *
 *  This property can be used to set seconds between scans. 0: disabled. Default: 23 (h), 82800 seconds
 */
@property (nonatomic, strong, readwrite) NSNumber * _Nullable bleScanInterval;

/**
 *  Bluetooth Scan duration value.
 *
 *  This property can be used to set milliseconds to scan for. Default: 10000 ms (10s)
 */
@property (nonatomic, strong, readwrite) NSNumber * _Nullable bleScanDuration;

/**
 *  Room number ir value.
 *
 *  This property can be used to set room number.
 */
@property (nonatomic, strong, readwrite) NSNumber * _Nullable irRoomNumber;

/**
 *  Occupancy mode.
 *
 *  @see KTKDeviceOccupancyModel
 */

@property (nonatomic, strong, readwrite) NSNumber * _Nullable occupancyModel;


/**
 *  Exclusions.
 *
 *  @see KTKDeviceOccupancyModel
 */

@property (nonatomic, strong, readwrite) NSArray <NSDictionary *>*  _Nullable exclusions;

/**
 *  Inclusions.
 *
 *  @see KTKDeviceOccupancyModel
 */

@property (nonatomic, strong, readwrite) NSArray <NSDictionary *>*  _Nullable inclusions;

#pragma mark - Data Logger Properties
///--------------------------------------------------------------------
/// @name Data Logger Properties
///--------------------------------------------------------------------

@property (nonatomic, strong, readwrite) NSNumber *dataLoggerSamplingInterval;

@property (nonatomic, assign, readwrite) KTKDeviceDataLoggerFields dataLoggerFields;
    
#pragma mark - Features Properties
///--------------------------------------------------------------------
/// @name Features Properties
///--------------------------------------------------------------------

/**
 *  The current value of real time clock. This property is currently available only on NRF52 chipset devices.
 */
@property (nonatomic, strong, readwrite) NSDate * _Nullable rtcDate;

@property (nonatomic, strong, readwrite) NSArray<KTKDeviceConfigurationGPIO *> * _Nullable GPIOStates;

#pragma mark - Secure Configuration
///--------------------------------------------------------------------
/// @name Secure Configuration
///--------------------------------------------------------------------

/**
 *  Raw properties dictionary.
 *
 *  Raw Secure Configuration Key Value storage.
 *  This is represented in the Cloud API as `customConfiguration`.
 */
@property (nonatomic, strong, readwrite) NSDictionary<NSString *, NSData *> * _Nullable rawProperties;

/**
 *  A response data object.
 *
 *  Response object contains data recieved from the device after configuration.
 */
@property (nonatomic, strong, readonly) NSData * _Nullable secureRequest;

/**
 *  A response data object.
 *
 *  Response object contains data recieved from the device after configuration.
 */
@property (nonatomic, strong, readonly) NSData * _Nullable secureResponse;

/**
 *  A response date object.
 *
 *  A date and time of when the response was recieved.
 */
@property (nonatomic, strong, readonly) NSDate * _Nullable secureResponseTime;

#pragma mark - Initialization Methods
///--------------------------------------------------------------------
/// @name Initialization Methods
///--------------------------------------------------------------------

/**
 *  Initializes and returns a device configuration object for device with the specified unique identifier.
 *
 *  @param uniqueID The unique identifier.
 *
 *  @return An initialized device configuration object.
 */
- (instancetype)initWithUniqueID:(NSString *)uniqueID;

#pragma mark - Additional Methods
///--------------------------------------------------------------------
/// @name Additional Methods
///--------------------------------------------------------------------

/**
 *  Returns a set of property keys modified when compared with given configuration object.
 *
 *  @param config The config object being compared with this object.
 *
 *  @return A set of property keys.
 */
- (NSSet <NSString *>*)modifiedKeysComparedTo:(KTKDeviceConfiguration *)config;

@end

NS_ASSUME_NONNULL_END
