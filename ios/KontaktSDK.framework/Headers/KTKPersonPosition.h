//
//  KontaktSDK-iOS
//
//  Copyright © 2021 Kontakt.io. All rights reserved.
//

#import <Foundation/Foundation.h>
#pragma mark -

#pragma mark - KTKPersonPosition (Interface)
NS_ASSUME_NONNULL_BEGIN

@interface KTKPersonPosition : NSObject <NSCopying>
@property (nonatomic, assign, readonly) NSUInteger x;
@property (nonatomic, assign, readonly) NSUInteger y;

- (nullable instancetype)initWithData:(NSData * _Nullable)data;
- (nullable instancetype)init: (NSUInteger) y : (NSUInteger)x;

@end

NS_ASSUME_NONNULL_END
