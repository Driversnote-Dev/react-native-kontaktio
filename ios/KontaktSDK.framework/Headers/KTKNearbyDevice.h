//
//  KontaktSDK
//  Version: 1.4.4
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

@import Foundation;
@import CoreBluetooth;

#import "KTKDeviceDefinitions.h"

NS_ASSUME_NONNULL_BEGIN

#pragma mark - KTKNearbyDevice (Interface)
@interface KTKNearbyDevice : NSObject <NSCopying>

#pragma mark - Nearby Device Properties
///--------------------------------------------------------------------
/// @name Nearby Device Properties
///--------------------------------------------------------------------

/**
 *  Advertised device name. (read-only)
 */
@property (nonatomic, readonly, copy) NSString * _Nullable name;

/**
 *  Kontakt unique identifier. (read-only)
 */
@property (nonatomic, readonly, copy) NSString * _Nullable uniqueID;

/**
 *  Device firmware version. (read-only)
 */
@property (nonatomic, readonly, strong) NSString *firmwareVersion;

/**
 *  Battery level percentage. (read-only)
 */
@property (nonatomic, readonly, assign) NSUInteger batteryLevel;

/**
 *  A Boolean indicating whether the device is powered with battery or power supply. (read-only)
 */
@property (nonatomic, readonly, assign, getter=isBatteryPowered) BOOL batteryPowered;

/**
 *  Transmission power. (read-only)
 *  
 *  @see KTKDeviceTransmissionPower
 */
@property (nonatomic, readonly, assign) KTKDeviceTransmissionPower transmissionPower;

/**
 *  A Boolean indicating whether the device has configuration profile ( Kontakt.io Secure Communication ). (read-only)
 *  All Kontakt.io's devices with firmware >= 4.0 and all devices since Beacon Pro support configuration profile.
 *
 *  @see https://kontakt.io/products-and-solutions/complete-beacon-security/
 */
@property (nonatomic, readonly, assign) BOOL hasConfigurationProfile;

/**
 *  A Boolean indicating whether the device is currently in Shuffle mode. (read-only)
 *  
 *  @see http://kontakt.io/blog/beacon-security/
 */
@property (nonatomic, readonly, assign, getter=isShuffled) BOOL shuffled;

/**
 *  A Boolean indicating whether the device is locked/non-connectable mode. (read-only)
 */
@property (nonatomic, readonly, assign, getter=isLocked) BOOL locked;

/**
 *  Current advertising profile. (read-only)
 *
 *  @warning *Important:* advertisingProfile property is not compatible with firmware 4.1 as devices can advertise multiple packets at the same time.
 *  advertisingProfile will return `KTKDeviceAdvertisingProfileInvalid` when nearby device's firmware is >= 4.1.
 *  Please note advertisingProfile most probably will soon be removed in favor of packets. Please keep it in mind when planing future projects.
 *
 *  @see KTKDeviceAdvertisingProfile
 */
@property (nonatomic, readonly, assign) KTKDeviceAdvertisingProfile advertisingProfile;

/**
 *  Nearby device model. (read-only)
 *
 *  @warning *Important:* Only devices advertising using Kontakt.io's Secure Profile (UUID: 0xFE6A) (Basically NONE of the devices prior to Beacon Pro model) will provide model information.
 *  In all other cases `model` property will be set to KTKDeviceModelUnknown or KTKDeviceModelInvalid.
 *
 *  @see KTKDeviceModel
 */
@property (nonatomic, readonly, assign) KTKDeviceModel model;

/**
 *  CoreBluetooth Peripheral object associated with the device. (read-only)
 */
@property (nonatomic, readonly, strong) CBPeripheral *peripheral;

/**
 *  Current RSSI value for the device. (read-only)
 */
@property (nonatomic, readonly, copy) NSNumber *RSSI;

/**
 *  Last discovery update timestamp. (read-only) 
 */
@property (nonatomic, readonly, assign) double updatedAt;

@end

NS_ASSUME_NONNULL_END
