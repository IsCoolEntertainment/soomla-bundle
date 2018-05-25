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

#include "base/CCUserDefault.h"

#include "data/CCBridgelessKeyValueStorage.h"

namespace soomla {
    
    
    #define KEY_VALUE_STORAGE_KEY "soomla.kvs.keys"
    
    CCBridgelessKeyValueStorage::CCBridgelessKeyValueStorage() {
        mStoredKeys = cocos2d::__Set::create();
        mStoredKeys->retain();
        
        loadStoredKeys();
    }
    
    const char *CCBridgelessKeyValueStorage::getValue(const char *key) const {
        std::string defaultValue = "";
        std::string result = cocos2d::UserDefault::getInstance()->getStringForKey(key, defaultValue);
        if (result == defaultValue) {
            return NULL;
        }
        
        // Using this for pooling facilities, so c_str won't go away when returned
        cocos2d::__String *returnedValue = cocos2d::__String::create(result);
        return returnedValue->getCString();
    }
    
    void CCBridgelessKeyValueStorage::setValue(const char *key, const char *val) {
        cocos2d::UserDefault::getInstance()->setStringForKey(key, val);
        cocos2d::UserDefault::getInstance()->flush();
        
        addStoredKeys(key);
        saveStoredKeys();
    }

    cocos2d::__Array *CCBridgelessKeyValueStorage::getEncryptedKeys() {
        cocos2d::__Array *result = cocos2d::__Array::create();
        for(cocos2d::__SetIterator i = mStoredKeys->begin(); i != mStoredKeys->end(); i++) {
            if (!(*i)) {
                break;
            }

            cocos2d::__String *key = dynamic_cast<cocos2d::__String *>(*i);
            result->addObject(key);
        }

        return result;
    }

    void CCBridgelessKeyValueStorage::deleteKeyValue(const char *key) {
        cocos2d::UserDefault::getInstance()->setStringForKey(key, "");
        cocos2d::UserDefault::getInstance()->flush();
        
        removeStoredKeys(key);
        saveStoredKeys();
    }
    
    void CCBridgelessKeyValueStorage::purge() {
        for(cocos2d::__SetIterator i = mStoredKeys->begin(); i != mStoredKeys->end(); i++) {
            if (!(*i)) {
                break;
            }
            
            cocos2d::__String *key = dynamic_cast<cocos2d::__String *>(*i);
            deleteKeyValue(key->getCString());
        }
        
        mStoredKeys->removeAllObjects();
        
        cocos2d::UserDefault::getInstance()->setStringForKey(KEY_VALUE_STORAGE_KEY, "");
        cocos2d::UserDefault::getInstance()->flush();
    }
    
    void CCBridgelessKeyValueStorage::addStoredKeys(const char *key) {
        cocos2d::__String *wrapKey = cocos2d::__String::create(key);
        
        if (mStoredKeys->containsObject(wrapKey)) {
            return;
        }
        
        mStoredKeys->addObject(wrapKey);
    }
    
    void CCBridgelessKeyValueStorage::removeStoredKeys(const char *key) {
        cocos2d::__String *wrapKey = cocos2d::__String::create(key);
        
        mStoredKeys->removeObject(wrapKey);
    }
    
    void CCBridgelessKeyValueStorage::saveStoredKeys() {
        std::string joinedKeys = "";
        for(cocos2d::__SetIterator i = mStoredKeys->begin(); i != mStoredKeys->end(); i++) {
            if (!(*i)) {
                break;
            }
            
            cocos2d::__String *key = dynamic_cast<cocos2d::__String *>(*i);
            joinedKeys.append("#").append(key->getCString());
        }
        
        cocos2d::UserDefault::getInstance()->setStringForKey(KEY_VALUE_STORAGE_KEY, joinedKeys);
        cocos2d::UserDefault::getInstance()->flush();
    }
    
    void CCBridgelessKeyValueStorage::loadStoredKeys() {
        std::string joinedKeys = cocos2d::UserDefault::getInstance()->getStringForKey(KEY_VALUE_STORAGE_KEY, "");
        
        std::stringstream ss(joinedKeys);
        std::string item;
        while(std::getline(ss, item, '#')) {
            addStoredKeys(item.c_str());
        }
    }
}

#undef KEY_VALUE_STORAGE_KEY
