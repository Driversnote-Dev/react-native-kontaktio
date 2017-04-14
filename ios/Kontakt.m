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
{
    bool hasListeners;
}

RCT_EXPORT_MODULE(KontaktBeacons)

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

@end
