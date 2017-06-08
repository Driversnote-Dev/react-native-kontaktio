//
//  KontaktSDK
//  Version: 1.4.4
//
//  Copyright © 2015 Kontakt.io. All rights reserved.
//

#import "KTKCloudModel.h"

NS_ASSUME_NONNULL_BEGIN

#pragma mark - KTKDeviceCredentials (Interface)
@interface KTKDeviceCredentials : NSObject <KTKCloudModel>

#pragma mark - Namespace Properties
///--------------------------------------------------------------------
/// @name Namespace Properties
///--------------------------------------------------------------------

/**
 *  Kontakt unique identifier. (read-only)
 */
@property (nonatomic, strong, readonly) NSString *uniqueID;

/**
 *  A Kontakt device's password. (read-only)
 */
@property (nonatomic, strong, readonly) NSString *password;

/**
 *  A Kontakt device's master password. (read-only)
 */
@property (nonatomic, strong, readonly) NSString *masterPassword;

#pragma mark - Initialization Methods
///--------------------------------------------------------------------
/// @name Initialization Methods- (void)readConfigurationWithCompletion:(void (^)(KTKDeviceConfiguration * _Nullable, NSError * _Nullable))completion
///--------------------------------------------------------------------

/**
 *  Initializes and returns a device credentials object with just password.
 *
 *  @param password A Kontakt device's password string object.
 *
 *  @return An initialized device credentials object.
 */
- (instancetype)initWithPassword:(NSString *)password;

@end

NS_ASSUME_NONNULL_END
