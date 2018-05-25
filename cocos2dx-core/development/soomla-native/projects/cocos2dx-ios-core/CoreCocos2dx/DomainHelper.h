#ifndef SOOMLA_COCOS2DX_IOS_CORE_DOMAIN_HELPER_H
#define SOOMLA_COCOS2DX_IOS_CORE_DOMAIN_HELPER_H

#import <Foundation/Foundation.h>

@interface DomainHelper : NSObject
+ (id)sharedDomainHelper;
- (void) registerType: (NSString *)type withClassName: (NSString *)className;
- (void) registerType: (NSString *)type withClassName: (NSString *)className andBlock: (id (^)(NSDictionary *dict)) creator;
- (id) getDomainsFromDictList: (NSArray *)dictList;
- (id) getDictListFromDomains: (NSArray *)domains;
- (NSDictionary *) domainToDict: (NSObject *)domain;
@end

#endif
