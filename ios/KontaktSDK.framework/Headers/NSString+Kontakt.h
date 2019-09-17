//
//  KontaktSDK
//  Version: 1.5.1
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

@import Foundation;

#pragma mark - NSString (Kontakt)
@interface NSString (Kontakt)

#pragma mark - Hashing Helpers Methods
///--------------------------------------------------------------------
/// @name Hashing Helpers Methods
///--------------------------------------------------------------------

/**
 *  Returns string's MD5 hash
 *
 *  @return The string's MD5 hash
 */
- (NSString*)ktk_MD5;

#pragma mark - Version Helpers Methods
///--------------------------------------------------------------------
/// @name Version Helpers Methods
///--------------------------------------------------------------------

/**
 *  Matches the semantic formatted version string object with a given version string.
 *
 *  @param versionString The semantic formatted version string.
 *
 *  @return <code>YES</code> if the version matches or <code>NO</code> if it is not. 
 */
- (BOOL)ktk_matchVersion:(NSString*)versionString;

@end
