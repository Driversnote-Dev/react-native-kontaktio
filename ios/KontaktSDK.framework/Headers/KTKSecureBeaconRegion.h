//
//  KontaktSDK
//  Version: 1.5.1
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

#import "KTKBeaconRegion.h"
#import "CLBeacon+Kontakt.h"

NS_ASSUME_NONNULL_BEGIN

#pragma mark - KTKBeaconRegion (Interface)
@interface KTKSecureBeaconRegion : KTKBeaconRegion <NSCopying, NSSecureCoding>

#pragma mark - Secure Region Properties
///--------------------------------------------------------------------
/// @name Secure Region Properties
///--------------------------------------------------------------------

/**
 *  A Boolean indicating whether enter and exit region notifications should be assisted by determine state events.
 */
@property (nonatomic, assign) BOOL assistedMonitoringEvents;

/**
 *  The secure proximity ID of the beacons being targeted. (read-only)
 */
@property (nonatomic, strong, readonly) NSUUID * _Nullable secureProximityUUID;

#pragma mark - Initialization Methods
///--------------------------------------------------------------------
/// @name Initialization Methods
///--------------------------------------------------------------------

/**
 *  Initializes and returns a region object that targets a beacon with the specified proximity ID.
 *
 *  @param secureProximityUUID  The secure proximity ID of the beacons being targeted. This value must not be nil.
 *  @param identifier           A unique identifier to associate with the returned region object. You use this identifier to differentiate regions within your application. This value must not be nil.
 *
 *  @return An initialized secure beacon region object.
 */
- (instancetype)initWithSecureProximityUUID:(NSUUID*)secureProximityUUID
                                 identifier:(NSString *)identifier;

/**
 *  Initializes and returns a region object that targets a beacon with the specified proximity ID and major value.
 *
 *  @param secureProximityUUID  The secure proximity ID of the beacons being targeted. This value must not be nil.
 *  @param major                The major value that you use to identify one or more beacons.
 *  @param identifier           A unique identifier to associate with the returned region object. You use this identifier to differentiate regions within your application. This value must not be nil.
 *
 *  @return An initialized secure beacon region object.
 */
- (instancetype)initWithSecureProximityUUID:(NSUUID*)secureProximityUUID
                                      major:(CLBeaconMajorValue)major
                                 identifier:(NSString *)identifier;

/**
 *  Initializes and returns a region object that targets a beacon with the specified proximity ID, major value, and minor value.
 *
 *  @param secureProximityUUID  The secure proximity ID of the beacons being targeted. This value must not be nil.
 *  @param major                The major value that you use to identify one or more beacons.
 *  @param minor                The minor value that you use to identify a specific beacon.
 *  @param identifier           A unique identifier to associate with the returned region object. You use this identifier to differentiate regions within your application. This value must not be nil.
 *
 *  @return An initialized secure beacon region object.
 */
- (instancetype)initWithSecureProximityUUID:(NSUUID*)secureProximityUUID
                                      major:(CLBeaconMajorValue)major
                                      minor:(CLBeaconMinorValue)minor
                                 identifier:(NSString *)identifier;

@end

NS_ASSUME_NONNULL_END
