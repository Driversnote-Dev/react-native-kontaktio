//
//  KontaktSDK
//  Version: 1.5.1
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

@import Foundation;

#import "KTKNearbyDevice.h"

NS_ASSUME_NONNULL_BEGIN

@protocol KTKDevicesManagerDelegate;

#pragma mark - External Constants
extern NSTimeInterval const KTKDeviceInvalidationAgeNever;

#pragma mark - Type Definition
/**
 *  Nearby devices discovery mode.
 */
typedef NS_ENUM(NSUInteger, KTKDevicesManagerDiscoveryMode) {
    /**
     *  Discovery mode Auto deliveres devices notifications as the devices becoming valid or invalid.
     *  There is no limit to these notifications so please make sure when working with hundreds of
     *  nearby devices this may impact performance. It is better to use discovery with interval then.
     */
    KTKDevicesManagerDiscoveryModeAuto = 0,
    
    /**
     *  Discovery mode Interval deliveres devices notifications with the specified time inverval.
     *  When working with hundreds of nearby devices this is preferred mode.
     *  When just few nearby devices have been discovered in a close time span it is better to use mode auto, as it is responding faster to changes.
     */
    KTKDevicesManagerDiscoveryModeInterval
};

#pragma mark - KTKDevicesManager (Interface)
@interface KTKDevicesManager : NSObject

#pragma mark - Other Properties
///--------------------------------------------------------------------
/// @name Other Properties
///--------------------------------------------------------------------

/**
 *  The current state of the bluetooth central.
 */
@property (nonatomic, assign, readonly) CBManagerState centralState;

/**
 *  A Boolean indicating whether the devices manager is currently discovering.
 */
@property (nonatomic, assign, readonly, getter=isDiscovering) BOOL discovering;

/**
 *  A Boolean indicating whether the devices manager should detect devices locked status.
 */
@property (nonatomic, assign, readwrite, getter=isDetectingLocks) BOOL detectingLocks;

/**
 *  The delegate object that will receive events.
 */
@property (nonatomic, weak, readonly) id<KTKDevicesManagerDelegate> _Nullable delegate;

#pragma mark - Initialization Methods
///--------------------------------------------------------------------
/// @name Initialization Methods
///--------------------------------------------------------------------

/**
 *  Initializes and returns an devices manager object with the specified delegate.
 *
 *  @param delegate The delegate object that will receive events.
 *
 *  @return An initialized devices manager object.
 *
 *  @see KTKDevicesManagerDelegate
 */
- (instancetype)initWithDelegate:(id<KTKDevicesManagerDelegate> _Nullable)delegate;

#pragma mark - Configuration Properties
///--------------------------------------------------------------------
/// @name Configuration Properties
///--------------------------------------------------------------------

/**
 *  A time interval after which nearby device will be invalidated if not re-discovered.
 *
 *  Each time nearby device advertising is discovered its <code>updateAt</code> property is updated.
 *  If <code>updateAt</code> property is updated for longer than <code>invalidationAge</code> value
 *  a nearby device will be invalidated/removed from current devices list.
 *
 *  Default value is 10.0 seconds.
 */
@property (nonatomic, assign, readwrite) NSTimeInterval invalidationAge;

/**
 *  A mode in which nearby devices discovery is done.
 *  
 *  If <code>discoveryInterval</code> property is set or discovery is started with <code>startDevicesDiscoveryWithInterval:</code> method,
 *  <code>discoveryMode</code> is automatically set to <code>KTKDevicesManagerDiscoveryModeInterval</code>.
 * 
 *  When discovery is started with <code>startDevicesDiscovery</code> mode will be set to <code>KTKDevicesManagerDiscoveryModeAuto</code>.
 *
 *  @see KTKDevicesManagerDiscoveryMode
 */
@property (nonatomic, assign, readwrite) KTKDevicesManagerDiscoveryMode discoveryMode;

/**
 *  A time interval after which discovered notifications will be delivered.
 */
@property (nonatomic, assign, readwrite) NSTimeInterval discoveryInterval;

#pragma mark - Discovery Methods
///--------------------------------------------------------------------
/// @name Discovery Methods
///--------------------------------------------------------------------

/**
 *  Starts discovery of Kontakt.io's nearby devices.
 */
- (void)startDevicesDiscovery;

/**
 *  Starts discovery of Kontakt.io's nearby devices with specified time interval.
 *
 *  @param interval A time interval after which discovered notifications will be delivered.
 */
- (void)startDevicesDiscoveryWithInterval:(NSTimeInterval)interval;

/**
 *  Stops discovery of Kontakt.io's nearby devices.
 */
- (void)stopDevicesDiscovery;

/**
 *  Restarts discovery of Kontakt.io's nearby devices.
 *
 *  @param completion A block object to be executed when manager restarts the discovery.
 */
- (void)restartDeviceDiscoveryWithCompletion:(void(^)( NSError * _Nullable))completion;

@end

#pragma mark - KTKDevicesManagerDelegate
@protocol KTKDevicesManagerDelegate <NSObject>

#pragma mark - Required Methods
///--------------------------------------------------------------------
/// @name Required Methods
///--------------------------------------------------------------------

/**
 *  Tells the delegate that one or more devices were discovered.
 *
 *  @param manager The devices manager object reporting the event.
 *  @param devices An list of discovered nearby devices.
 */
@required
- (void)devicesManager:(KTKDevicesManager*)manager didDiscoverDevices:(NSArray <KTKNearbyDevice*>*)devices;

#pragma mark - Optional Methods
///--------------------------------------------------------------------
/// @name Optional Methods
///--------------------------------------------------------------------

/**
 *  Tells the delegate that a devices discovery error occurred.
 *
 *  @param manager The devices manager object reporting the event.
 *  @param error   An error object containing the error code that indicates why discovery failed.
 */
@optional
- (void)devicesManagerDidFailToStartDiscovery:(KTKDevicesManager*)manager withError:(NSError*)error;

@end

NS_ASSUME_NONNULL_END
