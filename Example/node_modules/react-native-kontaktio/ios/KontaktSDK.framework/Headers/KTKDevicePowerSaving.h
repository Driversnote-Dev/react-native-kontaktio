//
//  KontaktSDK
//  Version: 1.4.4
//
//  Copyright © 2016 Kontakt.io. All rights reserved.
//

@import Foundation;

NS_ASSUME_NONNULL_BEGIN

/**
 *  Power saving features.
 */
typedef NS_OPTIONS(NSInteger, KTKDevicePowerSavingFeatures) {
    /**
     *  Power saving turned Off.
     */
    KTKDevicePowerSavingFeaturesOff    = 1 << 0,
    /**
     *  Power saving based on motion sensor.
     */
    KTKDevicePowerSavingFeaturesMotion = 1 << 1,
    /**
     *  Power saving based on light sensor.
     */
    KTKDevicePowerSavingFeaturesLight  = 1 << 2,
    /**
     *  Power saving based on real time clock.
     */
    KTKDevicePowerSavingFeaturesRTC    = 1 << 3,
};

#pragma mark - KTKDevicePowerSaving (Interface)
@interface KTKDevicePowerSaving : NSObject <NSObject, NSCopying, NSSecureCoding>

#pragma mark - General Properties
///--------------------------------------------------------------------
/// @name General Properties
///--------------------------------------------------------------------

@property (nonatomic, assign, readwrite) KTKDevicePowerSavingFeatures features;

#pragma mark - Light Sensor Properties
///--------------------------------------------------------------------
/// @name Light Sensor Properties
///--------------------------------------------------------------------

@property (nonatomic, assign, readwrite) NSInteger lightBrightnessLevel;

#pragma mark - RTC Properties
///--------------------------------------------------------------------
/// @name RTC Properties
///--------------------------------------------------------------------

@property (nonatomic, copy, readwrite) NSDictionary<NSNumber *, NSIndexSet *> * _Nullable rtcHours;

@end

NS_ASSUME_NONNULL_END
