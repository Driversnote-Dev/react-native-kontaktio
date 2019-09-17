//
//  KontaktSDK
//  Version: 1.5.1
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

#import "KTKDeviceDefinitions.h"
#import "KTKCloudModel.h"
#import "KTKDevicePowerSaving.h"

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
 *  A reference transmission power for iBeacon advertising (measured at 1 meter).
 */
@property (nonatomic, strong, readwrite) NSNumber * _Nullable referenceTXPowerIBeacon __attribute__((deprecated("Please use `rssiAt1Meter` property instead")));

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
 *  A reference transmission power for Eddystone advertising (measured at 0 meters).
 */
@property (nonatomic, strong, readwrite) NSNumber * _Nullable referenceTXPowerEddystone __attribute__((deprecated("Please use `rssiAt0Meter` property instead")));

/**
 *  A reference transmission power values for Eddystone advertising (measured at 0 meters).
 */
@property (nonatomic, strong, readwrite) NSArray <NSNumber *>* _Nullable rssiAt0Meter;

#pragma mark - Features Properties
///--------------------------------------------------------------------
/// @name Features Properties
///--------------------------------------------------------------------

/**
 *  The current value of real time clock. This property is currently available only on Beacon PRO device.
 */
@property (nonatomic, strong, readwrite) NSDate * _Nullable rtcDate;

#pragma mark - Secure Configuration
///--------------------------------------------------------------------
/// @name Secure Configuration
///--------------------------------------------------------------------

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
