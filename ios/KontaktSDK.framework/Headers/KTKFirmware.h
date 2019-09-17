//
//  KontaktSDK
//  Version: 1.5.1
//
//  Copyright © 2015 Kontakt.io. All rights reserved.
//

#import "KTKCloudModel.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, KTKFirmwareType) {
    KTKFirmwareTypeInvalid = -1,
    KTKFirmwareTypeDefault = 0,
    KTKFirmwareTypeArchive = 1
};

#pragma mark - KTKFirmware (Interface)
@interface KTKFirmware : NSObject <KTKCloudModel>

#pragma mark - Firmware Properties
///--------------------------------------------------------------------
/// @name Firmware Properties
///--------------------------------------------------------------------

/**
 *  The firmware ID.
 */
@property (nonatomic, strong, readonly) NSString *firmwareID;

/**
 *  The firmware version string.
 */
@property (nonatomic, strong, readonly) NSString *firmwareVersion;

/**
 *  Description text.
 */
@property (nonatomic, strong, readonly) NSString * _Nullable firmwareDescription;

/**
 *  An array of firmware versions which can be updated to this firmware version.
 */
@property (nonatomic, strong, readonly) NSArray <NSString*> *validVersions;

/**
 *  An array of devices unique IDs which can be updated to this firmware version.
 */
@property (nonatomic, strong, readonly) NSArray <NSString*> * _Nullable validDevicesUniqueID __attribute__((deprecated("Please use `devicesUniqueID` property instead")));

/**
 *  An array of devices unique IDs which can be updated to this firmware version.
 */
@property (nonatomic, strong, readonly) NSArray <NSString*> * _Nullable devicesUniqueID;

/**
 *  A Boolean indicating whether firmware can be applied or not.
 *
 *  It's possible that latest firmware release can require administrator confirmation through the web panel.
 *  Before the administrator allows this version to be installed on the devices this flag will be set to <code>NO</code>.
 *  Only the latest firmware where <code>scheduled</code> value is <code>YES</code> should be used to update devices.
 */
@property (nonatomic, assign, readonly, getter=isScheduled) BOOL scheduled;


/**
 *  A Boolean indicating whether the firmware is important release or not.
 */
@property (nonatomic, assign, readonly, getter=isImportant) BOOL important;

/**
 *  A Boolean indicating whether the firmware is optional or not.
 */
@property (nonatomic, assign, readonly, getter=isOptional) BOOL optional;

/**
 *  The firmware type.
 */
@property (nonatomic, assign, readonly) KTKFirmwareType type;

#pragma mark - Model Methods
///--------------------------------------------------------------------
/// @name Model Methods
///--------------------------------------------------------------------

/**
 *  Downloads the firmware data. You can store
 *
 *  @param completion A block object to be executed when a download process finishes.
 */
- (void)downloadWithCompletion:(void(^)(NSData * _Nullable, NSError * _Nullable))completion;

/**
 *  Gets a firmware objects for the specified kontakt unique IDs.
 *
 *  @param uniqueIDs  An array of kontakt unique identifiers.
 *  @param completion A block object to be executed when the request finishes.
 */
+ (void)getFirmwaresForUniqueIDs:(NSArray*)uniqueIDs completion:(void(^)(NSArray<KTKFirmware*> * _Nullable, NSError * _Nullable))completion;

@end

NS_ASSUME_NONNULL_END
