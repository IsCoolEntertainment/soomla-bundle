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

#include "CCSoomla.h"
#include "CCCoreBridge.h"
#include "CCSoomlaUtils.h"
#include "CCNdkBridge.h"

namespace soomla {
    
    
    #define TAG "SOOMLA Soomla"
    
    void CCSoomla::initialize(const char *soomlaSecret) {
        cocos2d::__String *soomlaSecretStr = cocos2d::__String::create(soomlaSecret);
        if (soomlaSecretStr == NULL || soomlaSecretStr->length()==0) {
            CCSoomlaUtils::logError(TAG, "Can't initialize SOOMLA without soomlaSecret");
            CCAssert(true, "");
            
            return;
        }
        
        CCCoreBridge::initShared();
        
        cocos2d::__Dictionary *params = cocos2d::__Dictionary::create();
        params->setObject(cocos2d::__String::create("CCSoomla::initialize"), "method");
        params->setObject(soomlaSecretStr, "soomlaSecret");
        CCNdkBridge::callNative(params, NULL);
    }
}

#undef TAG
