//
//  KontaktSDK
//  Version: 1.5.1
//
//  Copyright © 2016 Kontakt.io. All rights reserved.
//

@import CoreLocation;

NS_ASSUME_NONNULL_BEGIN

#pragma mark - CLBeacon (Kontakt)
@interface CLBeacon (Kontakt)

#pragma mark - Kontakt Secure Shuffling Properties
///--------------------------------------------------------------------
/// @name Kontakt Secure Shuffling Properties
///--------------------------------------------------------------------

/**
*  Proximity identifier associated with the beacon.
*/
@property (nonatomic, strong, readonly) NSUUID * ktk_proximityUUID;

/**
 *  Most significant value associated with the beacon.
 */
@property (nonatomic, strong, readonly) NSNumber * ktk_major;

/**
 *  Least significant value associated with the beacon.
 */
@property (nonatomic, strong, readonly) NSNumber * ktk_minor;

@end

NS_ASSUME_NONNULL_END
