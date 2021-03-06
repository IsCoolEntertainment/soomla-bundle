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

#include "domain/virtualGoods/CCSingleUsePackVG.h"
#include "CCSoomlaUtils.h"
#include "data/CCVirtualGoodsStorage.h"
#include "data/CCStoreInfo.h"
#include "domain/virtualGoods/CCSingleUseVG.h"

namespace soomla {
    
    #define TAG "SOOMLA SingleUsePackVG"
    
    CCSingleUsePackVG *CCSingleUsePackVG::create(cocos2d::__String *goodItemId, cocos2d::__Integer *goodAmount, cocos2d::__String *name, cocos2d::__String *description, cocos2d::__String *itemId, CCPurchaseType *purchaseType) {
        CCSingleUsePackVG *ret = new CCSingleUsePackVG();
        if (ret->init(goodItemId, goodAmount, name, description, itemId, purchaseType)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }
        return ret;
    }

    bool CCSingleUsePackVG::init(cocos2d::__String *goodItemId, cocos2d::__Integer *goodAmount, cocos2d::__String *name, cocos2d::__String *description, cocos2d::__String *itemId, CCPurchaseType *purchaseType) {
        bool res = CCVirtualGood::init(name, description, itemId, purchaseType);
        if (res) {
            setGoodItemId(goodItemId);
            setGoodAmount(goodAmount);
            return true;
        } else {
            return false;
        }
    }

    bool CCSingleUsePackVG::initWithDictionary(cocos2d::__Dictionary *dict) {
        bool res = CCVirtualGood::initWithDictionary(dict);
        if (res) {
            fillGoodItemIdFromDict(dict);
            fillGoodAmountFromDict(dict);
            return true;
        } else {
            return false;
        }
    }

    cocos2d::__Dictionary *CCSingleUsePackVG::toDictionary() {
        cocos2d::__Dictionary *dict = CCVirtualGood::toDictionary();

        putGoodItemIdToDict(dict);
        putGoodAmountToDict(dict);

        return dict;
    }


    const char *CCSingleUsePackVG::getType() const {
        return CCStoreConsts::JSON_JSON_TYPE_SINGLE_USE_PACK_VG;
    }

    CCSingleUsePackVG::~CCSingleUsePackVG() {
        CC_SAFE_RELEASE(mGoodItemId);
        CC_SAFE_RELEASE(mGoodAmount);
    }
    
    int CCSingleUsePackVG::give(int amount, bool notify, CCError **error) {
        const char *goodItemId = getGoodItemId()->getCString();
        CCSingleUseVG *good = dynamic_cast<CCSingleUseVG *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(goodItemId, error));
        
        if (good == NULL) {
            CCSoomlaUtils::logError(TAG, cocos2d::__String::createWithFormat("SingleUseVG with itemId: %s doesn't exist! Can't give this pack.",
                                                                   goodItemId)->getCString());
            return 0;
        }
        
        return CCVirtualGoodsStorage::getInstance()->add(good, getGoodAmount()->getValue() * amount, notify, error);
    }
    
    int CCSingleUsePackVG::take(int amount, bool notify, CCError **error) {
        const char *goodItemId = getGoodItemId()->getCString();
        CCSingleUseVG *good = dynamic_cast<CCSingleUseVG *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(goodItemId, error));
        
        if (good == NULL) {
            CCSoomlaUtils::logError(TAG, cocos2d::__String::createWithFormat("SingleUseVG with itemId: %s doesn't exist! Can't take this pack.",
                                                                    goodItemId)->getCString());
            return 0;
        }
        
        return CCVirtualGoodsStorage::getInstance()->remove(good, getGoodAmount()->getValue() * amount, notify, error);
    }
    
    int CCSingleUsePackVG::resetBalance(int balance, bool notify, CCError **error) {
        // Not supported for SingleUsePackVGs !
        CCSoomlaUtils::logError(TAG, "Someone tried to reset balance of GoodPack. That's not right.");
        return 0;
    }
    
    int CCSingleUsePackVG::getBalance(CCError **error) {
        // Not supported for SingleUsePackVGs !
        CCSoomlaUtils::logError(TAG, "Someone tried to check balance of GoodPack. That's not right.");
        return 0;
    }
}
#undef TAG
