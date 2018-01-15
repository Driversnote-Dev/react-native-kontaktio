//
//  KontaktSDK
//  Version: 1.4.4
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

@import Foundation;

NS_ASSUME_NONNULL_BEGIN

/**
 *  Eddystone Frame type.
 */
typedef NS_ENUM(NSUInteger, KTKEddystoneFrameType) {
    /**
     *  UID Frame type.
     */
    KTKEddystoneFrameTypeUID = 0x00,
    /**
     *  URL Frame type.
     */
    KTKEddystoneFrameTypeURL = 0x10,
    /**
     *  TLM (Telemetry) Frame type.
     */
    KTKEddystoneFrameTypeTLM = 0x20
};

#pragma mark - KTKEddystoneFrame (Protocol)
@protocol KTKEddystoneFrame <NSObject>

#pragma mark - Frame Protocol Properties
///--------------------------------------------------------------------
/// @name Frame Protocol Properties
///--------------------------------------------------------------------

/**
 *  Frame type. (read-only)
 *
 *  @see KTKEddystoneFrameType
 */
@property (nonatomic, assign, readonly) KTKEddystoneFrameType type;

@end

NS_ASSUME_NONNULL_END
