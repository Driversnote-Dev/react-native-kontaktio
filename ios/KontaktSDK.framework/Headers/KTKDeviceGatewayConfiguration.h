//
//  KontaktSDK
//  Version: 1.5.1
//
//  Copyright © 2017 Kontakt.io. All rights reserved.
//

#import "KTKDeviceConfiguration.h"

typedef NS_ENUM(NSInteger, KTKGatewayWiFiProtocol) {
    /**
     *  WPA_PSK Wifi protocol type.
     */
    KTKGatewayWifiProtocolWPAPSK = 10,
    /**
     *  WPA_EAP WiFi protocol type.
     */
    KTKGatewayWifiProtocolWPAEAP = 11
};

NS_ASSUME_NONNULL_BEGIN

#pragma mark - KTKDeviceGatewayConfiguration (Interface)
@interface KTKDeviceGatewayConfiguration : KTKDeviceConfiguration

#pragma mark - General Properties
///--------------------------------------------------------------------
/// @name General Properties
///--------------------------------------------------------------------

/**
 *  WiFi SSID.
 */
@property (nonatomic, copy, readwrite) NSString * _Nullable wifiSSID;

/**
 *  WiFi login.
 */
@property (nonatomic, copy, readwrite) NSString * _Nullable wifiLogin;

/**
 *  WiFi password.
 */
@property (nonatomic, copy, readwrite) NSString * _Nullable wifiPassword;

/**
 *  WiFi protocol.
 */
@property (nonatomic, assign, readwrite) KTKGatewayWiFiProtocol wifiProtocol;

/**
 *  Gateway's API Key.
 */
@property (nonatomic, copy, readwrite) NSString * _Nullable apiKey;

@end

NS_ASSUME_NONNULL_END
