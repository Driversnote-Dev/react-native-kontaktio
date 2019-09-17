//
//  KontaktSDK
//  Version: 1.5.1
//
//  Copyright © 2017 Kontakt.io. All rights reserved.
//

#import "KTKCloudModel.h"
#import "KTKCloudDefinitions.h"
#import "KTKTriggerContext.h"

/**
 *  Trigger type.
 */
typedef NS_ENUM(NSInteger, KTKTriggerType) {
    /**
     *  Trigger type is invalid.
     */
    KTKTriggerTypeInvalid = -1,
    /**
     *  Beacon detected trigger type.
     */
    KTKTriggerTypeBeaconDetected = 1,
    /**
     *  Beacon lost trigger type.
     */
    KTKTriggerTypeBeaconLost = 2,
};

/**
 *  Trigger executor.
 */
typedef NS_ENUM(NSInteger, KTKTriggerExecutor) {
    /**
     *  Executor type is invalid.
     */
    KTKTriggerExecutorInvalid = -1,
    /**
     *  Local executor type.
     */
    KTKTriggerExecutorLocal = 1,
    /**
     *  Cloud executor type.
     */
    KTKTriggerExecutorCloud = 2,
    /**
     *  Proximity SDK executor type.
     */
    KTKTriggerExecutorProximitySDK = 3,
};

NS_ASSUME_NONNULL_BEGIN

#pragma mark - KTKTrigger (Interface)
@interface KTKTrigger : NSObject <KTKCloudModel>

#pragma mark - Trigger Properties
///--------------------------------------------------------------------
/// @name Trigger Properties
///--------------------------------------------------------------------

/**
 *  Trigger identifier. (read-only)
 */
@property (nonatomic, strong, readonly) NSUUID *triggerID;

/**
 *  Trigger's name. (read-only)
 */
@property (nonatomic, strong, readonly) NSString * _Nullable name;

/**
 *  An array of activities identifiers assigned to the trigger. (read-only)
 */
@property (nonatomic, strong, readonly) NSArray <NSString*>* _Nullable activitiesIDs;

/**
 *  Type of the trigger. (read-only)
 */
@property (nonatomic, assign, readonly) KTKTriggerType type;

/**
 *  Trigger's context. (read-only)
 */
@property (nonatomic, strong, readonly) KTKTriggerContext *context;

/**
 *  Trigger's executor. (read-only)
 */
@property (nonatomic, assign, readonly) KTKTriggerExecutor executor;

@end

NS_ASSUME_NONNULL_END
