//
//  KontaktSDK
//  Version: 1.5.1
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

@import Foundation;

#if TARGET_OS_IOS || TARGET_OS_TV
@import UIKit;
#endif

#import "KTKKontaktResponse.h"

@protocol KTKCloudModel;

NS_ASSUME_NONNULL_BEGIN

#pragma mark - External Helper
extern NSDictionary * _Nullable KTKCloudErrorFromError(NSError * _Nullable error);

#pragma mark - KTKCloudClient (Interface)
@interface KTKCloudClient : NSObject

#pragma mark - Initialization Methods
///--------------------------------------------------------------------
/// @name Initialization Methods
///--------------------------------------------------------------------

/**
 *  A shared instance of Cloud client, used by the low-level SDK methods, and suitable for use directly for any ad-hoc requests.
 *
 *  @return A shared instance of a Cloud client.
 */
+ (nonnull instancetype)sharedInstance;

/**
 *  Initializes and returns a cloud client object with the specified session configuration.
 *
 *  @param configuration A configuration object that specifies certain behaviors, such as caching policies, timeouts, proxies, pipelining, TLS versions to support, cookie policies, and credential storage.
 *
 *  @return An initialized cloud client object.
 */
- (instancetype)initWithSessionConfiguration:(NSURLSessionConfiguration*)configuration;

#pragma mark - API Request Methods
///--------------------------------------------------------------------
/// @name API Request Methods
///--------------------------------------------------------------------

/**
 *  Runs a cloud API call with a GET request.
 *
 *  @param endpoint   The cloud API endpoint/resource.
 *  @param dictionary The parameters to be serialized for the request.
 *  @param completion A block object to be executed when the request finishes.
 *
 *  @see KTKKontaktResponseCompletionBlock
 *  @see KTKKontaktResponse
 */
- (void)GET:(NSString*)endpoint parameters:(NSDictionary* _Nullable)dictionary completion:(KTKKontaktResponseCompletionBlock _Nullable)completion;

/**
 *  Runs a cloud API call with a GET request for the specified url object.
 *  
 *  This method is the best candicate for calling next or previous results url.
 *  Please note <code>url</code> must be withing kontakt.io domain.
 *
 *  @param url        The url object for the GET request.
 *  @param completion A block object to be executed when the request finishes.
 *
 *  @see KTKKontaktResponseCompletionBlock
 *  @see KTKKontaktResponse
 *  @see [KTKKontaktResponse previousResultsURL]
 *  @see [KTKKontaktResponse nextResultsURL]
 */
- (void)GET:(NSURL*)url completion:(KTKKontaktResponseCompletionBlock _Nullable)completion;

/**
 *  Runs a cloud API call with a POST request.
 *
 *  @param endpoint   The cloud API endpoint/resource.
 *  @param dictionary The parameters to be serialized for the request.
 *  @param completion A block object to be executed when the request finishes.
 *
 *  @see KTKKontaktResponseCompletionBlock
 *  @see KTKKontaktResponse
 */
- (void)POST:(NSString*)endpoint parameters:(NSDictionary* _Nullable)dictionary completion:(KTKKontaktResponseCompletionBlock _Nullable)completion;

/**
 *  Runs a cloud API call with a POST request encoded for JSON payload.
 *
 *  @param endpoint   The cloud API endpoint/resource.
 *  @param dictionary The parameters to be serialized for the request.
 *  @param completion A block object to be executed when the request finishes.
 *
 *  @see KTKKontaktResponseCompletionBlock
 *  @see KTKKontaktResponse
 */
- (void)JSON:(NSString*)endpoint parameters:(NSDictionary* _Nullable)dictionary completion:(KTKKontaktResponseCompletionBlock _Nullable)completion;

#pragma mark - Objects Request Methods
///--------------------------------------------------------------------
/// @name Objects Request Methods
///--------------------------------------------------------------------

/**
 *  Gets an objects from the cloud API with the specified Class and parameters object.
 *
 *  @param objectClass The Class of an objects to get.
 *  @param parameters  The parameters to be serialized for the request.
 *  @param completion  A block object to be executed when the request finishes.
 */
- (void)getObjects:(Class<KTKCloudModel>)objectClass parameters:(NSDictionary * _Nullable)parameters completion:(KTKKontaktResponseCompletionBlock)completion;

/**
 *  Gets an objects from the cloud API with the specified Class.
 *
 *  @param objectClass The Class of an objects to get.
 *  @param completion  A block object to be executed when the request finishes.
 */
- (void)getObjects:(Class<KTKCloudModel>)objectClass completion:(KTKKontaktResponseCompletionBlock)completion;

/**
 *  Gets an object from the cloud API with the specified Class and primary key value.
 *
 *  @param objectClass The Class of an object to get.
 *  @param value       The primary key value of an object to get.
 *  @param completion  A block object to be executed when the request finishes.
 */
- (void)getObject:(Class<KTKCloudModel>)objectClass primaryKey:(id)value completion:(KTKKontaktResponseCompletionBlock)completion;

/**
 *  Creates specified object in the cloud API.
 *
 *  @param object     The object to be created in the cloud API.
 *  @param completion A block object to be executed when the request finishes.
 */
- (void)createObject:(id<KTKCloudModel>)object completion:(KTKKontaktResponseCompletionBlock)completion;

/**
 *  Updates specified object in the cloud API.
 *
 *  @param object     The object to be updated in the cloud API.
 *  @param completion A block object to be executed when the request finishes.
 */
- (void)updateObject:(id<KTKCloudModel>)object completion:(KTKKontaktResponseCompletionBlock)completion;

/**
 *  Deletes specified object in the cloud API.
 *
 *  @param object     The object to be deleted in the cloud API.
 *  @param completion A block object to be executed when the request finishes.
 */
- (void)deleteObject:(id<KTKCloudModel>)object completion:(KTKKontaktResponseCompletionBlock)completion;

/**
 *  Deletes an object in the cloud API with the specified Class and primary key value.
 *
 *  @param objectClass The Class of an object to delete.
 *  @param value       The primary key value of an object to delete.
 *  @param completion  A block object to be executed when the request finishes.
 */
- (void)deleteObject:(Class<KTKCloudModel>)objectClass primaryKey:(id)value completion:(KTKKontaktResponseCompletionBlock)completion;

@end

NS_ASSUME_NONNULL_END
