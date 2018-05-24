/*
 Copyright (C) 2012-2014 Soomla Inc.
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

#include "CCNativeSoomlaStore.h"
#include "CCNdkBridge.h"

namespace soomla {
    

    void CCNativeSoomlaStore::buyMarketItem(const char *productId, const char *payload, CCError **error) {
        cocos2d::__Dictionary *params = cocos2d::__Dictionary::create();
        params->setObject(cocos2d::__String::create("CCSoomlaStore::buyMarketItem"), "method");
        params->setObject(cocos2d::__String::create(productId), "productId");
        if (payload == NULL) {
            payload = "";
        }
        params->setObject(cocos2d::__String::create(payload), "payload");
        CCNdkBridge::callNative (params, error);
    }

    void CCNativeSoomlaStore::restoreTransactions() {
        cocos2d::__Dictionary *params = cocos2d::__Dictionary::create();
        params->setObject(cocos2d::__String::create("CCSoomlaStore::restoreTransactions"), "method");
        CCNdkBridge::callNative (params, NULL);
    }

    void CCNativeSoomlaStore::refreshInventory() {
        cocos2d::__Dictionary *params = cocos2d::__Dictionary::create();
        params->setObject(cocos2d::__String::create("CCSoomlaStore::refreshInventory"), "method");
        CCNdkBridge::callNative (params, NULL);
    }
    
    void CCNativeSoomlaStore::refreshMarketItemsDetails(CCError **error) {
        cocos2d::__Dictionary *params = cocos2d::__Dictionary::create();
        params->setObject(cocos2d::__String::create("CCSoomlaStore::refreshMarketItemsDetails"), "method");
        CCNdkBridge::callNative (params, error);
    }

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    bool CCNativeSoomlaStore::transactionsAlreadyRestored() {
        cocos2d::__Dictionary *params = cocos2d::__Dictionary::create();
        params->setObject(cocos2d::__String::create("CCSoomlaStore::transactionsAlreadyRestored"), "method");
        cocos2d::__Dictionary *retParams = (cocos2d::__Dictionary *) CCNdkBridge::callNative (params, NULL);
        cocos2d::__Bool *retValue = (cocos2d::__Bool *) retParams->objectForKey("return");
        return retValue->getValue();
    }
    #endif

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    void CCNativeSoomlaStore::startIabServiceInBg() {
        cocos2d::__Dictionary *params = cocos2d::__Dictionary::create();
        params->setObject(cocos2d::__String::create("CCSoomlaStore::startIabServiceInBg"), "method");
        CCNdkBridge::callNative (params, NULL);
    }

    void CCNativeSoomlaStore::stopIabServiceInBg() {
        cocos2d::__Dictionary *params = cocos2d::__Dictionary::create();
        params->setObject(cocos2d::__String::create("CCSoomlaStore::stopIabServiceInBg"), "method");
        CCNdkBridge::callNative (params, NULL);
    }
    #endif
    
    void CCNativeSoomlaStore::loadBillingService() {
        cocos2d::__Dictionary *params = cocos2d::__Dictionary::create();
        params->setObject(cocos2d::__String::create("CCSoomlaStore::loadBillingService"), "method");
        CCNdkBridge::callNative (params, NULL);
    }
}
