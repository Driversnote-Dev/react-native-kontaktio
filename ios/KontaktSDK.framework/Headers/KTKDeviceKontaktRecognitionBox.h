//
//  KontaktSDK-iOS
//
//  Copyright © 2021 Kontakt.io. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#pragma mark -

#pragma mark - KTKDeviceKontaktRecognitionBox (Interface)
@interface KTKDeviceKontaktRecognitionBox : NSObject <NSCopying>

@property (nonatomic, assign, readonly) NSUInteger score;
@property (nonatomic, assign, readonly) NSUInteger x;
@property (nonatomic, assign, readonly) NSUInteger y;
@property (nonatomic, assign, readonly) NSUInteger width;
@property (nonatomic, assign, readonly) NSUInteger height;

- (nullable instancetype)initWithData:(NSData * _Nullable)data;

@end

NS_ASSUME_NONNULL_END
