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

#include "rewards/RandomReward.h"
#include "data/JSONConsts.h"
#include "rewards/BadgeReward.h"
#include "SoomlaUtils.h"

@implementation RandomReward

@synthesize rewards;

static NSString* RANDOM_REWARD_RANDOM_REWARD_TAG = @"SOOMLA RandomReward";


- (id)initWithRewardId:(NSString *)oRewardId andName:(NSString *)oName andRewards:(NSArray *)oRewards {
    if (self = [super initWithRewardId:oRewardId andName:oName]) {
        
        if (![oRewards count]) {
            LogError(RANDOM_REWARD_RANDOM_REWARD_TAG, @"this reward doesn't make sense without items");
        }
        
        self.rewards = oRewards;
    }
    
    return self;
}

- (id)initWithDictionary:(NSDictionary *)dict {
    if (self = [super initWithDictionary:dict]) {
        
        NSMutableArray* tmpRewards = [NSMutableArray array];
        NSArray* rewardsArr = dict[SOOM_REWARDS];
        
        if (!rewardsArr) {
            LogDebug(RANDOM_REWARD_RANDOM_REWARD_TAG, @"reward has no meaning without children");
            rewardsArr = [NSMutableArray array];
        }
        
        // Iterate over all rewards in the JSON array and for each one create
        // an instance according to the reward type
        for (NSDictionary* rewardDict in rewardsArr) {
            
            Reward* reward = [Reward fromDictionary:rewardDict];
            if (reward) {
                [tmpRewards addObject:reward];
            }
        }
        
        self.rewards = tmpRewards;
    }
    
    return self;
}

- (NSDictionary *)toDictionary {
    NSDictionary* parentDict = [super toDictionary];
    
    NSMutableArray* rewardsArr = [NSMutableArray array];
    for (Reward* reward in self.rewards) {
        [rewardsArr addObject:[reward toDictionary]];
    }
    
    NSMutableDictionary* toReturn = [[NSMutableDictionary alloc] initWithDictionary:parentDict];
    [toReturn setObject:rewardsArr forKey:SOOM_REWARDS];
    
    return toReturn;
}

- (BOOL)giveInner {
    NSMutableArray* canBeGivenRewards = [NSMutableArray array];
    for (Reward* reward in self.rewards) {
        if ([reward canGive]) {
            [canBeGivenRewards addObject:reward];
        }
    }
    
    if (![canBeGivenRewards count]) {
        LogDebug(RANDOM_REWARD_RANDOM_REWARD_TAG, ([NSString stringWithFormat:@"No more rewards to give in this Random Reward: %@", self.ID]));
        return NO;
    }
    
    int i = arc4random() % [canBeGivenRewards count];
    Reward* randomReward = canBeGivenRewards[i];
    [randomReward give];
    lastGivenReward = randomReward;

    return YES;
}


- (BOOL)takeInner {
    
    // for now is able to take only last given
    if(!lastGivenReward) {
        return NO;
    }
    
    BOOL taken = [lastGivenReward take];
    lastGivenReward = nil;
    
    return taken;
}





@end
