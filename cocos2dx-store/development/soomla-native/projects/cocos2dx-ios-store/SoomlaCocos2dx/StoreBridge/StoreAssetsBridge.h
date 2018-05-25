//

//
#ifndef SOOMLA_COCOS2DX_IOS_STORE_STORE_ASSETS_BRIDGE_H
#define SOOMLA_COCOS2DX_IOS_STORE_STORE_ASSETS_BRIDGE_H

#import <Foundation/Foundation.h>
#include "IStoreAssets.h"

@interface StoreAssetsBridge : NSObject <IStoreAssets>{
    int version;
    NSMutableArray* virtualCurrenciesArray;
    NSMutableArray* virtualGoodsArray;
    NSMutableArray* virtualCurrencyPacksArray;
    NSMutableArray* virtualCategoriesArray;
}

+ (StoreAssetsBridge *)sharedInstance;
- (void)initializeWithStoreAssetsDict:(NSDictionary*)storeAssetsDict andVersion:(int)oVersion;

@end
#endif
