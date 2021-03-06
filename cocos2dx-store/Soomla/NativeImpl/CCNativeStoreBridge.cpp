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

#include "NativeImpl/CCNativeStoreBridge.h"
#include "CCNdkBridge.h"
#include "CCSoomlaUtils.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <string>

#define CLASS_NAME "com/soomla/cocos2dx/store/StoreBridgeBinder"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "CCStoreBridgeBinderIos.h"

#endif

namespace soomla {
    
    
    #define TAG "SOOMLA CCNativeStoreBridge"
    
    CCNativeStoreBridge::CCNativeStoreBridge() {
        // Just bind to native before initing
        this->bindNative();
    }
    
    void CCNativeStoreBridge::applyParams(cocos2d::__Dictionary *storeParams) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        cocos2d::__Bool *SSV = dynamic_cast<cocos2d::__Bool *>(storeParams->objectForKey("SSV"));
        if (SSV == NULL) {
            SSV = cocos2d::__Bool::create(false);
        }
        
        {
            cocos2d::__Dictionary *params = cocos2d::__Dictionary::create();
            params->setObject(cocos2d::__String::create("CCSoomlaStore::setSSV"), "method");
            params->setObject(SSV, "ssv");
            if (SSV->getValue()) {
                cocos2d::__Bool *verifyOnServerFailure = dynamic_cast<cocos2d::__Bool *>(storeParams->objectForKey("verifyOnServerFailure"));
                if (verifyOnServerFailure == nullptr) {
                    verifyOnServerFailure = cocos2d::__Bool::create(false);
                }
                params->setObject(verifyOnServerFailure, "verifyOnServerFailure");
            }
            CCNdkBridge::callNative (params, NULL);
        }
#endif

        {

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            {
                cocos2d::__String *androidPublicKey = dynamic_cast<cocos2d::__String *>(storeParams->objectForKey("androidPublicKey"));
                if (androidPublicKey != NULL && androidPublicKey->length()>0) {
                    cocos2d::__Dictionary *params = cocos2d::__Dictionary::create();
                    params->setObject(cocos2d::__String::create("CCSoomlaStore::setAndroidPublicKey"), "method");
                    params->setObject(androidPublicKey, "androidPublicKey");
                    CCNdkBridge::callNative (params, NULL);
                }

            }

            {
                cocos2d::__String *clientId = dynamic_cast<cocos2d::__String *>(storeParams->objectForKey("clientId"));
                cocos2d::__String *clientSecret = dynamic_cast<cocos2d::__String *>(storeParams->objectForKey("clientSecret"));
                cocos2d::__String *refreshToken = dynamic_cast<cocos2d::__String *>(storeParams->objectForKey("refreshToken"));
                cocos2d::__Bool *verifyOnServerFailure = dynamic_cast<cocos2d::__Bool *>(storeParams->objectForKey("verifyOnServerFailure"));

                if (clientId != NULL && clientId->length() > 0 &&
                        clientSecret != NULL && clientSecret->length() > 0 &&
                        refreshToken != NULL && refreshToken->length() > 0) {


                    cocos2d::__Dictionary *params = cocos2d::__Dictionary::create();
                    params->setObject(cocos2d::__String::create("CCSoomlaStore::configVerifyPurchases"), "method");
                    params->setObject(clientId, "clientId");
                    params->setObject(clientSecret, "clientSecret");
                    params->setObject(refreshToken, "refreshToken");
                    if (verifyOnServerFailure != NULL) {
                        params->setObject(verifyOnServerFailure, "verifyOnServerFailure");
                    }
                    CCNdkBridge::callNative(params, NULL);
                }

            }

            {
                cocos2d::__Bool *testPurchases = dynamic_cast<cocos2d::__Bool *>(storeParams->objectForKey("testPurchases"));
                if (testPurchases == NULL) {
                    testPurchases = cocos2d::__Bool::create(false);
                }
                cocos2d::__Dictionary *params = cocos2d::__Dictionary::create();
                params->setObject(cocos2d::__String::create("CCSoomlaStore::setTestPurchases"), "method");
                params->setObject(testPurchases, "testPurchases");
                CCNdkBridge::callNative (params, NULL);
            }
#endif
        }
    }
    
    void CCNativeStoreBridge::bindNative() {
        CCSoomlaUtils::logDebug(TAG, "Binding to native platform Store bridge...");
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        cocos2d::JniMethodInfo minfo;
        
        bool exists = cocos2d::JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "bind", "()V");
        
        if (exists)
        {
            minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
        }
        else {
            CCSoomlaUtils::logError(TAG, "Unable to bind native Store bridge on Android");
        }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        soomla::CCStoreBridgeBinderIos::bind();
#endif
    }
}
#undef CLASS_NAME

#undef TAG
