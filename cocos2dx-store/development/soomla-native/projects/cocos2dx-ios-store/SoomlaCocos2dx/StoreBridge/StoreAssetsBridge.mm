//

//


#include "StoreAssetsBridge.h"
#include "SoomlaUtils.h"
#include "domain/virtualCurrencies/VirtualCurrency.h"
#include "domain/virtualCurrencies/VirtualCurrencyPack.h"
#include "domain/virtualGoods/SingleUseVG.h"
#include "domain/virtualGoods/LifetimeVG.h"
#include "domain/virtualGoods/EquippableVG.h"
#include "domain/virtualGoods/UpgradeVG.h"
#include "domain/virtualGoods/SingleUsePackVG.h"
#include "domain/VirtualCategory.h"
#include "data/StoreJSONConsts.h"


@implementation StoreAssetsBridge

static NSString* STORE_ASSETS_BRIDGE_TAG = @"SOOMLA StoreAssets";

+ (StoreAssetsBridge *)sharedInstance {
    static StoreAssetsBridge * instance = nil;
    if (!instance) {
	instance = [[StoreAssetsBridge alloc] init];
    }
    return instance;
}

- (void)initializeWithStoreAssetsDict:(NSDictionary*)storeAssetsDict andVersion:(int)oVersion{
    version = oVersion;
    [self createFromDict:storeAssetsDict];
}

- (BOOL)createFromDict:(NSDictionary*)storeAssetsDict {
    LogDebug(STORE_ASSETS_BRIDGE_TAG, ([NSString stringWithFormat:@"the storeAssets dit is %@", storeAssetsDict]));

    @try {
        NSDictionary* storeInfo = storeAssetsDict;

        NSMutableArray* currencies = [[NSMutableArray alloc] init];
        NSArray* currenciesDicts = [storeInfo objectForKey:JSON_STORE_CURRENCIES];
        for(NSDictionary* currencyDict in currenciesDicts){
            VirtualCurrency* o = [[VirtualCurrency alloc] initWithDictionary: currencyDict];
            [currencies addObject:o];
        }
        virtualCurrenciesArray = currencies;

        NSMutableArray* currencyPacks = [[NSMutableArray alloc] init];
        NSArray* currencyPacksDicts = [storeInfo objectForKey:JSON_STORE_CURRENCYPACKS];
        for(NSDictionary* currencyPackDict in currencyPacksDicts){
            VirtualCurrencyPack* o = [[VirtualCurrencyPack alloc] initWithDictionary: currencyPackDict];
            [currencyPacks addObject:o];
        }
        virtualCurrencyPacksArray = currencyPacks;


        NSDictionary* goodsDict = [storeInfo objectForKey:JSON_STORE_GOODS];
        NSArray* suGoods = [goodsDict objectForKey:JSON_STORE_GOODS_SU];
        NSArray* ltGoods = [goodsDict objectForKey:JSON_STORE_GOODS_LT];
        NSArray* eqGoods = [goodsDict objectForKey:JSON_STORE_GOODS_EQ];
        NSArray* upGoods = [goodsDict objectForKey:JSON_STORE_GOODS_UP];
        NSArray* paGoods = [goodsDict objectForKey:JSON_STORE_GOODS_PA];
        NSMutableArray* goods = [[NSMutableArray alloc] init];
        for(NSDictionary* gDict in suGoods){
            SingleUseVG* g = [[SingleUseVG alloc] initWithDictionary: gDict];
            [goods addObject:g];
        }
        for(NSDictionary* gDict in ltGoods){
            LifetimeVG* g = [[LifetimeVG alloc] initWithDictionary: gDict];
            [goods addObject:g];
        }
        for(NSDictionary* gDict in eqGoods){
            EquippableVG* g = [[EquippableVG alloc] initWithDictionary: gDict];
            [goods addObject:g];
        }
        for(NSDictionary* gDict in upGoods){
            UpgradeVG* g = [[UpgradeVG alloc] initWithDictionary: gDict];
            [goods addObject:g];
        }
        for(NSDictionary* gDict in paGoods){
            SingleUsePackVG* g = [[SingleUsePackVG alloc] initWithDictionary: gDict];
            [goods addObject:g];
        }
        virtualGoodsArray = goods;

        NSMutableArray* categories = [[NSMutableArray alloc] init];
        NSArray* categoriesDicts = [storeInfo objectForKey:JSON_STORE_CATEGORIES];
        for(NSDictionary* categoryDict in categoriesDicts){
            VirtualCategory* c = [[VirtualCategory alloc] initWithDictionary: categoryDict];
            [categories addObject:c];
        }
        virtualCategoriesArray = categories;

        return YES;
    } @catch (NSException* ex) {
        LogError(STORE_ASSETS_BRIDGE_TAG, @"An error occured while trying to parse store assets JSON.");
    }

    return NO;
}

- (int)getVersion{
    return version;
}

- (NSArray*)virtualCurrencies{
    return virtualCurrenciesArray;
}

- (NSArray*)virtualGoods{
    return virtualGoodsArray;
}

- (NSArray*)virtualCurrencyPacks{
    return virtualCurrencyPacksArray;
}

- (NSArray*)virtualCategories{
    return virtualCategoriesArray;
}


@end
