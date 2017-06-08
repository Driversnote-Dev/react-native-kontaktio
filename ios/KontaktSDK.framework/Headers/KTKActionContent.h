//
//  KontaktSDK
//  Version: 1.4.4
//
//  Copyright © 2015 Kontakt.io. All rights reserved.
//

@import Foundation;

NS_ASSUME_NONNULL_BEGIN

/**
 *  Action content type.
 */
typedef NS_ENUM(NSInteger, KTKActionContentType) {
    /**
     *  Content type is invalid.
     */
    KTKActionContentTypeInvalid = -1,
    /**
     *  Image content type.
     */
    KTKActionContentTypeImage   = 1,
    /**
     *  Video content type.
     */
    KTKActionContentTypeVideo   = 2,
    /**
     *  Audio content type.
     */
    KTKActionContentTypeAudio   = 3,
    /**
     *  Text file content type.
     */
    KTKActionContentTypeText    = 4
};

#pragma mark - KTKActionContent (Interface)
@interface KTKActionContent : NSObject <NSObject, NSCopying, NSSecureCoding>

#pragma mark - Content Properties
///--------------------------------------------------------------------
/// @name Content Properties
///--------------------------------------------------------------------

/**
 *  Action content's type. (read-only)
 */
@property (nonatomic, assign, readonly) KTKActionContentType type;

/**
 *  Specific mime type of the content. (read-only)
 */
@property (nonatomic, strong, readonly) NSString *mimeType;

/**
 *  A boolean flag indicating whether content file is being converted now. (read-only)
 */
@property (nonatomic, assign, readonly, getter=isConverting) BOOL converting;

/**
 *  The URL object of content data. (read-only)
 */
@property (nonatomic, strong, readonly) NSURL * _Nullable contentURL;

#pragma mark - Model Methods
///--------------------------------------------------------------------
/// @name Model Methods
///--------------------------------------------------------------------

/**
 *  Downloads the action's content data.
 *
 *  @param completion A block object to be executed when a download process finishes.
 */
- (void)downloadContentDataWithCompletion:(void(^)( NSData * _Nullable, NSError * _Nullable ))completion;

@end

NS_ASSUME_NONNULL_END
