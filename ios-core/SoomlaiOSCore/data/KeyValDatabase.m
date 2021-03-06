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

#include "data/KeyValDatabase.h"


@implementation KeyValDatabase


+ (NSString*) keyGoodBalance:(NSString*)itemId {
    return [NSString stringWithFormat:@"good.%@.balance", itemId];
}

+ (NSString*) keyGoodEquipped:(NSString*)itemId {
    return [NSString stringWithFormat:@"good.%@.equipped", itemId];
}

+ (NSString*) keyGoodUpgrade:(NSString*)itemId {
    return [NSString stringWithFormat:@"good.%@.currentUpgrade", itemId];
}

+ (NSString*) keyCurrencyBalance:(NSString*)itemId {
    return [NSString stringWithFormat:@"currency.%@.balance", itemId];
}

+ (NSString*) keyMetaStoreInfo {
    return @"meta.storeinfo";
}


@end
