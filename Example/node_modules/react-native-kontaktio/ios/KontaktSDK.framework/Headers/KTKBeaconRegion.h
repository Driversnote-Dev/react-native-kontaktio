//
//  KontaktSDK
//  Version: 1.4.4
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

@import Foundation;
@import CoreLocation;

NS_ASSUME_NONNULL_BEGIN

#pragma mark - KTKBeaconRegion (Interface)
@interface KTKBeaconRegion : NSObject <NSCopying, NSSecureCoding>

#pragma mark - Region Properties
///--------------------------------------------------------------------
/// @name Region Properties
///--------------------------------------------------------------------

/**
 *  The proximity ID of the beacons being targeted. (read-only)
 */
@property (nonatomic, strong, readonly) NSUUID *proximityUUID;

/**
 *  The value identifying a group of beacons. (read-only)
 */
@property (nonatomic, strong, readonly) NSNumber * _Nullable major;

/**
 *  The value identifying a specific beacon within a group. (read-only)
 */
@property (nonatomic, strong, readonly) NSNumber * _Nullable minor;

/**
 *  A unique identifier to associate with the region object. You use this identifier to differentiate regions within your application. (read-only)
 */
@property (nonatomic, copy, readonly) NSString *identifier;

/**
 *  A Boolean indicating whether beacon notifications are sent when the device’s display is on.
 */
@property (nonatomic, assign) BOOL notifyEntryStateOnDisplay;

/**
 *  A Boolean indicating that notifications are generated upon entry into the region.
 */
@property (nonatomic, assign) BOOL notifyOnEntry;

/**
 *  A Boolean indicating that notifications are generated upon exit from the region.
 */
@property (nonatomic, assign) BOOL notifyOnExit;

#pragma mark - Initialization Methods
///--------------------------------------------------------------------
/// @name Initialization Methods
///--------------------------------------------------------------------

/**
 *  Initializes and returns a region object that targets a beacon with the specified proximity ID.
 *
 *  @param proximityUUID  The proximity ID of the beacons being targeted. This value must not be nil.
 *  @param identifier     A unique identifier to associate with the returned region object. You use this identifier to differentiate regions within your application. This value must not be nil.
 *
 *  @return An initialized beacon region object.
 */
- (instancetype)initWithProximityUUID:(NSUUID*)proximityUUID
                           identifier:(NSString *)identifier;;

/**
 *  Initializes and returns a region object that targets a beacon with the specified proximity ID and major value.
 *
 *  @param proximityUUID The proximity ID of the beacons being targeted. This value must not be nil.
 *  @param major         The major value that you use to identify one or more beacons.
 *  @param identifier    A unique identifier to associate with the returned region object. You use this identifier to differentiate regions within your application. This value must not be nil.
 *
 *  @return An initialized beacon region object.
 */
- (instancetype)initWithProximityUUID:(NSUUID*)proximityUUID
                                major:(CLBeaconMajorValue)major
                           identifier:(NSString *)identifier;

/**
 *  Initializes and returns a region object that targets a beacon with the specified proximity ID, major value, and minor value.
 *
 *  @param proximityUUID The proximity ID of the beacons being targeted. This value must not be nil.
 *  @param major         The major value that you use to identify one or more beacons.
 *  @param minor         The minor value that you use to identify a specific beacon.
 *  @param identifier    A unique identifier to associate with the returned region object. You use this identifier to differentiate regions within your application. This value must not be nil.
 *
 *  @return An initialized beacon region object.
 */
- (instancetype)initWithProximityUUID:(NSUUID*)proximityUUID
                                major:(CLBeaconMajorValue)major
                                minor:(CLBeaconMinorValue)minor
                           identifier:(NSString *)identifier;

@end

NS_ASSUME_NONNULL_END
