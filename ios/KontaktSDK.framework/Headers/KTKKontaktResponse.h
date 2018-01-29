//
//  KontaktSDK
//  Version: 1.5.1
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

@import Foundation;

NS_ASSUME_NONNULL_BEGIN

@class KTKKontaktResponse;

/**
 *  A block object to be executed when the cloud API request finishes.
 *
 *  @param response The cloud API response object.
 *  @param error    An error object.
 */
typedef void (^KTKKontaktResponseCompletionBlock)(KTKKontaktResponse * _Nullable response, NSError * _Nullable error);


#pragma mark - KTKKontaktResponse (Interface)
@interface KTKKontaktResponse: NSObject

#pragma mark - Properties
///--------------------------------------------------------------------
/// @name Properties
///--------------------------------------------------------------------

/**
 *  The index of which the result objects start from.
 */
@property (nonatomic, assign, readonly) NSUInteger startIndex;

/**
 *  The limit of the objects in the response.
 */
@property (nonatomic, assign, readonly) NSUInteger maxResult;

/**
 *  The count of the received objects.
 */
@property (nonatomic, assign, readonly) NSUInteger objectsCount;

/**
 *  The array of the objects received from the cloud API.
 */
@property (nonatomic, strong, readonly) NSArray * _Nullable objects;

/**
 *  The URL of the previous result set.
 */
@property (nonatomic, strong, readwrite) NSURL * _Nullable previousResultsURL;

/**
 *  The URL of the next result set.
 */
@property (nonatomic, strong, readwrite) NSURL * _Nullable nextResultsURL;

/**
 *  An HTTP status code of the response.
 */
@property (nonatomic, strong, readonly) NSNumber * _Nullable statusCode;

/**
 *  An ETag HTTP header value of the response.
 */
@property (nonatomic, strong, readonly) NSString * _Nullable ETag;

/**
 *  A raw object of the response. 
 *
 *  When objects property is nil its worth checking raw response.
 */
@property (nonatomic, strong, readonly) id _Nullable rawResponse;

@end

NS_ASSUME_NONNULL_END
