//
//  KontaktSDK
//  Version: 1.4.4
//
//  Copyright © 2015 Kontakt.io. All rights reserved.
//

@import CoreLocation;

#import "KTKCloudModel.h"
#import "KTKActionContent.h"
#import "KTKCloudDefinitions.h"

#if TARGET_OS_IOS
typedef CLProximity Proximity;
#else
typedef KTKProximity Proximity;
#endif

NS_ASSUME_NONNULL_BEGIN

/**
 *  Action type.
 */
typedef NS_ENUM(NSInteger, KTKActionType) {
    /**
     *  Action type is invalid.
     */
    KTKActionTypeInvalid = -1,
    /**
     *  Content action type.
     */
    KTKActionTypeContent = 1,
    /**
     *  Browser/URL action type.
     */
    KTKActionTypeBrowser = 2,
};

#pragma mark - KTKAction (Interface)
@interface KTKAction : NSObject <KTKCloudModel>

#pragma mark - Content Properties
///--------------------------------------------------------------------
/// @name Content Properties
///--------------------------------------------------------------------

/**
 *  Action identifier. (read-only)
 */
@property (nonatomic, strong, readonly) NSUUID *actionID;

/**
 *  Type of the action. (read-only)
 */
@property (nonatomic, assign, readonly) KTKActionType type;

/**
 *  The proximity on which action should be triggered. (read-only)
 */
@property (nonatomic, assign, readonly) Proximity proximity;

/**
 *  An array of devices unique identifiers assigned to the action. (read-only)
 */
@property (nonatomic, strong, readonly) NSArray <NSString*>* _Nullable devicesUniqueID;

#pragma mark - Action Type URL
///--------------------------------------------------------------------
/// @name Action Type URL
///--------------------------------------------------------------------

/**
 *  A url of the action. Nil when action type is equal to <code><KTKActionTypeContent></code> (read-only)
 */
@property (nonatomic, strong, readonly) NSURL * _Nullable url;

#pragma mark - Action Type Content
///--------------------------------------------------------------------
/// @name Action Type Content
///--------------------------------------------------------------------

/**
 *  A content object of the action. Nil when action type is equal to <code><KTKActionTypeBrowser></code> (read-only)
 */
@property (nonatomic, strong, readonly) KTKActionContent * _Nullable content;

@end

NS_ASSUME_NONNULL_END
