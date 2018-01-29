//
//  KontaktSDK
//  Version: 1.5.1
//
//  Copyright © 2017 Kontakt.io. All rights reserved.
//

@import Foundation;

#import "KTKCloudDefinitions.h"

NS_ASSUME_NONNULL_BEGIN

#pragma mark - KTKTriggerContext (Interface)
@interface KTKTriggerContext : NSObject <NSObject, NSCopying, NSSecureCoding>

#pragma mark - TriggerContext Properties
///--------------------------------------------------------------------
/// @name TriggerContext Properties
///--------------------------------------------------------------------

/**
 *  Cooldown property. (read-only)
 */
@property (nonatomic, strong, readonly) NSString * _Nullable cooldown;

/**
 *  Source ID property. (read-only)
 */
@property (nonatomic, strong, readonly) NSString * _Nullable sourceID;

/**
 *  Proximity property. (read-only)
 */
@property (nonatomic, assign, readonly) KTKProximity proximity;

/**
 *  Unique ID of device that we want to track. (read-only)
 */
@property (nonatomic, strong, readonly) NSString * _Nullable trackingID;

#pragma mark - iBeacon Properties
///--------------------------------------------------------------------
/// @name iBeacon Properties
///--------------------------------------------------------------------

/**
 *  Proximity UUID transmitted by tracked device. (read-only)
 */
@property (nonatomic, strong, readonly) NSUUID * _Nullable proximityUUID;

/**
 *  Major value transmitted by tracked device. (read-only)
 */
@property (nonatomic, strong, readonly) NSNumber * _Nullable major;

/**
 *  Minor value transmitted by tracked device. (read-only)
 */
@property (nonatomic, strong, readonly) NSNumber * _Nullable minor;

#pragma mark - Eddystone Properties
///--------------------------------------------------------------------
/// @name Eddystone Properties
///--------------------------------------------------------------------

/**
 *  Namespace ID transmitted by tracked device. (read-only)
 */
@property (nonatomic, strong, readonly) NSString * _Nullable namespaceID;

/**
 *  Instance ID transmitted by tracked device. (read-only)
 */
@property (nonatomic, strong, readonly) NSString * _Nullable instanceID;

@end

NS_ASSUME_NONNULL_END
