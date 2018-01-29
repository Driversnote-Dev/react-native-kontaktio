//
//  KontaktSDK
//  Version: 1.5.1
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

@import Foundation;

NS_ASSUME_NONNULL_BEGIN

#pragma mark - KTKEddystoneRegion (Interface)
@interface KTKEddystoneRegion : NSObject <NSCopying, NSSecureCoding>

#pragma mark - Eddystone Region Properties
///--------------------------------------------------------------------
/// @name Eddystone Region Properties
///--------------------------------------------------------------------

/**
 *  Namespace ID string of the eddystone being targeted. (read-only)
 */
@property (nonatomic, copy, readwrite) NSString * _Nullable namespaceID;

/**
 *  Secure namespace ID string of the eddystone being targeted. (read-only)
 */
@property (nonatomic, copy, readwrite) NSString * _Nullable instanceID;

/**
 *  URL object of the eddystone being targeted. (read-only)
 */
@property (nonatomic, copy, readwrite) NSURL * _Nullable URL;

/**
 *  URL domain of the eddystone being targeted. (read-only)
 */
@property (nonatomic, copy, readwrite) NSString * _Nullable URLDomain;

#pragma mark - Initialization Methods
///--------------------------------------------------------------------
/// @name Initialization Methods
///--------------------------------------------------------------------

/**
 *  Initializes and returns a region object that targets an eddystone with the specified namespace ID.
 *
 *  @param namespaceID Namespace ID string of the eddystone being targeted.
 *
 *  @return An initialized eddystone region object.
 */
- (instancetype)initWithNamespaceID:(NSString* _Nonnull)namespaceID;

/**
 *  Initializes and returns a region object that targets an eddystone with the specified namespace ID and instance ID.
 *
 *  @param namespaceID Namespace ID string of the eddystone being targeted.
 *  @param instanceID Instance ID string of the eddystone being targeted.
 *
 *  @return An initialized secure eddystone region object.
 */
- (instancetype)initWithNamespaceID:(NSString* _Nonnull)namespaceID
                         instanceID:(NSString* _Nullable)instanceID;

/**
 *  Initializes and returns a region object that targets an eddystone with the specified URL.
 *
 *  @param URL URL object of the eddystone being targeted.
 *
 *  @return An initialized eddystone region object.
 */
- (instancetype)initWithURL:(NSURL*)URL; 

/**
 *  Initializes and returns a region object that targets an eddystone with the specified URL domain.
 *
 *  @param URLDomain URL domain of the eddystone being targeted.
 *
 *  @return An initialized eddystone region object.
 */
- (instancetype)initWithURLDomain:(NSString*)URLDomain;

@end

NS_ASSUME_NONNULL_END
