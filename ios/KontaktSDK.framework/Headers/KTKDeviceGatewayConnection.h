//
//  KontaktSDK
//  Version: 3.1.0
//
//  Copyright © 2017 Kontakt.io. All rights reserved.
//

#import "KTKDeviceConnection.h"
#import "KTKDeviceGatewayWiFiNetwork.h"
#import "KTKDeviceGatewayConfiguration.h"
#import "KTKDeviceGatewayDiagnostic.h"

NS_ASSUME_NONNULL_BEGIN

#pragma mark - Completion Blocks

/**
 *  A completion block object to be executed when the reading WiFi networks operation finishes.
 *
 *  @param networks Set of WiFi networks visible by the Gateway.
 *  @param configuration The configuration object. Result of the read operation.
 *  @param error         An error object containing the error that indicates why the operation failed.
 */
typedef void (^KTKDeviceGatewayConnectionGetWiFiBlock)(NSSet <KTKDeviceGatewayWiFiNetwork *>* _Nullable networks, __kindof KTKDeviceGatewayConfiguration * _Nullable configuration, NSError * _Nullable error);

/**
 *  A completion block object to be executed when the reading mac networks operation finishes.
 *
 *  @param networks Set of mac networks visible by the Gateway.
 *  @param configuration The configuration object. Result of the read operation.
 *  @param error         An error object containing the error that indicates why the operation failed.
 */
typedef void (^KTKDeviceGatewayConnectionGetMACBlock)(NSString * _Nullable mac, NSError * _Nullable error);

/**
 *  A completion block object to be executed when the reading diagnostic networks operation finishes.
 *
 *  @param networks Set of diagnostic networks visible by the Gateway.
 *  @param configuration The configuration object. Result of the read operation.
 *  @param error         An error object containing the error that indicates why the operation failed.
 */
typedef void (^KTKDeviceGatewayConnectionGetDiagnosticBlock)(KTKDeviceGatewayDiagnostic * _Nullable gatewayDiagnostic, NSError * _Nullable error);


#pragma mark - KTKDeviceGatewayConnection (Interface)
@interface KTKDeviceGatewayConnection : KTKDeviceConnection

#pragma mark - Connection Methods
///--------------------------------------------------------------------
/// @name Connection Methods
///--------------------------------------------------------------------

- (void)writeUsingCloudConfiguration:(KTKDeviceConfiguration *)configuration completion:(KTKDeviceConnectionWriteCompletion)completion;

/**
 *  Reads the configuration from the connection device.
 *
 *  @param completion A block object to be executed when the read operation finishes.
 */
- (void)getWiFiNetworks:(KTKDeviceGatewayConnectionGetWiFiBlock)completion;

/**
 *  Reads the configuration from the connection device using MAC.
 *
 *  @param completion A block object to be executed when the read operation finishes.
 */
- (void)getMacDevice:(KTKDeviceGatewayConnectionGetMACBlock)completion;


/**
 *  Blink device
 *
 *  @param completion A block object to be executed when the read operation finishes.
 */
- (void)getBlinkDevice:(KTKDeviceGatewayConnectionGetMACBlock)completion;
/**
 *  Reads the configuration from the connection device using MAC.
 *
 *  @param completion A block object to be executed when the read operation finishes.
 */
- (void)getDiagnosticDevice:(KTKDeviceGatewayConnectionGetDiagnosticBlock)completion;

@end

NS_ASSUME_NONNULL_END
