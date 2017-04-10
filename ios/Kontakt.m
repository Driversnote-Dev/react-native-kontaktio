#import "Kontakt.h"

#if __has_include("RCTConvert.h")
  #import "RCTConvert.h"
#else
  #import <React/RCTConvert.h>
#endif

#if __has_include("RCTLog.h")
  #import "RCTLog.h"
#else
  #import <React/RCTLog.h>
#endif


@implementation Kontakt

RCT_EXPORT_MODULE(KontaktBeacons)

- (NSDictionary *)constantsToExport
{
  return @{ @"ANDRE_CONSTANT": @"this-is-super-important" };
}

RCT_EXPORT_METHOD(test)
{
  NSLog(@"This is the first test method of the Kontakt.io package!");
}

@end
