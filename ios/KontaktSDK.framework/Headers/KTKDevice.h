//
//  KontaktSDK
//  Version: 1.5.1
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

#import "KTKCloudModel.h"
#import "KTKDeviceDefinitions.h"
#import "KTKDeviceConfiguration.h"
#import "KTKDeviceCredentials.h"

NS_ASSUME_NONNULL_BEGIN

#pragma mark - KTKDevice (Interface)
@interface KTKDevice : NSObject <KTKCloudModel>

#pragma mark - Device Object Properties
///--------------------------------------------------------------------
/// @name Device Object Properties
///--------------------------------------------------------------------

/**
 *  Kontakt unique identifier. (read-only)
 */
@property (nonatomic, strong, readonly) NSString *uniqueID;

/**
 *  Mac Address of the device. (read-only)
 */
@property (nonatomic, strong, readonly) NSString *macAddress;

/**
 *  Secure iBeacon proximity UUID. (read-only)
 */
@property (nonatomic, strong, readonly) NSUUID *secureProximity;

/**
 *  Secure Eddystone namespace ID. (read-only)
 */
@property (nonatomic, strong, readonly) NSString *secureNamespace;

/**
 *  The device configuration object.
 */
@property (nonatomic, strong, readwrite) KTKDeviceConfiguration *configuration;

/**
 *  An alias of the device.
 */
@property (nonatomic, strong, readwrite) NSString * _Nullable alias;

/**
 *  An array of device tags.
 */
@property (nonatomic, strong, readwrite) NSArray <NSString *>* _Nullable tags;

/**
 *  Meta dictionary object.
 */
@property (nonatomic, strong, readwrite) NSDictionary * _Nullable meta;

/**
 *  The firmware version.
 */
@property (nonatomic, strong, readwrite) NSString *firmwareVersion;

/**
 *  Kontakt order ID. (read-only)
 */
@property (nonatomic, strong, readonly) NSString *orderID;

/**
 *  Device type. (read-only)
 *
 *  @see KTKDeviceType
 */
@property (nonatomic, assign, readonly) KTKDeviceType type;

/**
 *  Device specification. (read-only)
 *
 *  @see KTKDeviceSpecification
 */
@property (nonatomic, assign, readonly) KTKDeviceSpecification specification;

/**
 *  Device model. (read-only)
 *
 *  @see KTKDeviceModel
 */
@property (nonatomic, assign, readonly) KTKDeviceModel model;

/**
 *  Device manager's ID. (read-only)
 */
@property (nonatomic, strong, readonly) NSUUID *managerID;

/**
 *  Device venue ID. (read-only)
 */
@property (nonatomic, strong, readonly) NSUUID * _Nullable venueID;

/**
 *  The number of actions assigned to the device.
 */
@property (nonatomic, strong, readonly) NSNumber * _Nullable actionsCount;

/**
 *  Device access rights. (read-only)
 *
 *  @see KTKDeviceAccess
 */
@property (nonatomic, assign, readonly) KTKDeviceAccess access;

/**
 *  The latitude of the device.
 */
@property (nonatomic, strong, readwrite) NSNumber * _Nullable latitude;

/**
 *  The longitude of the device.
 */
@property (nonatomic, strong, readwrite) NSNumber * _Nullable longitude;

#pragma mark - Initialization Methods
///--------------------------------------------------------------------
/// @name Initialization Methods
///--------------------------------------------------------------------

/**
 *  Initializes and returns a device with the specified unique identifier.
 *
 *  @param uniqueID The unique identifier.
 *
 *  @return An initialized device object.
 */
- (instancetype)initWithUniqueID:(NSString *)uniqueID;

#pragma mark - Model Methods
///--------------------------------------------------------------------
/// @name Model Methods
///--------------------------------------------------------------------

/**
 *  Gets device credentails from the Cloud API.
 *
 *  @param completion A block object to be executed when the request finishes.
 */
- (void)getCredentialsWithCompletion:(void(^)(KTKDeviceCredentials * _Nullable, NSError * _Nullable))completion;

@end

NS_ASSUME_NONNULL_END
