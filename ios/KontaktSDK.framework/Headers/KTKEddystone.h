//
//  KontaktSDK
//  Version: 1.5.1
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

@import Foundation;

#import "KTKEddystoneUID.h"
#import "KTKEddystoneURL.h"
#import "KTKEddystoneTLM.h"

NS_ASSUME_NONNULL_BEGIN

/**
 *  Represents the current proximity of an entity.
 */
typedef NS_ENUM(NSInteger, KTKEddystoneProximity) {
    /**
     *  Proximity Unknown
     */
    KTKEddystoneProximityUnknown,
    /**
     *  Proximity Immediate (± 0-1 meter range)
     */
    KTKEddystoneProximityImmediate,
    /**
     *  Proximity Near (± 1-8 meters range)
     */
    KTKEddystoneProximityNear,
    /**
     *  Proximity Far (± 8 and more meters range)
     */
    KTKEddystoneProximityFar
};

#pragma mark - KTKEddystone (Interface)
@interface KTKEddystone : NSObject <NSCopying, NSSecureCoding>

#pragma mark - Eddystone Frames
///--------------------------------------------------------------------
/// @name Eddystone Frames
///--------------------------------------------------------------------

/**
 *  UID Frame object. (read-only)
 *  
 *  @see KTKEddystoneUID
 */
@property (nonatomic, strong, readonly) KTKEddystoneUID * _Nullable eddystoneUID;

/**
 *  URL Frame object. (read-only)
 *
 *  @see KTKEddystoneURL
 */
@property (nonatomic, strong, readonly) KTKEddystoneURL * _Nullable eddystoneURL;

/**
 *  TLM Frame object. (read-only)
 *
 *  @see KTKEddystoneTLM
 */
@property (nonatomic, strong, readonly) KTKEddystoneTLM * _Nullable eddystoneTLM;

#pragma mark - Eddystone Properties
///--------------------------------------------------------------------
/// @name Eddystone Properties
///--------------------------------------------------------------------

/**
 *  The accuracy of the proximity value, measured in meters from the eddystone. (read-only)
 */
@property (nonatomic, assign, readonly) double accuracy;

/**
 *  The relative distance to the eddystone. (read-only)
 *
 *  @see KTKEddystoneProximity
 */
@property (nonatomic, assign, readonly) KTKEddystoneProximity proximity;

/**
 *  Current RSSI value for the eddystone. (read-only)
 */
@property (nonatomic, strong, readonly) NSNumber *RSSI;

/**
 *  CoreBluetooth peripheral identifier. (read-only)
 */
@property (nonatomic, strong, readonly) NSUUID *identifier;

/**
 *  Last discovery update timestamp. (read-only)
 */
@property (nonatomic, assign, readonly) double updatedAt;

@end

NS_ASSUME_NONNULL_END
