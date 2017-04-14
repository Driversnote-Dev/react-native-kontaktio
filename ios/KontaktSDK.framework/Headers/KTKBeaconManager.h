//
//  KontaktSDK
//  Version: 1.4.4
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

@import Foundation;
@import CoreLocation;

#import "KTKBeaconRegion.h"
#import "KTKSecureBeaconRegion.h"

NS_ASSUME_NONNULL_BEGIN

#pragma mark - External Helpers
extern NSUUID * KTKKontaktProximityUUID();

#pragma mark -
@protocol KTKBeaconManagerDelegate;

#pragma mark - KTKBeaconManager (Interface)
@interface KTKBeaconManager : NSObject 

#pragma mark - Other Properties
///--------------------------------------------------------------------
/// @name Other Properties
///--------------------------------------------------------------------

/**
 *  The delegate object to receive update events.
 *
 *  @see KTKBeaconManagerDelegate
 */
@property (nonatomic, weak, readwrite) id<KTKBeaconManagerDelegate> _Nullable delegate;

#pragma mark - Initialization Methods
///--------------------------------------------------------------------
/// @name Initialization Methods
///--------------------------------------------------------------------

/**
 *  Initializes and returns a beacon manager object with the specified delegate.
 *
 *  @param delegate The delegate object to receive update events.
 *
 *  @return An initialized beacon manager object.
 *
 *  @see KTKBeaconManagerDelegate
 */
- (instancetype)initWithDelegate:(id<KTKBeaconManagerDelegate> _Nullable)delegate;

#pragma mark - Core Location Authorization
///--------------------------------------------------------------------
/// @name Core Location Authorization
///--------------------------------------------------------------------

/**
 *  Requests permission to use location services whenever the app is running.
 *
 */
- (void)requestLocationAlwaysAuthorization;

/**
 *  Requests permission to use location services while the app is in the foreground.
 *
 */
- (void)requestLocationWhenInUseAuthorization;

/**
 *  Returns the app’s authorization status for using location services.
 *
 *  @return  A value indicating whether the app is authorized to use location services.
 */
+ (CLAuthorizationStatus)locationAuthorizationStatus;

#pragma mark - Monitoring Beacon Regions
///--------------------------------------------------------------------
/// @name Monitoring Beacon Regions
///--------------------------------------------------------------------

/**
 *  Returns a Boolean indicating whether the device supports monitoring for region.
 *
 *  @return <code>YES</code> if the device is capable of monitoring regions or <code>NO</code> if it is not.
 */
+ (BOOL)isMonitoringAvailable;

/**
 *  The set of regions currently being monitored. (read-only)
 *
 *  @see KTKBeaconRegion
 *  @see KTKSecureBeaconRegion
 */
@property (nonatomic, copy, readonly, nonnull) NSSet<__kindof KTKBeaconRegion*>* monitoredRegions;

/**
 *  Starts monitoring the specified region.
 *
 *  For more details read Apple Documentation for startMonitoringForRegion: <http://apple.co/1KbW5cY>
 *
 *  @param region The region object that defines the boundary to monitor. This parameter must not be nil.
 *
 *  @see KTKBeaconManagerDelegate
 *  @see KTKBeaconRegion
 *  @see KTKSecureBeaconRegion
 *  @see [[CLLocationManager startMonitoringForRegion:]](http://apple.co/1KbW5cY)
 */
- (void)startMonitoringForRegion:(__kindof KTKBeaconRegion*)region;

/**
 *  Stops monitoring the specified region.
 *
 *  If the specified region object is not currently being monitored, this method has no effect.
 *  For more details read Apple Documentation for stopMonitoringForRegion: <http://apple.co/1ODGt3L>
 *
 *  @param region The region object currently being monitored. This parameter must not be nil.
 *
 *  @see KTKBeaconManagerDelegate
 *  @see KTKBeaconRegion
 *  @see KTKSecureBeaconRegion
 *  @see [[CLLocationManager stopMonitoringForRegion:]](http://apple.co/1ODGt3L)
 */
- (void)stopMonitoringForRegion:(__kindof KTKBeaconRegion*)region;

/**
 *  Stops monitoring for all regions.
 *
 *  If any regions are monitored directly by an instance of CLLocationManager they will also be stopped
 *  as monitoredRegions property is shared between instances of CLLocationManager.
 *
 *  @see KTKBeaconManagerDelegate
 */
- (void)stopMonitoringForAllRegions;

/**
 *  Retrieves the state of a region asynchronously.
 *
 *  @param region The region whose state you want to know.
 *
 *  @see KTKBeaconManagerDelegate
 *  @see [[CLLocationManager requestStateForRegion:]](http://apple.co/1MWG5NO)
 */
- (void)requestStateForRegion:(__kindof KTKBeaconRegion*)region;

#pragma mark - Ranging Beacons
///--------------------------------------------------------------------
/// @name Ranging Beacons
///--------------------------------------------------------------------

/**
 *  The set of regions currently being tracked using ranging. (read-only)
 *
 *  @see KTKBeaconRegion
 *  @see KTKSecureBeaconRegion
 */
@property (nonatomic, copy, readonly, nonnull) NSSet<__kindof KTKBeaconRegion*>* rangedRegions;

/**
 *  Returns a Boolean indicating whether the device supports ranging of beacons.
 *
 *  @return <code>YES</code> if the device supports ranging or <code>NO</code> if it does not
 */
+ (BOOL)isRangingAvailable;

/**
 *  Starts the delivery of notifications for beacons in the specified region.
 *
 *  @param region The region object that defines the identifying information for the targeted beacons. This parameter must not be nil.
 *
 *  @see KTKBeaconRegion
 *  @see KTKSecureBeaconRegion
 *  @see KTKBeaconManagerDelegate
 *  @see [[CLLocationManager startRangingBeaconsInRegion:]](http://apple.co/1GWUWp6)
 */
- (void)startRangingBeaconsInRegion:(__kindof KTKBeaconRegion*)region;

/**
 *  Stops the delivery of notifications for the specified beacon region.
 *
 *  @param region The region that identifies the beacons. This parameter must not be nil.
 *
 *  @see KTKBeaconRegion
 *  @see KTKSecureBeaconRegion
 *  @see KTKBeaconManagerDelegate
 *  @see [[CLLocationManager stopRangingBeaconsInRegion:]](http://apple.co/1Lab3uq)
 */
- (void)stopRangingBeaconsInRegion:(__kindof KTKBeaconRegion*)region;

/**
 *  Stops the delivery of notifications for all the beacon regions.
 *
 *  @see KTKBeaconManagerDelegate
 */
- (void)stopRangingBeaconsInAllRegions;

@end

#pragma mark - KTKBeaconManagerDelegate
/**
 *  The delegate of a KTKBeaconManager object must adopt the KTKBeaconManagerDelegate protocol.
 */
@protocol KTKBeaconManagerDelegate <NSObject>

@optional

#pragma mark - Core Location Authorization
///--------------------------------------------------------------------
/// @name Core Location Authorization
///--------------------------------------------------------------------

/**
 *  Tells the delegate that the authorization status for the application changed.
 *
 *  @param manager The beacon manager object reporting the event.
 *  @param status  The new authorization status for the application.
 *
 *  @see [KTKBeaconManager requestLocationAlwaysAuthorization]
 *  @see [KTKBeaconManager requestLocationWhenInUseAuthorization]
 *  @see [KTKBeaconManager locationAuthorizationStatus]
 */
- (void)beaconManager:(KTKBeaconManager*)manager didChangeLocationAuthorizationStatus:(CLAuthorizationStatus)status;

#pragma mark - Monitoring Beacon Regions Reporting
///--------------------------------------------------------------------
/// @name Monitoring Beacon Regions Reporting
///--------------------------------------------------------------------

/**
 *  Tells the delegate that a new region is being monitored.
 *
 *  @param manager The beacon manager object reporting the event.
 *  @param region The region that is being monitored.
 *
 *  @see [KTKBeaconManager startMonitoringForRegion:]
 */
- (void)beaconManager:(KTKBeaconManager*)manager didStartMonitoringForRegion:(__kindof KTKBeaconRegion*)region;

/**
 *  Tells the delegate that a region monitoring error occurred.
 *
 *  @param manager The beacon manager object reporting the event.
 *  @param region  The region for which the error occurred.
 *  @param error   An error object containing the error code that indicates why region monitoring failed.
 *
 *  @see [KTKBeaconManager startMonitoringForRegion:]
 *  @see [KTKBeaconManager stopMonitoringForRegion:]
 */
- (void)beaconManager:(KTKBeaconManager*)manager monitoringDidFailForRegion:(__kindof KTKBeaconRegion* _Nullable)region withError:(NSError* _Nullable)error;

/**
 *  Tells the delegate that the user entered the specified region.
 *
 *  @param manager The beacon manager object reporting the event.
 *  @param region  An object containing information about the region that was entered.
 *
 *  @see [KTKBeaconManager startMonitoringForRegion:]
 *  @see [KTKBeaconManager stopMonitoringForRegion:]
 */
- (void)beaconManager:(KTKBeaconManager*)manager didEnterRegion:(__kindof KTKBeaconRegion*)region;

/**
 *  Tells the delegate that the user left the specified region.
 *
 *  @param manager The beacon manager object reporting the event.
 *  @param region  An object containing information about the region that was exited.
 *
 *  @see [KTKBeaconManager startMonitoringForRegion:]
 *  @see [KTKBeaconManager stopMonitoringForRegion:]
 */
- (void)beaconManager:(KTKBeaconManager*)manager didExitRegion:(__kindof KTKBeaconRegion*)region;

/**
 *  Tells the delegate about the state of the specified region. (required)
 *
 *  @param manager The beacon manager object reporting the event.
 *  @param state   The state of the specified region. For a list of possible values, see the CLRegionState type.
 *  @param region  The region whose state was determined.
 *
 *  @see [KTKBeaconManager requestStateForRegion:]
 *  @see [CLRegionState](http://apple.co/1PCibWE)
 */
- (void)beaconManager:(KTKBeaconManager*)manager didDetermineState:(CLRegionState)state forRegion:(__kindof KTKBeaconRegion*)region;

#pragma mark - Ranging Beacons Reporting
///--------------------------------------------------------------------
/// @name Ranging Beacons
///--------------------------------------------------------------------

/**
 *  Tells the delegate that one or more beacons are in range.
 *
 *  @param manager The beacon manager object reporting the event.
 *  @param beacons  An array of CLBeacon objects representing the beacons currently in range.
 *                  If beacons is empty, you can assume that no beacons matching the specified region are in range.
 *                  When a specific beacon is no longer in beacons, that beacon is no longer received by the device.
 *  @param region  The region object containing the parameters that were used to range the beacons.
 *
 *  @see [KTKBeaconManager startRangingBeaconsInRegion:]
 */
- (void)beaconManager:(KTKBeaconManager*)manager didRangeBeacons:(NSArray <CLBeacon *>*)beacons inRegion:(__kindof KTKBeaconRegion*)region;

/**
 *  Tells the delegate that a region monitoring error occurred.
 *
 *  @param manager The beacon manager object reporting the event.
 *  @param region  The region for which the error occurred.
 *  @param error   An error object containing the error code that indicates why region monitoring failed.
 *
 *  @see [KTKBeaconManager startRangingBeaconsInRegion:]
 *  @see [KTKBeaconManager stopRangingBeaconsInRegion:]
 */
- (void)beaconManager:(KTKBeaconManager*)manager rangingBeaconsDidFailForRegion:(__kindof KTKBeaconRegion* _Nullable)region withError:(NSError* _Nullable)error;

@end

NS_ASSUME_NONNULL_END
