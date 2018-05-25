//
//  DictionaryFactory.m
//  SoomlaiOSLevelUp
//
//  Created by Gur Dotan on 6/15/14.
//  Copyright (c) 2014 Soomla. All rights reserved.
//

#include "util/DictionaryFactory.h"
#include "data/JSONConsts.h"
#include "SoomlaUtils.h"

@implementation DictionaryFactory

static NSString* TAG = @"SOOMLA DictionaryFactory";

- (id)createObjectWithDictionary:(NSDictionary *)dict {
    
    if (!dict) {
        // warn
        return nil;
    }
    
    id obj = nil;
    NSString* className = dict[SOOM_CLASSNAME];
    
    Class clazz = NSClassFromString(className);
    
    if (clazz) {
        obj = [[clazz alloc] initWithDictionary:dict];
    } else {
        LogError(TAG, ([NSString stringWithFormat:@"Unknown class name: %@", className]));
    }
    
    return obj;
}

@end
