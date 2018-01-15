//
//  KontaktSDK
//  Version: 1.4.4
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

@import Foundation;
#import "KTKEddystoneFrame.h"

NS_ASSUME_NONNULL_BEGIN

#pragma mark - KTKEddystoneURL (Interface)
@interface KTKEddystoneURL : NSObject <KTKEddystoneFrame, NSCopying, NSSecureCoding>

#pragma mark - URL Frame Properties
///--------------------------------------------------------------------
/// @name URL Frame Properties
///--------------------------------------------------------------------

/**
 *  Machine to machine flag. (read-only)
 */
@property (nonatomic, assign, readonly, getter=isMachineToMachine) BOOL machineToMachine;

/**
 *  URL object. (read-only)
 */
@property (nonatomic, strong, readonly) NSURL * _Nullable url;

@end

NS_ASSUME_NONNULL_END
