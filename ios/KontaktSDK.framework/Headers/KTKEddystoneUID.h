//
//  KontaktSDK
//  Version: 1.5.1
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

@import Foundation;

#import "KTKEddystoneFrame.h"

NS_ASSUME_NONNULL_BEGIN

#pragma mark - KTKEddystoneUID (Interface)
@interface KTKEddystoneUID : NSObject <KTKEddystoneFrame, NSCopying, NSSecureCoding>

#pragma mark - UID Frame Properties
///--------------------------------------------------------------------
/// @name UID Frame Properties
///--------------------------------------------------------------------

/**
 *  Namespace ID string. (read-only)
 */
@property (nonatomic, copy, readonly) NSString *namespaceID;

/**
 *  Secure namespace ID string. (read-only)
 */
@property (nonatomic, copy, readonly) NSString * _Nullable secureNamespaceID;

/**
 *  Instance ID string. (read-only)
 */
@property (nonatomic, copy, readonly) NSString *instanceID;

#pragma mark - Initialization Methods
///--------------------------------------------------------------------
/// @name Initialization Methods
///--------------------------------------------------------------------

/**
 *  Initializes and returns a UID frame object with the specified namespace ID and instance ID.
 *
 *  @param namespaceID Namespace ID string of the eddystone UID frame object.
 *  @param instanceID Instance ID string of the eddystone UID frame object.
 *
 *  @return An initialized UID frame object.
 */
- (instancetype)initWithNamespaceID:(NSString *)namespaceID
                         instanceID:(NSString *)instanceID;

@end

NS_ASSUME_NONNULL_END
