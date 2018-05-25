//
//  SoomlaEventHandling.m
//  SoomlaiOSProfile
//
//  Created by Gur Dotan on 6/2/14.
//  Copyright (c) 2014 Soomla. All rights reserved.
//

#include "SoomlaEventHandling.h"
#include "rewards/BadgeReward.h"

@implementation SoomlaEventHandling

+ (void)observeAllEventsWithObserver:(id)observer withSelector:(SEL)selector {
    [[NSNotificationCenter defaultCenter] addObserver:observer selector:selector name:EVENT_ID_REWARD_GIVEN object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:observer selector:selector name:EVENT_ID_REWARD_TAKEN object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:observer selector:selector name:EVENT_ID_CUSTOM object:nil];
}

+ (void)postRewardGiven:(NSString *)rewardId {
    NSDictionary *userInfo = @{
                               DICT_ELEMENT_ID_REWARD: rewardId
                               };
    [[NSNotificationCenter defaultCenter] postNotificationName:EVENT_ID_REWARD_GIVEN object:self userInfo:userInfo];
}

+ (void)postRewardTaken:(NSString *)rewardId {
    NSDictionary *userInfo = @{
                               DICT_ELEMENT_ID_REWARD: rewardId
                               };
    [[NSNotificationCenter defaultCenter] postNotificationName:EVENT_ID_REWARD_TAKEN object:self userInfo:userInfo];
}

+ (void)postCustomEventWithName:(NSString*)name andExtraInfo:(NSDictionary*)extra {
    NSDictionary* userInfo = @{
                               DICT_ELEMENT_ID_NAME: name,
                               DICT_ELEMENT_ID_EXTRA: extra
                               };
    [[NSNotificationCenter defaultCenter] postNotificationName:EVENT_ID_CUSTOM object:self userInfo:userInfo];
}

@end
