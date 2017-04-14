#import "KontaktBeacons.h"

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

#import <KontaktSDK/KontaktSDK.h>

@interface KontaktBeacons() <KTKBeaconManagerDelegate>

@property (strong, nonatomic) KTKBeaconManager *beaconManager;

@end


@implementation KontaktBeacons
{
    bool hasListeners;
}

RCT_EXPORT_MODULE()


#pragma mark Initialization

- (instancetype)init
{
    if (self = [super init]) {
        [Kontakt setAPIKey:@"yourSuperSecretAPIKey"];

        // init of beaconManager has to happen here! I still don't understand why.. but
        // calling it later doesn't work..
        // TODO: Try separating it in two functions. 1. First init then 2. startMonitoring
        self.beaconManager = [[KTKBeaconManager alloc] initWithDelegate:self];
        NSLog(@"beacon manager is initialized!");

        //    self.locationManager = [[CLLocationManager alloc] init];
        //    self.locationManager.delegate = self;
    }

    return self;
}

#pragma mark

- (NSArray<NSString *> *)supportedEvents
{
    return @[@"EventReminder"];
}

- (NSDictionary *)constantsToExport
{
  return @{ @"ANDRE_CONSTANT": @"this-is-super-important" };
}


// Will be called when this module's first listener is added.
-(void)startObserving {
    hasListeners = YES;
    // Set up any upstream listeners or background tasks as necessary
}

// Will be called when this module's last listener is removed, or on dealloc.
-(void)stopObserving {
    hasListeners = NO;
    // Remove upstream listeners, stop unnecessary background tasks
}

- (void)calendarEventReminderReceived:(NSNotification *)notification
{
    NSString *eventName = notification.userInfo[@"name"];
    if (hasListeners) { // Only send events if anyone is listening
        [self sendEventWithName:@"EventReminder" body:@{@"name": eventName}];
    }
}


RCT_EXPORT_METHOD(test)
{
  NSLog(@"This is the first test method of the Kontakt.io package!");
}

// Promise
RCT_REMAP_METHOD(findEvents,
                 findEvents_resolver:(RCTPromiseResolveBlock)resolve
                 findEvents_rejecter:(RCTPromiseRejectBlock)reject)
{
    NSArray *events = @[@"one", @"two", @"three"];
    if (events) {
        resolve(events);
    } else {
        NSError *error;
        reject(@"no_events", @"There were no events", error);
    }
}


// ---------
// BEACONS
// ---------

RCT_REMAP_METHOD(initBeacons,
                 initBeacons_resolver:(RCTPromiseResolveBlock)resolve
                 initBeacons_rejecter:(RCTPromiseRejectBlock)reject)
{
    @try {

        //    [self.beaconManager requestLocationAlwaysAuthorization];

        // define region
        NSUUID *myProximityUUID = [[NSUUID alloc] initWithUUIDString:@"b0702880-a295-a8ab-f734-031a98a512de"];
        KTKBeaconRegion *region1 = [[KTKBeaconRegion alloc] initWithProximityUUID:myProximityUUID identifier:@"Beacon region 1"];


        switch ([KTKBeaconManager locationAuthorizationStatus]) {
            case kCLAuthorizationStatusNotDetermined:
                [self.beaconManager requestLocationAlwaysAuthorization];
                break;

            case kCLAuthorizationStatusDenied:
            case kCLAuthorizationStatusRestricted:
                // No access to Location Services
                break;

            case kCLAuthorizationStatusAuthorizedWhenInUse:
                // For most iBeacon-based app this type of
                // permission is not adequate
                break;

            case kCLAuthorizationStatusAuthorizedAlways:
                if ([KTKBeaconManager isMonitoringAvailable]) {
                    [self.beaconManager startMonitoringForRegion:region1];
                    NSLog(@"called method to start region monitoring!");
                }
                break;
        }
        NSLog(@"current status: %d", [KTKBeaconManager locationAuthorizationStatus]);
        resolve(@"yeah baby - initialized");
    } @catch (NSException *exception) {
        NSError *error;
        reject(@"not_init", @"Sorry no init for you", error);
    } @finally {
        // Nothing
    }

}


- (void)beaconManager:(KTKBeaconManager *)manager didChangeLocationAuthorizationStatus:(CLAuthorizationStatus)status {
    if (status == kCLAuthorizationStatusAuthorizedAlways) {
        // When status changes to kCLAuthorizationStatusAuthorizedAlways
        // e.g. after calling [self.beaconManager requestLocationAlwaysAuthorization]
        // we can start region monitoring from here
        NSLog(@"you have always authorization!");
    }
}

- (void)beaconManager:(KTKBeaconManager *)manager didStartMonitoringForRegion:(__kindof KTKBeaconRegion *)region {
    // Do something when monitoring for a particular
    // region is successfully initiated
    NSLog(@"Beacons: didStartMonitoringForRegion");
}

- (void)beaconManager:(KTKBeaconManager *)manager monitoringDidFailForRegion:(__kindof KTKBeaconRegion *)region withError:(NSError *)error {
    // Handle monitoring failing to start for your region
    NSLog(@"Beacons: monitoringDidFailForRegion");
}

- (void)beaconManager:(KTKBeaconManager *)manager didEnterRegion:(__kindof KTKBeaconRegion *)region {
    // Decide what to do when a user enters a range of your region; usually used
    // for triggering a local notification and/or starting a beacon ranging
    NSLog(@"Beacons: didEnterRegion");
    [manager startRangingBeaconsInRegion:region];
}

- (void)beaconManager:(KTKBeaconManager *)manager didExitRegion:(__kindof KTKBeaconRegion *)region {
    // Decide what to do when a user exits a range of your region; usually used
    // for triggering a local notification and stoping a beacon ranging
    NSLog(@"Beacons: didExitRegion");
    [manager stopRangingBeaconsInRegion:region];
}

@end
