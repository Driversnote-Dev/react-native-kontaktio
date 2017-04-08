#import "Kontakt.h"
#import <React/RCTLog.h>
#import <React/RCTConvert.h>

@interface Kontakt() <KTKBeaconManagerDelegate>

@property (strong, nonatomic) KTKBeaconManager *beaconManager;

@end


@implementation Kontakt

RCT_EXPORT_MODULE(KontaktModule)

- (NSDictionary *)constantsToExport
{
  return @{ @"ANDRE_CONSTANT": @"this-is-super-important" };
}

RCT_EXPORT_METHOD(test)
{
  NSLog(@"This is the first test method of the Kontakt.io package!");
}

@end
