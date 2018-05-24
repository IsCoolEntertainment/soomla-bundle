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

#include "CCNativeRewardStorage.h"
#include "CCError.h"
#include "CCNdkBridge.h"
#include "CCSoomlaUtils.h"

namespace soomla {
    
    #define TAG "SOOMLA NativeRewardStorage"
    

    void CCNativeRewardStorage::setRewardStatus(CCReward *reward, bool give, bool notify) {
        CCError *error = NULL;
        
        cocos2d::__Dictionary *params = cocos2d::__Dictionary::create();
        params->setObject(cocos2d::__String::create("CCNativeRewardStorage::setRewardStatus"), "method");
        params->setObject(reward->getId(), "reward");
        params->setObject(cocos2d::__Bool::create(give), "give");
        params->setObject(cocos2d::__Bool::create(notify), "notify");
        CCNdkBridge::callNative (params, &error);
        
        if (error) {
            CCSoomlaUtils::logException(TAG, error);
            CC_ASSERT(false);
        }
    }

    int CCNativeRewardStorage::getTimesGiven(CCReward *reward) {
        CCError *error = NULL;
        
        cocos2d::__Dictionary *params = cocos2d::__Dictionary::create();
        params->setObject(cocos2d::__String::create("CCNativeRewardStorage::getTimesGiven"), "method");
        params->setObject(reward->getId(), "reward");
        cocos2d::__Dictionary *retParams = (cocos2d::__Dictionary *) CCNdkBridge::callNative (params, &error);
        
        if (error) {
            CCSoomlaUtils::logException(TAG, error);
            CC_ASSERT(false);
            return -1;
        }
        
        if (retParams == NULL) {
            return -1;
        }
        
        cocos2d::__Integer *retValue = (cocos2d::__Integer *) retParams->objectForKey("return");
        if (!retValue) {
            return -1;
        }
        
        return retValue->getValue();
    }

    int CCNativeRewardStorage::getLastSeqIdxGiven(CCSequenceReward *sequenceReward) {
        CCError *error = NULL;
        
        cocos2d::__Dictionary *params = cocos2d::__Dictionary::create();
        params->setObject(cocos2d::__String::create("CCNativeRewardStorage::getLastSeqIdxGiven"), "method");
        params->setObject(sequenceReward->getId(), "reward");
        cocos2d::__Dictionary *retParams = (cocos2d::__Dictionary *) CCNdkBridge::callNative (params, &error);
        
        if (error) {
            CCSoomlaUtils::logException(TAG, error);
            CC_ASSERT(false);
            return -1;
        }
        
        if (retParams == NULL) {
            return -1;
        }
        
        cocos2d::__Integer *retValue = (cocos2d::__Integer *) retParams->objectForKey("return");
        if (!retValue) {
            return -1;
        }
        
        return retValue->getValue();
    }

    void CCNativeRewardStorage::setLastSeqIdxGiven(CCSequenceReward *sequenceReward, unsigned int idx) {
        CCError *error = NULL;
        
        cocos2d::__Dictionary *params = cocos2d::__Dictionary::create();
        params->setObject(cocos2d::__String::create("CCNativeRewardStorage::setLastSeqIdxGiven"), "method");
        params->setObject(sequenceReward->getId(), "reward");
        params->setObject(cocos2d::__Integer::create(idx), "idx");
        CCNdkBridge::callNative (params, &error);
        
        if (error) {
            CCSoomlaUtils::logException(TAG, error);
            CC_ASSERT(false);
        }
    }
}

#undef TAG
