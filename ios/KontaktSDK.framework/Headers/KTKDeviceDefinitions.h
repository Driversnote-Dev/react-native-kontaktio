//
//  KontaktSDK
//  Version: 3.1.0
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

@import Foundation;

#if __IPHONE_OS_VERSION_MAX_ALLOWED >= 100000 || __TV_OS_VERSION_MAX_ALLOWED >= 100000
#else
#define CBManagerState CBCentralManagerState
#define CBManagerStateUnknown CBCentralManagerStateUnknown
#define CBManagerStateResetting CBCentralManagerStateResetting
#define CBManagerStateUnsupported CBCentralManagerStateUnsupported
#define CBManagerStateUnauthorized CBCentralManagerStateUnauthorized
#define CBManagerStatePoweredOff CBCentralManagerStatePoweredOff
#define CBManagerStatePoweredOn CBCentralManagerStatePoweredOn
#endif

/**
 *  Device Connection Operation Types
 */
typedef NS_ENUM(NSInteger, KTKDeviceConnectionOperationType) {
    /**
     *  Type Unknown.
     */
    KTKDeviceConnectionOperationTypeUnknown = -1,
    /**
     *  Read Operation.
     */
    KTKDeviceConnectionOperationTypeRead    = 1,
    /**
     *  Write Operation.
     */
    KTKDeviceConnectionOperationTypeWrite   = 2,
    /**
     *  DFU Operation.
     */
    KTKDeviceConnectionOperationTypeDFU     = 3,
    /**
     *  Notification Operation.
     */
    KTKDeviceConnectionOperationTypeNotify     = 4
};

/**
 *  Configuration Profile Generator Types
 */
typedef NS_ENUM(NSInteger, KTKConfigProfileGenerator) {
    /**
     *  Generate using Cloud Only API Key required.
     */
    KTKConfigProfileGeneratorUsingCloud       = 1,
    
    /**
     *  Generate using KTKDeviceCredentails.
     */
    KTKConfigProfileGeneratorUsingCredentials = 2
};

/**
 *  A Kontakt device type.
 */
typedef NS_ENUM(NSInteger, KTKDeviceType) {
    /**
     *  Invalid device type.
     */
    KTKDeviceTypeInvalid     = -1,
    /**
     *  Beacon device type.
     */
    KTKDeviceTypeBeacon      = 1,
    /**
     *  Cloud Beacon device type.
     */
    KTKDeviceTypeCloudBeacon = 2,
    /**
     *  Gateway device type.
     */
    KTKDeviceTypeGateway = 3
    
};

/**
 *  A Kontakt image type.
 */
typedef NS_ENUM(uint16_t, KTKKontaktImageType) {
    KTKKontaktImageRAW                     ,
    KTKKontaktImageRAWContinuous           ,
    KTKKontaktImageCalibration             ,
    KTKKontaktImageRecalibration           
};

/**
 *  Legacy devices Advertising Profile
 */
typedef NS_ENUM(NSInteger, KTKDeviceAdvertisingProfile) {
    /**
     *  Invalid Profile.
     */
    KTKDeviceAdvertisingProfileInvalid   = -1,
    /**
     *  iBeacon Profile.
     */
    KTKDeviceAdvertisingProfileIBeacon   = 1,
    /**
     *  Eddystone Profile.
     */
    KTKDeviceAdvertisingProfileEddystone = 2
};

/**
 *  A device Advertising Packets
 */
typedef NS_OPTIONS(NSInteger, KTKDeviceAdvertisingPackets) {
    /**
     *  Ivalid packet.
     */
    KTKDeviceAdvertisingPacketsInvalid         = 1 << 0,
    /**
     *  iBeacon packet.
     */
    KTKDeviceAdvertisingPacketsIBeacon         = 1 << 1,
    /**
     *  Eddystone UID packet.
     */
    KTKDeviceAdvertisingPacketsEddystoneUID    = 1 << 2,
    /**
     *  Eddystone URL packet.
     */
    KTKDeviceAdvertisingPacketsEddystoneURL    = 1 << 3,
    /**
     *  Eddystone Telemetry packet.
     */
    KTKDeviceAdvertisingPacketsEddystoneTLM    = 1 << 4,
    /**
     *  Eddystone Telemetry packet.
     */
    KTKDeviceAdvertisingPacketsEddystoneEID    = 1 << 5,
    /**
     *  Eddystone Telemetry packet.
     */
    KTKDeviceAdvertisingPacketsEddystoneETLM   = 1 << 6,
    /**
     *  Kontakt identification packet.
     */
    KTKDeviceAdvertisingPacketsKontakt         = 1 << 7,
    /**
     *  Kontakt identification packet.
     */
    KTKDeviceAdvertisingPacketsKontaktTLM      = 1 << 8,
    /**
     *  iBeacon Button packet.
     */
    KTKDeviceAdvertisingPacketsIBeaconButton   = 1 << 9,
    /**
     *  Kontakt Location packet.
     */
    KTKDeviceAdvertisingPacketsKontaktLocation = 1 << 10,
    /**
     *  Kontakt Location packet.
     */
    KTKDeviceAdvertisingPacketsKontaktPeopleDetectionFrame   = 1 << 13,
    /**
     *  All supprted Eddystone packets.
     */
    KTKDeviceAdvertisingPacketsEddystoneAll    = (NSInteger)0b00000000000000000000000000011100,
    /**
     *  All supprted Eddystone Secure (EID + ETLM).
     */
    KTKDeviceAdvertisingPacketsEddystoneSecure = (NSInteger)0b00000000000000000000000001100000,
    /**
     *  All supprted packets.
     */
    KTKDeviceAdvertisingPacketsAll             = (NSInteger)0b11111111111111111111111111111110
};

/**
 *  A device Telemetry Fields
 */
typedef NS_OPTIONS(NSInteger, KTKDeviceTelemetryFields) {
    /**
     *  Raw Accelerometer.
     */
    KTKDeviceTelemetryFieldsRawAccelerometer                = 1 << 0,
    /**
     *  Movement Threshold Event.
     */
    KTKDeviceTelemetryFieldsMovementThresholdEvent          = 1 << 1,
    /**
     *  Double Tap Event.
     */
    KTKDeviceTelemetryFieldsDoubleTapEvent                  = 1 << 2,
    /**
     *  Tap Event.
     */
    KTKDeviceTelemetryFieldsTapEvent                        = 1 << 3,
    /**
     *  Light Level.
     */
    KTKDeviceTelemetryFieldsLightLevel                      = 1 << 4, //
    /**
     *  Temperature.
     */
    KTKDeviceTelemetryFieldsTemperature                     = 1 << 5,
    /**
     *  Battery.
     */
    KTKDeviceTelemetryFieldsBattery                         = 1 << 6,
    /**
     *  Button Click.
     */
    KTKDeviceTelemetryFieldsButtonClick                     = 1 << 7,
    /**
     *  Button Double Click.
     */
    KTKDeviceTelemetryFieldsButtonDoubleClick               = 1 << 8,
    /**
     *  UTC Time.
     */
    KTKDeviceTelemetryFieldsUTCTime                         = 1 << 9,
    /**
     *  Logging Enabled.
     */
    KTKDeviceTelemetryFieldsLoggingEnabled                  = 1 << 10,
    /**
     *  Identified Button Click.
     */
    KTKDeviceTelemetryFieldsIdentifiedButtonClick           = 1 << 11,
    /**
     *  Humidity.
     */
    KTKDeviceTelemetryFieldsHumidity                        = 1 << 12,
    /**
     *  Temperature 16 bits.
     */
    KTKDeviceTelemetryFieldsTemperature16bits               = 1 << 13,
    /**
     *  BLE channel.
     */
    KTKDeviceTelemetryFieldsBLEChannel                      = 1 << 14,
    /**
     *  Gpio. - depricate
     */
    KTKDeviceTelemetryFieldsGpio                            = 1 << 15,
    /**
     *  Movement event.
     */
    KTKDeviceTelemetryFieldsMovementEvent                   = 1 << 16,
    /**
     *  Air Pressure.
     */
    KTKDeviceTelemetryFieldsAirPressure                     = 1 << 17,
    /**
     *  PIR detection.
     */
    KTKDeviceTelemetryFieldsPIRDetection                    = 1 << 18,
    /**
     *  Two button info.
     */
    KTKDeviceTelemetryFieldsTwoButtonInfo                   = 1 << 19, //
    /**
     *  Air Quality.
     */
    KTKDeviceTelemetryFieldsAirQuality                      = 1 << 20,
    /**
     *  Room number.
     */
    KTKDeviceTelemetryFieldsRoomNumber                      = 1 << 21,
    /**
     *  Occupancy.
     */
    KTKDeviceTelemetryFieldsOccupancy                       = 1 << 22,
    /**
     *  BLE scan result.
     */
    KTKDeviceTelemetryFieldsBLEScanResult                   = 1 << 23,
    
    /**
     *  Proximity report.
     */
    KTKDeviceTelemetryFieldsProximityReport                 = 1 << 24,
    
    /**
     *  Gas Sensor.
     */
    KTKDeviceTelemetryFieldsGasSensor                       = 1 << 25,
    
    /**
     *  Light level lux.
     */
    KTKDeviceTelemetryFieldsLightLevelLux                   = 1 << 26,
    
    /**
     *  Inout counter.
     */
    KTKDeviceTelemetryFieldsInOutCount                      = 1 << 27,
    
    /**
     *  Soap dispenser.
     */
    KTKDeviceTelemetryFieldsSoapDispenser                   = 1 << 28,
    
    /**
     *  People Detection.
     */
    KTKDeviceTelemetryFieldsPeopleDetection                 = 1 << 29,
    
    /**
     *  RSSI Scan.
     */
    KTKDeviceTelemetryFieldsRSSIScan                        = 1 << 30,
    
    /**
     *  All supprted packets.
     */
    KTKDeviceTelemetryFieldsAll                             = (NSInteger)0b111111111111111111111111
};

/**
 *  A device access rights.
 */
typedef NS_ENUM(NSInteger, KTKDeviceAccess) {
    /**
     *  Invalid value.
     */
    KTKDeviceAccessInvalid   = -1,
    /**
     *  Owner
     */
    KTKDeviceAccessOwner      = 1,
    /**
     *  Supervisor
     */
    KTKDeviceAccessSupervisor = 2,
    /**
     *  Editor
     */
    KTKDeviceAccessEditor     = 3,
    /**
     *  Viewer
     */
    KTKDeviceAccessViewer     = 4
};

/**
 *  A kontakt device specification.
 */
typedef NS_ENUM(NSInteger, KTKDeviceSpecification) {
    /**
     *  Invalid value.
     */
    KTKDeviceSpecificationInvalid  = -1,
    /**
     *  Standard specification.
     */
    KTKDeviceSpecificationStandard = 1,
    /**
     *  Tough Beacon specification.
     */
    KTKDeviceSpecificationTough = 2
};

/**
 *  A kontakt device models.
 */
typedef NS_ENUM(NSInteger, KTKDeviceModel) {
    /**
     *  Invalid value.
     */
    KTKDeviceModelInvalid  = -1,
    /**
     *  Unknown model.
     */
    KTKDeviceModelUnknown  = 0,
    /**
     *  Smart Beacon
     */
    KTKDeviceModelSmartBeacon = 1,
    /**
     *  USB Beacon
     */
    KTKDeviceModelUSBBeacon = 2,
    /**
     *  Sensor Beacon
     */
    KTKDeviceModelSensorBeacon = 3,
    /**
     *  Cloud Beacon
     */
    KTKDeviceModelCloudBeacon = 4,
    /**
     *  Card Beacon
     */
    KTKDeviceModelCardBeacon = 5,
    /**
     *  Pro Beacon
     */
    KTKDeviceModelProBeacon = 6,
    /**
     *  Gateway
     */
    KTKDeviceModelGateway = 7,
    /**
     *  Tag Beacon
     */
    KTKDeviceModelTagBeacon = 8,
    /**
     *  Smart Beacon 3 (Retrofit)
     */
    KTKDeviceModelSmartBeacon3 = 9,
    /**
     *  Heavy Duty Beacon
     */
    KTKDeviceModelHeavyDutyBeacon = 10,
    /**
     *  Card Beacon 2
     */
    KTKDeviceModelCardBeacon2 = 11,
    /**
     *  Coin Tag
     */
    KTKDeviceModelCoinTag = 12,
    /**
     *  Humidity Beacon
     */
    KTKDeviceModelSmartBeacon3H = 13,
    /**
     * Tough Beacon 2
     */
    KTKDeviceModelToughBeacon2 = 14,
    /**
     *  Bracelet Tag
     */
    KTKDeviceModelBraceletTag = 15,
    /**
     *  Universal Tag
     */
    KTKDeviceModelUniversalTag = 16,
    /**
     *  Bracelet Tag 2
     */
    KTKDeviceModelBraceletTag2 = 17,
    /**
     *  Minew E5
     */
    KTKDeviceModelTT20 = 19,
    /**
     *  Beacon TT 20
     */
    KTKDeviceModelMinewE5 = 20,
    /**
     *  Minew E7
     */
    KTKDeviceModelMinewE7 = 21,
    /**
     *  Minew E8
     */
    KTKDeviceModelMinewE8 = 22,
    /**
     *  Minew i3
     */
    KTKDeviceModelMinewI3 = 23,
    /**
     *  Minew i7
     */
    KTKDeviceModelMinewI7 = 24,
    /**
     *  Minew S1
     */
    KTKDeviceModelMinewS1 = 25,
    /**
     *  Lanyard Tag
     */
    KTKDeviceModelLanyardTag = 26,
    /**
     *  Nano Tag
     */
    KTKDeviceModelNanoTag = 27,
    /**
     *  Puck Beacon
     */
    KTKDeviceModelPuckBeacon = 28,
    /**
     *  Portal Light
     */
    KTKDeviceModelPortalLight = 29,
    /**
     *  Smart Badge
     */
    KTKDeviceModelSmartBadge = 30,
    /**
     *  Portal Beam
     */
    KTKDeviceModelPortalBeam = 31,
    /**
     *  Nano Series
     */
    KTKDeviceModelNanoSeries = 32,
    /**
     *  Asset Tag 2
     */
    KTKDeviceModelAssetTag2 = 33,
    /**
     *  Anchor Beacon
     */
    KTKDeviceModelAnchorBeacon2 = 34,
    /**
     *  Mini Beam
     */
    KTKDeviceModelMiniBeam = 35,
    /**
     *  Portal Beam IR
     */
    KTKDeviceModelPortalBeamIR = 36,
    /**
     *  Dispenser Beacon
     */
    KTKDeviceModelDispenserBeacon = 37,
    /**
     *  Portal Light 2S
     */
    KTKDeviceModelPortalLight2S = 38,
    /**
     *  Portal Light 2
     */
    KTKDeviceModelPortalLight2 = 39,
    /**
     *  Asset Tag 2 Mini
     */
    KTKDeviceModelAssetTag2Mini = 40,
    
    /**
     *  Partner provided name
     */
    KTKDeviceModelPartnerDevice = 128
};

/**
 *  A kontakt device symbols.
 */
typedef NS_ENUM(NSInteger, KTKDeviceSymbol) {
    KTKDeviceSymbolInvalid  = -1,
    KTKDeviceSymbolUnknown,
    KTKDeviceSymbolSB16_2,
    KTKDeviceSymbolTB15_1,
    KTKDeviceSymbolGW14_1,
    KTKDeviceSymbolUB16_2,
    KTKDeviceSymbolCT16_2,
    KTKDeviceSymbolGW16_2,
    KTKDeviceSymbolBP16_3,
    KTKDeviceSymbolS18_3,
    KTKDeviceSymbolSB18_3,
    KTKDeviceSymbolHD18_3,
    KTKDeviceSymbolCT18_3,
    KTKDeviceSymbolC18_3,
    KTKDeviceSymbolSB18_3H,
    KTKDeviceSymbolTB18_2,
    KTKDeviceSymbolBT18_3,
    KTKDeviceSymbolUT19_1,
    KTKDeviceSymbolBT19_4,
    KTKDeviceSymbolTT20_1 = 19,
    KTKDeviceSymbolM_E5 = 20,
    KTKDeviceSymbolM_E7 = 21,
    KTKDeviceSymbolM_E8 = 22,
    KTKDeviceSymbolM_I3 = 23,
    KTKDeviceSymbolM_I7 = 24,
    KTKDeviceSymbolM_S1 = 25,
    KTKDeviceSymbolLB20_1 = 26,
    KTKDeviceSymbolBT20_1 = 27,
    KTKDeviceSymbolPB20_1 = 28,
    KTKDeviceSymbolGW20_1 = 29,
    KTKDeviceSymbolSMBA_1 = 30,
    KTKDeviceSymbolPOBE_1 = 31,
    KTKDeviceSymbolNASE_1 = 32,
    KTKDeviceSymbolAST_2 = 33,
    KTKDeviceSymbolANB_2 = 34,
    KTKDeviceSymbolMB = 35,
    KTKDeviceSymbolPB_IR = 36,
    KTKDeviceSymbolDB = 37,
    KTKDeviceSymbolPL_2S = 38,
    KTKDeviceSymbolPL_2 = 39,
    KTKDeviceSymbolAST_2_M = 40,
    
    KTKDeviceSymbolPD = 128
};

/**
 *  A kontakt device channels status.
 */
typedef NS_ENUM(NSInteger, KTKDeviceBLEChannel) {
    /**
     *  Channel is unknown.
     */
    KTKDeviceBLEChannelUknown        = -1,
    /**
     *  Device supported all channels.
     */
    KTKDeviceBLEChannelALL          = 0,
    /**
     *  Device status is channel 37.
     */
    KTKDeviceBLEChannel37            = 37,
    /**
     *  Device status is channel 38.
     */
    KTKDeviceBLEChannel38            = 38,
    
    /**
     *  Device status is channel 39.
     */
    KTKDeviceBLEChannel39            = 39
};

/**
 *  A kontakt device filtering Class.
 */
typedef NS_ENUM(NSInteger, KTKDeviceFilteringClass) {
    /**
     *  Class is unknown.
     */
    KTKDeviceFilteringClassUknown        = -1,
    /**
     *  Device status flitering class  Kontakt.
     */
    KTKDeviceFilteringClassKtk           = 1,
    /**
     *  Device status flitering class  iBeacon, Eddystone, Kontakt .
     */
    KTKDeviceFilteringClassIbEidKtk      = 7,
    /**
     *  Device supported all classes.
     */
    KTKDeviceFilteringClassALL           = 15
};

/**
 *  A kontakt device shuffle status.
 */
typedef NS_ENUM(NSInteger, KTKDeviceShuffleStatus) {
    /**
     *  Status is unknown.
     */
    KTKDeviceShuffleStatusUknown        = -1,
    /**
     *  Device shuffle is not supported.
     */
    KTKDeviceShuffleStatusNotSupported  = 0,
    /**
     *  Device shuffle status is ON.
     */
    KTKDeviceShuffleStatusON            = 1,
    /**
     *  Device shuffle status is OFF.
     */
    KTKDeviceShuffleStatusOFF           = 2
};

/**
 *  A device transmission power level.
 *
 *  @see https://support.kontakt.io/hc/en-gb/articles/201621521-Transmission-power-settings
 */
typedef NS_ENUM(NSInteger, KTKDeviceTransmissionPower) {
    /**
     *  Invalid value
     */
    KTKDeviceTransmissionPowerInvalid = -1,
    /**
     *  Transmission power level 0 (-30dBm).
     */
    KTKDeviceTransmissionPower0,
    /**
     *  Transmission power level 1 (-20dBm).
     */
    KTKDeviceTransmissionPower1,
    /**
     *  Transmission power level 2 (-16dBm).
     */
    KTKDeviceTransmissionPower2,
    /**
     *  Transmission power level 3 (-12dBm).
     */
    KTKDeviceTransmissionPower3,
    /**
     *  Transmission power level 4 (-8dBm).
     */
    KTKDeviceTransmissionPower4,
    /**
     *  Transmission power level 5 (-4dBm).
     */
    KTKDeviceTransmissionPower5,
    /**
     *  Transmission power level 6 (0dBm).
     */
    KTKDeviceTransmissionPower6,
    /**
     *  Transmission power level 7 (4dBm).
     */
    KTKDeviceTransmissionPower7,
};

/**
 *  A device motion detection modes.
 */
typedef NS_ENUM(NSInteger, KTKDeviceMotionDetectionMode) {
    /**
     *  Invalid mode.
     */
    KTKDeviceMotionDetectionModeInvalid  = -1,
    /**
     *  Motion detection is off.
     */
    KTKDeviceMotionDetectionModeOff      = 0,
    /**
     *  Motion detection is set in counting mode.
     * 
     *  You can access counter value by reading device configuration.
     *  
     *  @see [KTKDeviceConfiguration motionCounter]
     */
    KTKDeviceMotionDetectionModeCounting = 1,
    /**
     *  Motion detection is set in alarm mode.
     *
     *  When motion is detected device will advertise `4b6f6e74-616b-742e-696f-4d6f74696f6e` proximity UUID.
     *  Major and minor values will remain the same.
     */
    KTKDeviceMotionDetectionModeAlarm    = 2
};

typedef NS_ENUM(NSInteger, KTKDeviceOccupancyModel) {
    /**
     *  Invalid mode.
     */
    KTKDeviceOccupancyModeInvalid  = -1,
    /**
     *  Occupancy Mode is occupancy 1.
     */
    KTKDeviceOccupancyModeOccupancy1     = 0,
    /**
     *  Occupancy Mode is occupancy 2.
     */
    
    KTKDeviceOccupancyModeOccupancy2    =  1,
    /**
     *  MOccupancy Mode is footfall door.
     */
    
    KTKDeviceOccupancyModeFootfallDoor = 2,
    /**
     *  Occupancy Mode is footfall corridor.
     */
    KTKDeviceOccupancyModeFootfallCorridor    = 3
};

/**
 *  A device data logger fields.
 */
typedef NS_OPTIONS(uint32_t, KTKDeviceDataLoggerFields) {
    KTKDeviceDataLoggerFieldsTemperature8   = 1 << 0,
    KTKDeviceDataLoggerFieldsTemperature16  = 1 << 1,
    KTKDeviceDataLoggerFieldsHumidity       = 1 << 2,
    KTKDeviceDataLoggerFieldsLightLevel     = 1 << 3,
    KTKDeviceDataLoggerFieldsAccelerometer  = 1 << 4,
    KTKDeviceDataLoggerFieldsDebugCounter   = 1 << 5,
    KTKDeviceDataLoggerFieldsTimestamp      = 1 << 6,
    KTKDeviceDataLoggerFieldsBattery        = 1 << 7,
};

/**
 *  A kontakt GPIO state options.
 */
typedef NS_ENUM(int8_t, KTKGPIOState) {
    KTKGPIOStateOff = -1,
    KTKGPIOStateLow,
    KTKGPIOStateHigh,
    KTKGPIOStateInput,
};

/**
 *  A kontakt device GPIOs states.
 */
struct KTKNearbyDeviceGPIOStates {
    KTKGPIOState pin[8];
};

/**
 *  A device acceleration structure.
 */
typedef struct {
    int8_t x;
    int8_t y;
    int8_t z;
} KTKDeviceAcceleration;
