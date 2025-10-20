//
//  KontaktSDK
//  Version: 3.1.0
//
//  Copyright © 2021 Kontakt.io. All rights reserved.
//

@import Foundation;
#import "KTKDeviceGatewayConfiguration.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(uint8_t, KTKKontaktGatewayDiagnosticCommand) {
    KTKKontaktGatewayDiagnosticCommandDiagnostinc           = 0x01,
};


#pragma mark - KTKDeviceGatewayDiagnostic (Interface)
@interface KTKDeviceGatewayDiagnostic : NSObject <NSCopying>

#pragma mark - Initialization Methods
///--------------------------------------------------------------------
/// @name Initialization Methods
///--------------------------------------------------------------------

- (void)updateDiagnosticData:(NSData *)serviceData;

#pragma mark - Diagnostic Properties
///--------------------------------------------------------------------
/// @name Diagnostic
///--------------------------------------------------------------------

@property (nonatomic, readonly, assign, getter=isAPIConnection)             BOOL aPIConnection;

@property (nonatomic, readonly, assign, getter=isEventCollectConnection)    BOOL eventCollectConnection;

@property (nonatomic, readonly, copy)                                 NSString * iPAddress;

@property (nonatomic, readonly, assign, getter=isTimeSynchronization)       BOOL timeSynchronization;

@property (nonatomic, readonly, assign, getter=isConnectedToWiFi)           BOOL connectedToWiFi;

@property (nonatomic, readonly, assign, getter=isFallbackNetworkConnected)  BOOL fallbackNetworkConnected;

@property (nonatomic, readonly, assign, getter=isMainNetworkVisible)        BOOL mainNetworkVisible;

@property (nonatomic, readonly, assign)                               NSInteger  mainNetworkRSSI;

@property (nonatomic, readonly, assign, getter=isFallbackNetworkVisible)    BOOL fallbackNetworkVisible;

@property (nonatomic, readonly, assign)                               NSInteger  fallbackNetworkRSSI;

@property (nonatomic, readonly, assign, getter=isNearbyNetworks)            BOOL nearbyNetworks;

@property (nonatomic, readonly, assign, getter=isProvision)                 BOOL provision;


@end

NS_ASSUME_NONNULL_END

