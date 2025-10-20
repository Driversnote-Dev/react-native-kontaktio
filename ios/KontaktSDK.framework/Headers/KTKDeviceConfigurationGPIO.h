//
//  KontaktSDK
//  Version: 3.1.0
//
//  Copyright © 2018 Kontakt.io. All rights reserved.
//

@import Foundation;

#import "KTKDeviceDefinitions.h"

NS_ASSUME_NONNULL_BEGIN

#pragma mark - KTKDeviceConfigurationGPIO (Interface)
@interface KTKDeviceConfigurationGPIO : NSObject

+ (instancetype)pin:(int8_t)pin state:(KTKGPIOState)state;

@property (nonatomic, readwrite, assign) int8_t pin;
@property (nonatomic, readwrite, assign) KTKGPIOState state;

@end

NS_ASSUME_NONNULL_END
