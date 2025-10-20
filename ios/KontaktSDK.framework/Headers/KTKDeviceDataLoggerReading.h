//
//  KontaktSDK
//  Version: 3.1.0
//
//  Copyright © 2017 Kontakt.io. All rights reserved.
//

@import Foundation;

#import "KTKDeviceDefinitions.h"

NS_ASSUME_NONNULL_BEGIN

#pragma mark - KTKDeviceDataLoggerReading (Interface)
@interface KTKDeviceDataLoggerReading : NSObject <NSCopying>

/**
 *  Temperature in degree Celsius. (read-only)
 */
@property (nonatomic, strong, readonly) NSNumber * _Nullable temperature;

/**
 *  Humidity in percentage (0-100). (read-only)
 */
@property (nonatomic, strong, readonly) NSNumber * _Nullable humidity;

/**
 *  Light Sensor Percentage (0-100). (read-only)
 */
@property (nonatomic, strong, readonly) NSNumber * _Nullable lightLevel;

/**
 *  Raw Accelerometer data filtered with lowpass filter. (read-only)
 */
@property (nonatomic, assign, readonly) KTKDeviceAcceleration acceleration;

/**
 *  A date of the reading. (read-only)
 */
@property (nonatomic, strong, readonly) NSDate *date;

/**
 *  Battery Percentage (0-100). (read-only)
 */
@property (nonatomic, strong, readonly) NSNumber * _Nullable batteryLevel;

@end

NS_ASSUME_NONNULL_END
