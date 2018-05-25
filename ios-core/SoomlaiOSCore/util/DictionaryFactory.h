//
//  DictionaryFactory.h
//  SoomlaiOSLevelUp
//
//  Created by Gur Dotan on 6/15/14.
//  Copyright (c) 2014 Soomla. All rights reserved.
//
#ifndef SOOMLA_IOS_CORE_DICTIONARY_FACTORY_H
#define SOOMLA_IOS_CORE_DICTIONARY_FACTORY_H

@interface DictionaryFactory : NSObject

- (id)createObjectWithDictionary:(NSDictionary *)dict;

@end

#endif
