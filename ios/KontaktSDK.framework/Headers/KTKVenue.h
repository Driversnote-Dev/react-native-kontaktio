//
//  KontaktSDK
//  Version: 1.4.4
//
//  Copyright © 2015 Kontakt.io. All rights reserved.
//

#import "KTKCloudModel.h"

#if TARGET_OS_IOS || TARGET_OS_TV
#import <UIKit/UIImage.h>
typedef UIImage KTKImage;
#elif TARGET_OS_MAC
#import <AppKit/NSImage.h>
typedef NSImage KTKImage;
#endif

NS_ASSUME_NONNULL_BEGIN

/**
 *  A venue access rights.
 */
typedef NS_ENUM(NSInteger, KTKVenueAccess) {
    /**
     *  Invalid value.
     */
    KTKVenueAccessInvalid   = -1,
    /**
     *  Owner
     */
    KTKVenueAccessOwner      = 1,
    /**
     *  Supervisor
     */
    KTKVenueAccessSupervisor = 2,
    /**
     *  Viewer
     */
    KTKVenueAccessViewer     = 3
};

#pragma mark - KTKVenue (Interface)
@interface KTKVenue : NSObject <KTKCloudModel>

#pragma mark - Venue Properties
///--------------------------------------------------------------------
/// @name Venue Properties
///--------------------------------------------------------------------

/**
 *  Venue identifier. (read-only)
 */
@property (nonatomic, strong, readonly) NSUUID *venueID;

/**
 *  Venue name. (read-only)
 */
@property (nonatomic, strong, readonly) NSString * _Nullable venueName;

/**
 *  Venue description text. (read-only)
 */
@property (nonatomic, strong, readonly) NSString * _Nullable venueDescription;

/**
 *  Venue meta data. (read-only)
 */
@property (nonatomic, strong, readonly) NSDictionary * _Nullable meta;

/**
 *  The number of devices assigned to the venue. (read-only)
 */
@property (nonatomic, strong, readonly) NSNumber *devicesCount;

/**
 *  Venue manager's identifier. (read-only)
 */
@property (nonatomic, strong, readonly) NSUUID *managerID;

/**
 *  Venue access rights. (read-only)
 *
 *  @see KTKVenueAccess
 */
@property (nonatomic, assign, readonly) KTKVenueAccess access;

/**
 *  The latitude of the venue.
 */
@property (nonatomic, strong, readonly) NSNumber * _Nullable latitude;

/**
 *  The longitude of the venue.
 */
@property (nonatomic, strong, readonly) NSNumber * _Nullable longitude;

#pragma mark - Model Methods
///--------------------------------------------------------------------
/// @name Model Methods
///--------------------------------------------------------------------

/**
 *  Downloads the firmware bin data.
 *
 *  @param completion A block object to be executed when a download process finishes.
 */
- (void)venueCoverImageWithCompletion:(void(^)(KTKImage * _Nullable, NSError * _Nullable))completion;

@end

NS_ASSUME_NONNULL_END
