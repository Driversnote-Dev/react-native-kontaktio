//
//  KontaktSDK
//  Version: 1.5.1
//
//  Copyright © 2015 Kontakt.io. All rights reserved.
//

@import Foundation;

typedef NS_ENUM(NSInteger, KTKCloudModelRequests) {
    KTKCloudModelRequestGet    = 1 << 1,
    KTKCloudModelRequestCreate = 1 << 2,
    KTKCloudModelRequestUpdate = 1 << 3,
    KTKCloudModelRequestDelete = 1 << 4,
};

#pragma mark - KTKCloudModel protocol
@protocol KTKCloudModel <NSObject, NSCopying, NSSecureCoding>

/**
 *  Returns a key path for the object's primary key.
 *
 *  @return A key path string object.
 */
@required
+ (NSString*)primaryKey;

/**
 *  Returns the allowed actions options.
 *
 *  @return An allowed actions options.
 */
@required
+ (KTKCloudModelRequests)availableRequests;

@end
