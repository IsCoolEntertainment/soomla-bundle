#ifndef SOOMLA_COCOS2DX_IOS_CORE_DOMAIN_FACTORY_H
#define SOOMLA_COCOS2DX_IOS_CORE_DOMAIN_FACTORY_H

#import <Foundation/Foundation.h>


@interface DomainFactory : NSObject
+ (id)sharedDomainFactory;
- (void)registerCreatorForKey: (NSString *)key withBlock: (id (^)(NSDictionary *dict)) creator;
- (id)createWithDict: (NSDictionary *)dict;
@end
#endif
