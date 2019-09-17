//
//  KontaktSDK
//  Version: 1.5.1
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

@import Foundation;

#import "KTKEddystoneFrame.h"

NS_ASSUME_NONNULL_BEGIN

#pragma mark - KTKEddystoneTLM (Interface)
@interface KTKEddystoneTLM : NSObject <KTKEddystoneFrame, NSCopying, NSSecureCoding>

#pragma mark - TLM (Telemetry) Frame Properties
///--------------------------------------------------------------------
/// @name TLM (Telemetry) Frame Properties
///--------------------------------------------------------------------

/**
 *  Eddystone Version. (read-only)
 */
@property (nonatomic, assign, readonly) NSUInteger version;

/**
 *  Battery voltage in Volts. (read-only)
 */
@property (nonatomic, assign, readonly) double batteryVoltage;

/**
 *  Temperature reading value in Celcius. (read-only)
 */
@property (nonatomic, assign, readonly) double temperature;

/**
 *  Number of advertising packets sent since power up. (read-only)
 */
@property (nonatomic, assign, readonly) NSUInteger advertisingCount;

/**
 *  Time interval since power up. (read-only)
 */
@property (nonatomic, assign, readonly) NSTimeInterval timeIntervalSincePowerUp;

@end

NS_ASSUME_NONNULL_END
