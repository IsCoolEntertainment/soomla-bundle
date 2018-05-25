#ifndef SOOMLA_COCOS2DX_IOS_CORE_CORE_BRIDGE_H
#define SOOMLA_COCOS2DX_IOS_CORE_CORE_BRIDGE_H

#import <Foundation/Foundation.h>

@interface CoreBridge : NSObject
+ (id)initShared;
+ (id)sharedCoreBridge;
@end
#endif
