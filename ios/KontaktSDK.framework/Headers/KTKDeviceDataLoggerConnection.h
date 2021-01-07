//
//  KontaktSDK-iOS
//
//  Copyright © 2018 Kontakt.io. All rights reserved.
//

#import "KTKDeviceConnection.h"
#import "KTKDeviceDataLoggerReading.h"

NS_ASSUME_NONNULL_BEGIN

#pragma mark - Completion Blocks

/**
 *  A completion block object to be executed when the data logger reading operation finishes.
 *
 *  @param configuration    The configuration object. Result of the read operation.
 *  @param readings         An array of data logger entries.
 *  @param error            An error object containing the error that indicates why the operation failed.
 */
typedef void (^KTKDeviceDataLoggerConnectionReadBlock)(KTKDeviceConfiguration * _Nullable configuration, NSArray <KTKDeviceDataLoggerReading *> * _Nullable readings, NSError * _Nullable error);

/**
 *  A completion block object to be executed when the data logger clear operation finishes.
 *
 *  @param error            An error object containing the error that indicates why the operation failed.
 */
typedef void (^KTKDeviceDataLoggerConnectionClearBlock)(NSError * _Nullable error);

#pragma mark - KTKDeviceLoggerConnection (Interface)
@interface KTKDeviceDataLoggerConnection : KTKDeviceConnection

#pragma mark - Connection Methods
///--------------------------------------------------------------------
/// @name Connection Methods
///--------------------------------------------------------------------

/**
*  Reads the data from the data logger device.
*
*  @param date              A date until logger data will be recieved. If date is `nil` read will return all available date.
*  @param completion        A block object to be executed when the read operation finishes.
*/
- (void)dataLoggerReadUntil:(NSDate * _Nullable)date completion:(KTKDeviceDataLoggerConnectionReadBlock)completion;

/**
 *  Clears the data from the data logger device.
 *
 *  @param completion       A block object to be executed when the clear operation finishes.
 */
- (void)dataLoggerClearWithCompletion:(KTKDeviceDataLoggerConnectionClearBlock)completion;


@end

NS_ASSUME_NONNULL_END
