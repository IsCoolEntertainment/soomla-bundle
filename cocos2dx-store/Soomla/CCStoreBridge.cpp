

#include "CCStoreBridge.h"
#include "CCDomainFactory.h"
#include "CCStoreConsts.h"
#include "domain/CCVirtualItem.h"
#include "domain/CCMarketItem.h"
#include "domain/CCVirtualCategory.h"
#include "domain/virtualCurrencies/CCVirtualCurrency.h"
#include "domain/virtualCurrencies/CCVirtualCurrencyPack.h"
#include "domain/virtualGoods/CCEquippableVG.h"
#include "domain/virtualGoods/CCSingleUsePackVG.h"
#include "domain/virtualGoods/CCUpgradeVG.h"
#include "domain/virtualGoods/CCSingleUseVG.h"
#include "CCDomainHelper.h"
#include "CCStoreEventDispatcher.h"
#include "rewards/CCVirtualItemReward.h"
#include "NativeImpl/CCNativeStoreBridge.h"
#include "CCSoomlaStore.h"

namespace soomla {
    

    #define TAG "SOOMLA CCStoreBridge"

    static CCStoreBridge *sInstance = nullptr;

    CCStoreBridge *CCStoreBridge::getInstance() {
        if (!sInstance)
        {
            #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            sInstance = new CCNativeStoreBridge();
            #else
            sInstance = new CCStoreBridge();
            #endif
            sInstance->retain();
        }
        return sInstance;
    }

    void CCStoreBridge::initShared() {
        CCStoreBridge *storeBridge = CCStoreBridge::getInstance();
        if (!storeBridge->init()) {
            exit(1);
        }
    }

    bool CCStoreBridge::init() {

        CCStoreEventDispatcher::getInstance();    // to get sure it's inited

        CCDomainFactory *domainFactory = CCDomainFactory::getInstance();
        domainFactory->registerCreator(CCStoreConsts::JSON_JSON_TYPE_MARKET_ITEM, CCMarketItem::createWithDictionary);
        domainFactory->registerCreator(CCStoreConsts::JSON_JSON_TYPE_VIRTUAL_CATEGORY, CCVirtualCategory::createWithDictionary);
        domainFactory->registerCreator(CCStoreConsts::JSON_JSON_TYPE_VIRTUAL_CURRENCY, CCVirtualCurrency::createWithDictionary);
        domainFactory->registerCreator(CCStoreConsts::JSON_JSON_TYPE_VIRTUAL_CURRENCY_PACK, CCVirtualCurrencyPack::createWithDictionary);
        domainFactory->registerCreator(CCStoreConsts::JSON_JSON_TYPE_EQUIPPABLE_VG, CCEquippableVG::createWithDictionary);
        domainFactory->registerCreator(CCStoreConsts::JSON_JSON_TYPE_LIFETIME_VG, CCLifetimeVG::createWithDictionary);
        domainFactory->registerCreator(CCStoreConsts::JSON_JSON_TYPE_SINGLE_USE_PACK_VG, CCSingleUsePackVG::createWithDictionary);
        domainFactory->registerCreator(CCStoreConsts::JSON_JSON_TYPE_SINGLE_USE_VG, CCSingleUseVG::createWithDictionary);
        domainFactory->registerCreator(CCStoreConsts::JSON_JSON_TYPE_UPGRADE_VG, CCUpgradeVG::createWithDictionary);

        domainFactory->registerCreator(CCStoreConsts::JSON_JSON_TYPE_ITEM, &CCVirtualItemReward::createWithDictionary);

        return true;
    }
    
    void CCStoreBridge::applyParams(cocos2d::__Dictionary *storeParams) {}
#undef TAG
}
