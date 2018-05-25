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

#include "NativeImpl/CCNativeVirtualCurrencyStorage.h"

#include "NativeImpl/CCNativeVirtualGoodsStorage.h"
#include "CCSoomlaUtils.h"
#include "CCNdkBridge.h"
#include "data/CCStoreInfo.h"
#include "domain/virtualGoods/CCUpgradeVG.h"

namespace soomla {
#define TAG "SOOMLA NativeVirtualCurrencyStorage"
    
    
    CCNativeVirtualCurrencyStorage::CCNativeVirtualCurrencyStorage() {
        
    }
    
    CCNativeVirtualCurrencyStorage::~CCNativeVirtualCurrencyStorage() {
        
    }
    
    int CCNativeVirtualCurrencyStorage::getBalance(CCVirtualItem *item, CCError **error) {
        const char *itemId = item->getId()->getCString();
        
        CCSoomlaUtils::logDebug(TAG,
                                cocos2d::__String::createWithFormat("SOOMLA/COCOS2DX Calling getBalance with: %s", itemId)->getCString());
        cocos2d::__Dictionary *params = cocos2d::__Dictionary::create();
        params->setObject(cocos2d::__String::create("CCNativeVirtualCurrencyStorage::getBalance"), "method");
        params->setObject(cocos2d::__String::create(itemId), "itemId");
        cocos2d::__Dictionary *retParams = (cocos2d::__Dictionary *) CCNdkBridge::callNative (params, error);
        
        if (retParams == NULL) {
            return 0;
        }
        
        cocos2d::__Integer *retValue = (cocos2d::__Integer *) retParams->objectForKey("return");
        if (retValue) {
            return retValue->getValue();
        } else {
            return 0;
        }
    }
    
    int CCNativeVirtualCurrencyStorage::setBalance(CCVirtualItem *item, int balance, bool notify, CCError **error) {
        const char *itemId = item->getId()->getCString();
        
        CCSoomlaUtils::logDebug(TAG,
                                cocos2d::__String::createWithFormat("SOOMLA/COCOS2DX Calling setBalance with: %s", itemId)->getCString());
        cocos2d::__Dictionary *params = cocos2d::__Dictionary::create();
        params->setObject(cocos2d::__String::create("CCNativeVirtualCurrencyStorage::setBalance"), "method");
        params->setObject(cocos2d::__String::create(itemId), "itemId");
        params->setObject(cocos2d::__Integer::create(balance), "balance");
        params->setObject(cocos2d::__Bool::create(notify), "notify");
        cocos2d::__Dictionary *retParams = (cocos2d::__Dictionary *) CCNdkBridge::callNative (params, error);
        
        if (retParams == NULL) {
            return 0;
        }
        
        cocos2d::__Integer *retValue = (cocos2d::__Integer *) retParams->objectForKey("return");
        if (retValue) {
            return retValue->getValue();
        } else {
            return 0;
        }
    }
    
    int CCNativeVirtualCurrencyStorage::add(CCVirtualItem *item, int amount, bool notify, CCError **error) {
        const char *itemId = item->getId()->getCString();
        
        CCSoomlaUtils::logDebug(TAG,
                                cocos2d::__String::createWithFormat("SOOMLA/COCOS2DX Calling add with: %s", itemId)->getCString());
        cocos2d::__Dictionary *params = cocos2d::__Dictionary::create();
        params->setObject(cocos2d::__String::create("CCNativeVirtualCurrencyStorage::add"), "method");
        params->setObject(cocos2d::__String::create(itemId), "itemId");
        params->setObject(cocos2d::__Integer::create(amount), "amount");
        params->setObject(cocos2d::__Bool::create(notify), "notify");
        cocos2d::__Dictionary *retParams = (cocos2d::__Dictionary *) CCNdkBridge::callNative (params, error);
        
        if (retParams == NULL) {
            return 0;
        }
        
        cocos2d::__Integer *retValue = (cocos2d::__Integer *) retParams->objectForKey("return");
        if (retValue) {
            return retValue->getValue();
        } else {
            return 0;
        }
    }
    
    int CCNativeVirtualCurrencyStorage::remove(CCVirtualItem *item, int amount, bool notify, CCError **error) {
        const char *itemId = item->getId()->getCString();
        
        CCSoomlaUtils::logDebug(TAG,
                                cocos2d::__String::createWithFormat("SOOMLA/COCOS2DX Calling remove with: %s", itemId)->getCString());
        cocos2d::__Dictionary *params = cocos2d::__Dictionary::create();
        params->setObject(cocos2d::__String::create("CCNativeVirtualCurrencyStorage::remove"), "method");
        params->setObject(cocos2d::__String::create(itemId), "itemId");
        params->setObject(cocos2d::__Integer::create(amount), "amount");
        params->setObject(cocos2d::__Bool::create(notify), "notify");
        cocos2d::__Dictionary *retParams = (cocos2d::__Dictionary *) CCNdkBridge::callNative (params, error);
        
        if (retParams == NULL) {
            return 0;
        }
        
        cocos2d::__Integer *retValue = (cocos2d::__Integer *) retParams->objectForKey("return");
        if (retValue) {
            return retValue->getValue();
        } else {
            return 0;
        }
    }
}
#undef TAG
