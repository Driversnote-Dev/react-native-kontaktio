//
//  KontaktSDK
//  Version: 1.5.1
//
//  Copyright © 2017 Kontakt.io. All rights reserved.
//

@import Foundation;
#import "KTKDeviceGatewayConfiguration.h"

NS_ASSUME_NONNULL_BEGIN

#pragma mark -
typedef NS_OPTIONS(NSInteger, KTKDeviceGatewayWiFiNetworkType) {
    KTKDeviceGatewayWiFiNetworkTypeUnknown           = 0,
    KTKDeviceGatewayWiFiNetworkTypeOpen             = 1 << 0,
    KTKDeviceGatewayWiFiNetworkTypeWEP              = 1 << 1,
    KTKDeviceGatewayWiFiNetworkTypePersonalWPA      = 1 << 2,
    KTKDeviceGatewayWiFiNetworkTypeEnterpriseWPA    = 1 << 3,
    KTKDeviceGatewayWiFiNetworkTypePersonalWPA2     = 1 << 4,
    KTKDeviceGatewayWiFiNetworkTypeEnterpriseWPA2   = 1 << 5,
};

#pragma mark - KTKDeviceGatewayWiFiNetwork (Interface)
@interface KTKDeviceGatewayWiFiNetwork : NSObject <NSCopying>

#pragma mark - Initialization Methods
///--------------------------------------------------------------------
/// @name Initialization Methods
///--------------------------------------------------------------------

- (instancetype)initWithName:(NSString*)name;

#pragma mark - Network Properties
///--------------------------------------------------------------------
/// @name Network Properties
///--------------------------------------------------------------------

@property (nonatomic, readonly, strong) NSString *networkSSID;

@property (nonatomic, readonly, assign) NSUInteger signalStrength;

@property (nonatomic, readonly, assign) KTKDeviceGatewayWiFiNetworkType type;

@property (nonatomic, readonly, assign, getter=isSecure) BOOL secure;

@property (nonatomic, readonly, assign, getter=isEnterprise) BOOL enterprise;

#pragma mark - Authorization Properties
///--------------------------------------------------------------------
/// @name Authorization Properties
///--------------------------------------------------------------------

@property (nonatomic, readwrite, copy) NSString * _Nullable login;

@property (nonatomic, readwrite, copy) NSString * _Nullable password;

#pragma mark - Helper Methods
///--------------------------------------------------------------------
/// @name Helper Methods
///--------------------------------------------------------------------

- (KTKDeviceGatewayConfiguration* _Nullable)configuration;

@end

NS_ASSUME_NONNULL_END
