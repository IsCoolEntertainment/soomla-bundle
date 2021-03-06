//
//  SoomlaEventHandling.h
//  SoomlaiOSProfile
//
//  Created by Gur Dotan on 6/2/14.
//  Copyright (c) 2014 Soomla. All rights reserved.
//
#ifndef SOOMLA_IOS_CORE_SOOMLA_EVENT_HANDLING_H
#define SOOMLA_IOS_CORE_SOOMLA_EVENT_HANDLING_H

@class Reward;

// Events
#define EVENT_ID_REWARD_GIVEN                  @"RewardGiven"
#define EVENT_ID_REWARD_TAKEN                  @"RewardTaken"
#define EVENT_ID_CUSTOM                        @"CustomEvent"

// Dictionary Elements
#define DICT_ELEMENT_ID_REWARD                 @"reward"
#define DICT_ELEMENT_ID_NAME                   @"name"
#define DICT_ELEMENT_ID_EXTRA                  @"extra"


@interface SoomlaEventHandling : NSObject

+ (void)observeAllEventsWithObserver:(id)observer withSelector:(SEL)selector;
+ (void)postRewardGiven:(NSString *)rewardId;
+ (void)postRewardTaken:(NSString *)rewardId;
+ (void)postCustomEventWithName:(NSString*)name andExtraInfo:(NSDictionary*)extra;

@end
#endif
