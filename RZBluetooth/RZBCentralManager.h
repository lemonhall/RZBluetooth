//
//  RZCentralManager.h
//  UMTSDK
//
//  Created by Brian King on 7/22/15.
//  Copyright (c) 2015 Raizlabs. All rights reserved.
//

#import "RZBDefines.h"

@class RZBPeripheral;

NS_ASSUME_NONNULL_BEGIN

/**
 * RZCentralManager encapsulates all delegate interactions, exposing only the high
 * level Bluetooth actions. RZCentralManager will automatically connect, and
 * discover any needed services or characteristics. It will also wait for 
 * Core Bluetooth to become available, and even re-submit any commands if the 
 * CoreBluetooth process crashes.
 */
@interface RZBCentralManager : NSObject

/**
 * Create a new central manager on the main dispatch queue, with a default identifier.
 */
- (instancetype)init;

/**
 * Create a new central manager
 *
 * @param identifier the restore identifier.
 * @param queue the dispatch queue for the central to use. The main queue will be used if queue is nil.
 *              It is important that the dispatch queue be a serial queue
 *
 */
- (instancetype)initWithIdentifier:(NSString *)identifier queue:(dispatch_queue_t __nullable)queue;

/**
 * Create a new central manager
 *
 * @param identifier the restore identifier.
 * @param peripheralClass the subclass of RZBPeripheral to use
 * @param queue the dispatch queue for the central to use. The main queue will be used if queue is nil.
 *              It is important that the dispatch queue be a serial queue
 */
- (instancetype)initWithIdentifier:(NSString *)identifier peripheralClass:(Class)peripheralClass queue:(dispatch_queue_t __nullable)queue;

/**
 * Expose the backing CBCentralManagerState. See RZBluetoothErrorForState to generate an
 * error object representing the non-functioning terminal states.
 */
@property (assign, nonatomic, readonly) CBCentralManagerState state;

/**
 * This block will be triggered whenever the central manager state changes.
 */
@property (nonatomic, copy) RZBStateBlock centralStateHandler;

/**
 * This block will be triggered when restored with an array of CBPeripheral objects
 */
@property (nonatomic, copy) RZBRestorationBlock restorationHandler;

/**
 * Helper to get a peripheral from a peripheralUUID
 */
- (RZBPeripheral *)peripheralForUUID:(NSUUID *)peripheralUUID;

/**
 * Scan for peripherals with the specified UUIDs and options. Trigger the scanBlock
 * for every discovered peripheral. Multiple calls to this method will replace the previous
 * calls. 
 *
 * The onError: block will be triggered if there are any CBCentralManagerState errors and
 * for user interaction timeout errors if configured.
 */
- (void)scanForPeripheralsWithServices:(NSArray<CBUUID *> * __nullable)serviceUUIDs
                               options:(NSDictionary<NSString *, id> * __nullable)options
                onDiscoveredPeripheral:(RZBScanBlock)scanBlock;

/**
 * Stop the peripheral scan.
 */
- (void)stopScan;

/**
 * This is the CoreBluetooth central manager that backs this central manager.
 */
@property (strong, nonatomic, readonly) CBCentralManager *centralManager;

@end

NS_ASSUME_NONNULL_END
