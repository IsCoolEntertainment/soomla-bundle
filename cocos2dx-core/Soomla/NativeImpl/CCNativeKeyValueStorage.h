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

#ifndef __CCNativeKeyValueStorage_H__
#define __CCNativeKeyValueStorage_H__

#include "data/CCKeyValueStorage.h"

namespace soomla {
    
    /**
     The native implementation of CCKeyValueStorage, uses the bridge to talk
     to native implementations of KeyValueStorage.
     
     See parent for all functions.
     */
    class CCNativeKeyValueStorage : public CCKeyValueStorage {
    public:
        
        virtual const char *getValue(const char *key) const;
        
        virtual void setValue(const char *key, const char *val);

        virtual cocos2d::__Array *getEncryptedKeys() override;

        virtual void deleteKeyValue(const char *key);
        
        virtual void purge();
    };
}

#endif // __CCNativeKeyValueStorage_H__
