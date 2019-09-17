//
//  KontaktSDK
//  Version: 1.5.1
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

@import Foundation;

#pragma mark - External Constants
extern double        KTKSDKVersion;
extern unsigned long KTKAPIVersion;

/**
 *  Devices monitoring options
 */
typedef NS_OPTIONS(NSUInteger, KTKMonitoringOptions) {
    /**
     *  The battery Status monitoring
     */
    KTKMonitoringOptionsBatteryStatus = 1 << 0,
    /**
     *  The devices GPS Position/Location monitoring
     */
    KTKMonitoringOptionsGPSLocation   = 1 << 1
};

/**
 *  Calculates distance to device from specified TX Power and RSSI.
 *
 *  @param TXPower Transmission power.
 *  @param RSSI    RSSI value.
 *
 *  @return Distance in meters as double value.
 */
extern double KTKCalculateDistanceFrom(int TXPower, double RSSI);

#pragma mark - Kontakt
@interface Kontakt : NSObject

#pragma mark - Configuration
///--------------------------------------------------------------------
/// @name Configuration
///--------------------------------------------------------------------

/**
 *  Sets the Cloud API Key.
 *
 *  @param key The API Key string.
 *
 *  @see APIKey
 */
+ (void)setAPIKey:(NSString*)key;

/**
 *  Returns a string value of the Cloud API Key.
 *
 *  @return A string value of the API Key.
 *
 *  @see setAPIKey:
 */
+ (NSString*)APIKey;

/**
 *  Removes caches created by the SDK.
 * 
 *  Cache should be removed every time <code>APIKey</code> is changed.
 */
+ (void)removeCaches;

/**
 *  Sets the devices monitoring options.
 *
 *  @param options The devices monitoring options.
 */
+ (void)setMonitoringOptions:(KTKMonitoringOptions)options;

/**
 *  Returns a devices monitoring options.
 * 
 *  Default value is KTKMonitoringOptionsBatteryStatus
 *
 *  @return A devices monitoring options.
 */
+ (KTKMonitoringOptions)monitoringOptions;

/**
 *  Sets the CBCentralManagerOptionShowPowerAlertKey option for internal Central Manager.
 *
 *  @param alert A Boolean value that specifies whether the system should display a warning dialog to the user if Bluetooth is powered off when the central manager is instantiated.
 */
+ (void)setCentralManagerPowerAlert:(BOOL)alert;

@end
