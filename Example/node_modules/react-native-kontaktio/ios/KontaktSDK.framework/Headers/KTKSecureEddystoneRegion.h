//
//  KontaktSDK
//  Version: 1.4.4
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

#import "KTKEddystoneRegion.h"

NS_ASSUME_NONNULL_BEGIN

#pragma mark - KTKSecureEddystoneRegion (Interface)
@interface KTKSecureEddystoneRegion : KTKEddystoneRegion <NSCopying, NSSecureCoding>

#pragma mark - Secure Eddystone Region Properties
///--------------------------------------------------------------------
/// @name Secure Eddystone Region Properties
///--------------------------------------------------------------------

/**
 *  Eddystone region secure namespace ID.
 */
@property (nonatomic, copy, readwrite) NSString * _Nullable secureNamespaceID;

#pragma mark - Initialization Methods
///--------------------------------------------------------------------
/// @name Initialization Methods
///--------------------------------------------------------------------

/**
 *  Initializes and returns a region object that targets an eddystone with the specified secure namespace ID.
 *
 *  @param secureNamespaceID Secure namespace ID string of the eddystone being targeted.
 *
 *  @return An initialized secure eddystone region object.
 */
- (instancetype)initWithSecureNamespaceID:(NSString* _Nonnull)secureNamespaceID;

/**
 *  Initializes and returns a region object that targets an eddystone with the specified secure namespace ID and instance ID.
 *
 *  @param secureNamespaceID Secure namespace ID string of the eddystone being targeted.
 *  @param instanceID Instance ID string of the eddystone being targeted.
 *
 *  @return An initialized secure eddystone region object.
 */
- (instancetype)initWithSecureNamespaceID:(NSString* _Nonnull)secureNamespaceID
                               instanceID:(NSString* _Nullable)instanceID;


#pragma mark - Unavailable Initialization Methods

- (instancetype)initWithURL:(NSURL*)URL __attribute__((unavailable("initWithURL: is unavailable in KTKSecureEddystoneRegion")));

- (instancetype)initWithURLDomain:(NSString*)URLDomain __attribute__((unavailable("initWithURLDomain is unavailable in KTKSecureEddystoneRegion")));

@end

NS_ASSUME_NONNULL_END
