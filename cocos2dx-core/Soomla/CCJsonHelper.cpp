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

#include "CCJsonHelper.h"

cocos2d::Ref *CCJsonHelper::getCCObjectFromJson(json_t *obj) {
    if (obj == NULL) {
        return NULL;
    }

    if (json_is_object(obj)) {
        cocos2d::__Dictionary *dictionary = cocos2d::__Dictionary::create();

        const char *key;
        json_t *value;

        void *iter = json_object_iter(obj);
        while (iter) {
            key = json_object_iter_key(iter);
            value = json_object_iter_value(iter);

            dictionary->setObject(CCJsonHelper::getCCObjectFromJson(value), std::string(key));

            iter = json_object_iter_next(obj, iter);
        }

        return dictionary;
    }
    else if (json_is_array(obj)) {
        size_t sizeArray = json_array_size(obj);
        cocos2d::__Array *array = cocos2d::__Array::createWithCapacity(sizeArray);

        for (unsigned int i = 0; i < sizeArray; i++) {
            array->addObject(CCJsonHelper::getCCObjectFromJson(json_array_get(obj, i)));
        }

        return array;
    }
    else if (json_is_boolean(obj)) {
        cocos2d::__Bool *ccBool = cocos2d::__Bool::create(json_is_true(obj));
        return ccBool;
    }
    else if (json_is_integer(obj)) {
        json_int_t intVal = json_integer_value(obj);

        cocos2d::__Integer *ccInteger = cocos2d::__Integer::create((int) intVal);
        return ccInteger;
    }
    else if (json_is_real(obj)) {
        double realVal = json_real_value(obj);

        cocos2d::__Double *ccDouble = cocos2d::__Double::create(realVal);
        return ccDouble;
    }
    else if (json_is_string(obj)) {
        std::stringstream str;
        str << json_string_value(obj);

        cocos2d::__String *ccString = cocos2d::__String::create(str.str());
        return ccString;
    }
    else if (json_is_null(obj)) {
        return cocos2d::__String::create("");
    }
    else {
        CC_ASSERT(false);
        return NULL;
    }
}

json_t*CCJsonHelper::getJsonFromCCObject(cocos2d::Ref* obj) {
    if (dynamic_cast<cocos2d::__Dictionary *>(obj)) {
        cocos2d::__Dictionary *mainDict = (cocos2d::__Dictionary *) obj;
        cocos2d::__Array *allKeys = mainDict->allKeys();
        json_t *jsonDict = json_object();

        if (allKeys == NULL ) return jsonDict;
        for (unsigned int i = 0; i < allKeys->count(); i++) {
            const char *key = ((cocos2d::__String *) allKeys->getObjectAtIndex(i))->getCString();
            json_object_set_new(jsonDict,
                    key,
                    CCJsonHelper::getJsonFromCCObject(mainDict->objectForKey(key)));
        }

        return jsonDict;
    }
    else if (dynamic_cast<cocos2d::__Array *>(obj)) {
        cocos2d::__Array *mainArray = (cocos2d::__Array *) obj;
        json_t *jsonArray = json_array();

        for (unsigned int i = 0; i < mainArray->count(); i++) {
            json_array_append_new(jsonArray,
                    CCJsonHelper::getJsonFromCCObject(mainArray->getObjectAtIndex(i)));
        }

        return jsonArray;
    }
    else if (dynamic_cast<cocos2d::__String *>(obj)) {
        cocos2d::__String *mainString = (cocos2d::__String *) obj;
        json_t *jsonString = json_string(mainString->getCString());

        return jsonString;
    }
    else if (dynamic_cast<cocos2d::__Integer *>(obj)) {
        cocos2d::__Integer *mainInteger = (cocos2d::__Integer *) obj;
        json_t *jsonInt = json_integer(mainInteger->getValue());

        return jsonInt;
    }
    else if (dynamic_cast<cocos2d::__Double *>(obj)) {
        cocos2d::__Double *mainDouble = (cocos2d::__Double *) obj;
        json_t *jsonReal = json_real(mainDouble->getValue());

        return jsonReal;
    }
    else if (dynamic_cast<cocos2d::__Float *>(obj)) {
        cocos2d::__Float *mainFloat = (cocos2d::__Float *) obj;
        json_t *jsonString = json_real(mainFloat->getValue());

        return jsonString;
    }
    else if (dynamic_cast<cocos2d::__Bool *>(obj)) {
        cocos2d::__Bool *mainBool = (cocos2d::__Bool *) obj;
        json_t *jsonBoolean = json_boolean(mainBool->getValue());

        return jsonBoolean;
    }
    else {
        CC_ASSERT(false);
        return NULL;
    }
}
