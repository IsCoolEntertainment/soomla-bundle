

#include "CCStoreEventDispatcher.h"
#include "CCSoomlaEventDispatcher.h"
#include "CCError.h"
#include "CCStoreInfo.h"
#include "CCSoomlaUtils.h"
#include "CCPurchaseWithMarket.h"
#include "CCNdkBridge.h"
#include "CCStoreInventory.h"

namespace soomla {


    static CCStoreEventDispatcher *s_SharedInstance = NULL;

    CCStoreEventDispatcher *CCStoreEventDispatcher::getInstance() {
        if (!s_SharedInstance) {
            s_SharedInstance = new CCStoreEventDispatcher();
            s_SharedInstance->init();
        }

        return s_SharedInstance;
    }

    bool CCStoreEventDispatcher::init() {

        CCSoomlaEventDispatcher *eventDispatcher = CCSoomlaEventDispatcher::getInstance();

        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_BILLING_NOT_SUPPORTED,
                [this](cocos2d::__Dictionary *parameters) {
                    this->onBillingNotSupported();
                });

        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_BILLING_SUPPORTED,
                [this](cocos2d::__Dictionary *parameters) {
                    this->onBillingSupported();
                });

        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_CURRENCY_BALANCE_CHANGED,
                [this](cocos2d::__Dictionary *parameters) {
                    cocos2d::__String *itemId = (cocos2d::__String *)(parameters->objectForKey("itemId"));
                    cocos2d::__Integer *balance = (cocos2d::__Integer *)(parameters->objectForKey("balance"));
                    cocos2d::__Integer *amountAdded = (cocos2d::__Integer *)(parameters->objectForKey("amountAdded"));
                    CCError *error = NULL;
                    CCVirtualCurrency *virtualCurrency =
                            dynamic_cast<CCVirtualCurrency *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &error));
                    if (error) {
                        CCSoomlaUtils::logException(CCStoreConsts::EVENT_CURRENCY_BALANCE_CHANGED, error);
                        return;
                    }
                    CC_ASSERT(virtualCurrency);
                    this->onCurrencyBalanceChanged(virtualCurrency, balance->getValue(), amountAdded->getValue());
                });

        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_GOOD_BALANCE_CHANGED,
                [this](cocos2d::__Dictionary *parameters) {
                    cocos2d::__String *itemId = (cocos2d::__String *)(parameters->objectForKey("itemId"));
                    cocos2d::__Integer *balance = (cocos2d::__Integer *)(parameters->objectForKey("balance"));
                    cocos2d::__Integer *amountAdded = (cocos2d::__Integer *)(parameters->objectForKey("amountAdded"));
                    CCError *error = NULL;
                    CCVirtualGood *virtualGood =
                            dynamic_cast<CCVirtualGood *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &error));
                    if (error) {
                        CCSoomlaUtils::logException(CCStoreConsts::EVENT_GOOD_BALANCE_CHANGED, error);
                        return;
                    }
                    CC_ASSERT(virtualGood);
                    this->onGoodBalanceChanged(virtualGood, balance->getValue(), amountAdded->getValue());
                });

        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_GOOD_EQUIPPED,
                [this](cocos2d::__Dictionary *parameters) {
                    cocos2d::__String *itemId = (cocos2d::__String *)(parameters->objectForKey("itemId"));
                    CCError *error = NULL;
                    CCEquippableVG *equippableVG =
                            dynamic_cast<CCEquippableVG *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &error));
                    if (error) {
                        CCSoomlaUtils::logException(CCStoreConsts::EVENT_GOOD_EQUIPPED, error);
                        return;
                    }
                    CC_ASSERT(equippableVG);
                    this->onGoodEquipped(equippableVG);
                });

        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_GOOD_UNEQUIPPED,
                [this](cocos2d::__Dictionary *parameters) {
                    cocos2d::__String *itemId = (cocos2d::__String *)(parameters->objectForKey("itemId"));
                    CCError *error = NULL;
                    CCEquippableVG *equippableVG =
                            dynamic_cast<CCEquippableVG *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &error));
                    if (error) {
                        CCSoomlaUtils::logException(CCStoreConsts::EVENT_GOOD_UNEQUIPPED, error);
                        return;
                    }
                    CC_ASSERT(equippableVG);
                    this->onGoodUnEquipped(equippableVG);
                });

        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_GOOD_UPGRADE,
                [this](cocos2d::__Dictionary *parameters) {
                    cocos2d::__String *itemId = (cocos2d::__String *)(parameters->objectForKey("itemId"));
                    cocos2d::__String *vguItemId = (cocos2d::__String *)(parameters->objectForKey("vguItemId"));

                    CCError *error;

                    error = NULL;
                    CCVirtualGood *virtualGood =
                            dynamic_cast<CCVirtualGood *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &error));
                    if (error) {
                        CCSoomlaUtils::logException(CCStoreConsts::EVENT_GOOD_UPGRADE, error);
                        return;
                    }
                    CC_ASSERT(virtualGood);

                    error = NULL;
                    CCUpgradeVG *upgradeVG = NULL;
                    if (vguItemId) {
                        upgradeVG = dynamic_cast<CCUpgradeVG *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(vguItemId->getCString(), &error));
                        if (error) {
                            CCSoomlaUtils::logException(CCStoreConsts::EVENT_GOOD_UPGRADE, error);
                            return;
                        }
                        CC_ASSERT(upgradeVG);
                    }
                    this->onGoodUpgrade(virtualGood, upgradeVG);
                });

        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_ITEM_PURCHASED,
                [this](cocos2d::__Dictionary *parameters) {
                    cocos2d::__String *itemId = (cocos2d::__String *)(parameters->objectForKey("itemId"));
                    cocos2d::__String *payload = (cocos2d::__String *)(parameters->objectForKey("payload"));
                    CCError *error = NULL;
                    CCPurchasableVirtualItem *purchasableVirtualItem =
                            dynamic_cast<CCPurchasableVirtualItem *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &error));
                    if (error) {
                        CCSoomlaUtils::logException(CCStoreConsts::EVENT_ITEM_PURCHASED, error);
                        return;
                    }
                    CC_ASSERT(purchasableVirtualItem);
                    this->onItemPurchased(purchasableVirtualItem, payload);
                });

        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_ITEM_PURCHASE_STARTED,
                [this](cocos2d::__Dictionary *parameters) {
                    cocos2d::__String *itemId = (cocos2d::__String *)(parameters->objectForKey("itemId"));
                    CCError *error = NULL;
                    CCPurchasableVirtualItem *purchasableVirtualItem = dynamic_cast<CCPurchasableVirtualItem *>(
                            CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &error));
                    if (error) {
                        CCSoomlaUtils::logException(CCStoreConsts::EVENT_ITEM_PURCHASE_STARTED, error);
                        return;
                    }
                    CC_ASSERT(purchasableVirtualItem);
                    this->onItemPurchaseStarted(purchasableVirtualItem);
                });

        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_MARKET_PURCHASE_CANCELED,
                [this](cocos2d::__Dictionary *parameters) {
                    cocos2d::__String *itemId = (cocos2d::__String *)(parameters->objectForKey("itemId"));
                    CCError *error = NULL;
                    CCPurchasableVirtualItem *purchasableVirtualItem =
                            dynamic_cast<CCPurchasableVirtualItem *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &error));
                    if (error) {
                        CCSoomlaUtils::logException(CCStoreConsts::EVENT_MARKET_PURCHASE_CANCELED, error);
                        return;
                    }
                    CC_ASSERT(purchasableVirtualItem);
                    this->onMarketPurchaseCancelled(purchasableVirtualItem);
                });

        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_MARKET_PURCHASE_DEFERRED,
                [this](cocos2d::__Dictionary *parameters) {
                    cocos2d::__String *itemId = (cocos2d::__String *)(parameters->objectForKey("itemId"));
                    cocos2d::__String *payload = (cocos2d::__String *)(parameters->objectForKey("payload"));
                    CCError *error = NULL;
                    CCPurchasableVirtualItem *purchasableVirtualItem =
                            dynamic_cast<CCPurchasableVirtualItem *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &error));
                    if (error) {
                        CCSoomlaUtils::logException(CCStoreConsts::EVENT_MARKET_PURCHASE_DEFERRED, error);
                        return;
                    }
                    CC_ASSERT(purchasableVirtualItem);
                    this->onMarketPurchaseDeferred(purchasableVirtualItem, payload);
                });

        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_MARKET_PURCHASE,
                [this](cocos2d::__Dictionary *parameters) {
                    cocos2d::__String *itemId = (cocos2d::__String *)(parameters->objectForKey("itemId"));
                    CCError *error = NULL;
                    CCPurchasableVirtualItem *purchasableVirtualItem =
                            dynamic_cast<CCPurchasableVirtualItem *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &error));
                    if (error) {
                        CCSoomlaUtils::logException(CCStoreConsts::EVENT_MARKET_PURCHASE, error);
                        return;
                    }
                    CC_ASSERT(purchasableVirtualItem);
                    cocos2d::__Bool *restored = (cocos2d::__Bool *)(parameters->objectForKey("isRestored"));
                    cocos2d::__String *payload = (cocos2d::__String *)(parameters->objectForKey("payload"));
                    cocos2d::__Dictionary *extraInfo = (cocos2d::__Dictionary *)(parameters->objectForKey("extraInfo"));
                    this->onMarketPurchase(purchasableVirtualItem, restored, payload, extraInfo);
                });

        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_MARKET_PURCHASE_STARTED,
                [this](cocos2d::__Dictionary *parameters) {
                    cocos2d::__String *itemId = (cocos2d::__String *)(parameters->objectForKey("itemId"));
                    CCError *error = NULL;
                    CCPurchasableVirtualItem *purchasableVirtualItem = dynamic_cast<CCPurchasableVirtualItem *>(
                            CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &error));
                    if (error) {
                        CCSoomlaUtils::logException(CCStoreConsts::EVENT_MARKET_PURCHASE_STARTED, error);
                        return;
                    }
                    CC_ASSERT(purchasableVirtualItem);
                    this->onMarketPurchaseStarted(purchasableVirtualItem);
                });

        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_MARKET_PURCHASE_STARTED,
                [this](cocos2d::__Dictionary *parameters) {
                    cocos2d::__String *itemId = (cocos2d::__String *)(parameters->objectForKey("itemId"));
                    CCError *error = NULL;
                    CCPurchasableVirtualItem *purchasableVirtualItem =
                            dynamic_cast<CCPurchasableVirtualItem *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &error));
                    if (error) {
                        CCSoomlaUtils::logException(CCStoreConsts::EVENT_MARKET_PURCHASE_STARTED, error);
                        return;
                    }
                    CC_ASSERT(purchasableVirtualItem);
                    this->onMarketPurchaseStarted(purchasableVirtualItem);
                });

        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_MARKET_ITEMS_REFRESHED,
                [this](cocos2d::__Dictionary *parameters) {
                    cocos2d::__Array *marketItemDicts = (cocos2d::__Array *)(parameters->objectForKey("marketItems"));
                    cocos2d::__Array *marketItems = cocos2d::__Array::create();
                    cocos2d::__Array *virtualItems = cocos2d::__Array::create();

                    CCError *error = NULL;
                    cocos2d::__Dictionary *marketItem = NULL;
                    for (unsigned int i = 0; i < (unsigned int)marketItemDicts->count(); i++) {
                        marketItem = dynamic_cast<cocos2d::__Dictionary *>(marketItemDicts->getObjectAtIndex(i));
                        CC_ASSERT(marketItem);
                        cocos2d::__String *productId = dynamic_cast<cocos2d::__String *>(marketItem->objectForKey("productId"));
                        cocos2d::__String *marketPrice = dynamic_cast<cocos2d::__String *>(marketItem->objectForKey("marketPrice"));
                        cocos2d::__String *marketTitle = dynamic_cast<cocos2d::__String *>(marketItem->objectForKey("marketTitle"));
                        cocos2d::__String *marketDescription = dynamic_cast<cocos2d::__String *>(marketItem->objectForKey("marketDesc"));
                        cocos2d::__String *marketCurrencyCode = dynamic_cast<cocos2d::__String *>(marketItem->objectForKey("marketCurrencyCode"));
                        cocos2d::__Integer *marketPriceMicros = dynamic_cast<cocos2d::__Integer *>(marketItem->objectForKey("marketPriceMicros"));

                        CCPurchasableVirtualItem *pvi = CCStoreInfo::sharedStoreInfo()->getPurchasableItemWithProductId(
                                productId->getCString(), &error);
                        if (error) {
                            CCSoomlaUtils::logException(CCStoreConsts::EVENT_MARKET_ITEMS_REFRESHED, error);
                            return;
                        }
                        CC_ASSERT(pvi);

                        CCPurchaseWithMarket *purchaseWithMarket = dynamic_cast<CCPurchaseWithMarket *>(pvi->getPurchaseType());
                        CC_ASSERT(purchaseWithMarket);
                        CCMarketItem *mi = purchaseWithMarket->getMarketItem();
                        mi->setMarketPriceAndCurrency(marketPrice);
                        mi->setMarketTitle(marketTitle);
                        mi->setMarketDescription(marketDescription);
                        mi->setMarketCurrencyCode(marketCurrencyCode);
                        mi->setMarketPriceMicros(marketPriceMicros);

                        marketItems->addObject(mi);
                        virtualItems->addObject(pvi);
                    }
                    
                    if (virtualItems->count() > 0) {
                        // no need to save to DB since it's already saved in native
                        // before this event is received
                        CCStoreInfo::sharedStoreInfo()->saveItems(virtualItems, false);
                    }

                    this->onMarketItemsRefreshed(marketItems);
                });

        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_MARKET_ITEMS_REFRESH_STARTED,
                [this](cocos2d::__Dictionary *parameters) {
                    this->onMarketItemsRefreshStarted();
                });
        
        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_MARKET_ITEMS_REFRESH_FAILED,
                [this](cocos2d::__Dictionary *parameters) {
                    cocos2d::__String *errorMessage = (cocos2d::__String *)(parameters->objectForKey("errorMessage"));
                    this->onMarketItemsRefreshFailed(errorMessage);
                });
        
        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_VERIFICATION_STARTED,
                [this](cocos2d::__Dictionary *parameters) {
                    cocos2d::__String *itemId = (cocos2d::__String *)(parameters->objectForKey("itemId"));
                    CCError *error = NULL;
                    CCPurchasableVirtualItem *purchasableVirtualItem =
                            dynamic_cast<CCPurchasableVirtualItem *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &error));
                    if (error) {
                        CCSoomlaUtils::logException(CCStoreConsts::EVENT_VERIFICATION_STARTED, error);
                        return;
                    }
                    CC_ASSERT(purchasableVirtualItem);
                    this->onVerificationStarted(purchasableVirtualItem);
                });

        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_MARKET_PURCHASE_VERIFICATION,
                [this](cocos2d::__Dictionary *parameters) {
                    cocos2d::__String *itemId = (cocos2d::__String *)(parameters->objectForKey("itemId"));
                    CCError *error = NULL;
                    CCPurchasableVirtualItem *purchasableVirtualItem =
                            dynamic_cast<CCPurchasableVirtualItem *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &error));
                    if (error) {
                        CCSoomlaUtils::logException(CCStoreConsts::EVENT_MARKET_PURCHASE_VERIFICATION, error);
                        return;
                    }
                    CC_ASSERT(purchasableVirtualItem);
                    this->onMarketPurchaseVerification(purchasableVirtualItem);
               });

        eventDispatcher->registerEventHandler
            ( CCStoreConsts::EVENT_PURCHASE_VERIFICATION_STARTED,
              [this](cocos2d::__Dictionary *parameters) {

                cocos2d::__String *itemType =
                    (cocos2d::__String *)(parameters->objectForKey("itemType"));
                CC_ASSERT(itemType);
                
                cocos2d::__String *signature =
                    (cocos2d::__String *)(parameters->objectForKey("signature"));
                CC_ASSERT(signature);

                cocos2d::__String *originalJson =
                    (cocos2d::__String *)(parameters->objectForKey("originalJson"));
                CC_ASSERT(originalJson);
                
                this->onPurchaseVerificationStarted
                    ( itemType, signature, originalJson );
            });

        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_RESTORE_TRANSACTION_FINISHED,
                [this](cocos2d::__Dictionary *parameters) {
                    cocos2d::__Bool *success = (cocos2d::__Bool *)(parameters->objectForKey("success"));
                    this->onRestoreTransactionsFinished(success->getValue());
               });

        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_RESTORE_TRANSACTION_STARTED,
                [this](cocos2d::__Dictionary *parameters) {
                    this->onRestoreTransactionsStarted();
               });

        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_UNEXPECTED_STORE_ERROR,
                [this](cocos2d::__Dictionary *parameters) {
                    cocos2d::__Integer *errorCode = (cocos2d::__Integer *)(parameters->objectForKey("errorCode"));
                    this->onUnexpectedStoreError(errorCode);
               });

        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_SOOMLA_STORE_INITIALIZED,
                [this](cocos2d::__Dictionary *parameters) {
                    this->onSoomlaStoreInitialized();
               });

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_MARKET_REFUND,
                [this](cocos2d::__Dictionary *parameters) {
                    cocos2d::__String *itemId = (cocos2d::__String *)(parameters->objectForKey("itemId"));
                    CCError *error = NULL;
                    CCPurchasableVirtualItem *purchasableVirtualItem =
                            dynamic_cast<CCPurchasableVirtualItem *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &error));
                    if (error) {
                        CCSoomlaUtils::logException(CCStoreConsts::EVENT_MARKET_REFUND, error);
                        return;
                    }
                    CC_ASSERT(purchasableVirtualItem);
                    this->onMarketRefund(purchasableVirtualItem);
               });

        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_IAB_SERVICE_STARTED,
                [this](cocos2d::__Dictionary *parameters) {
                    this->onIabServiceStarted();
               });

        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_IAB_SERVICE_STOPPED,
                [this](cocos2d::__Dictionary *parameters) {
                    this->onIabServiceStopped();
               });
#endif
        return true;
    }

    void CCStoreEventDispatcher::onBillingNotSupported() {
        cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCStoreConsts::EVENT_BILLING_NOT_SUPPORTED);
    }

    void CCStoreEventDispatcher::onBillingSupported() {
        cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCStoreConsts::EVENT_BILLING_SUPPORTED);
    }

    void CCStoreEventDispatcher::onCurrencyBalanceChanged(CCVirtualCurrency *virtualCurrency, int balance, int amountAdded) {
        CCStoreInventory::sharedStoreInventory()->refreshOnCurrencyBalanceChanged(virtualCurrency, balance, amountAdded);
        
        cocos2d::__Dictionary *eventDict = cocos2d::__Dictionary::create();
        eventDict->setObject(virtualCurrency, CCStoreConsts::DICT_ELEMENT_CURRENCY);
        eventDict->setObject(cocos2d::__Integer::create(balance), CCStoreConsts::DICT_ELEMENT_BALANCE);
        eventDict->setObject(cocos2d::__Integer::create(amountAdded), CCStoreConsts::DICT_ELEMENT_AMOUNT_ADDED);
        
        cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCStoreConsts::EVENT_CURRENCY_BALANCE_CHANGED, eventDict);
    }

    void CCStoreEventDispatcher::onGoodBalanceChanged(CCVirtualGood *virtualGood, int balance, int amountAdded) {
        CCStoreInventory::sharedStoreInventory()->refreshOnGoodBalanceChanged(virtualGood, balance, amountAdded);
        
        cocos2d::__Dictionary *eventDict = cocos2d::__Dictionary::create();
        eventDict->setObject(virtualGood, CCStoreConsts::DICT_ELEMENT_GOOD);
        eventDict->setObject(cocos2d::__Integer::create(balance), CCStoreConsts::DICT_ELEMENT_BALANCE);
        eventDict->setObject(cocos2d::__Integer::create(amountAdded), CCStoreConsts::DICT_ELEMENT_AMOUNT_ADDED);
        
        cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCStoreConsts::EVENT_GOOD_BALANCE_CHANGED, eventDict);
    }

    void CCStoreEventDispatcher::onGoodEquipped(CCEquippableVG *equippableVG) {
        CCStoreInventory::sharedStoreInventory()->refreshOnGoodEquipped(equippableVG);
        
        cocos2d::__Dictionary *eventDict = cocos2d::__Dictionary::create();
        eventDict->setObject(equippableVG, CCStoreConsts::DICT_ELEMENT_EQUIPPABLEVG);
        
        cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCStoreConsts::EVENT_GOOD_EQUIPPED, eventDict);
    }

    void CCStoreEventDispatcher::onGoodUnEquipped(CCEquippableVG *equippableVG) {
        CCStoreInventory::sharedStoreInventory()->refreshOnGoodUnEquipped(equippableVG);
        
        cocos2d::__Dictionary *eventDict = cocos2d::__Dictionary::create();
        eventDict->setObject(equippableVG, CCStoreConsts::DICT_ELEMENT_EQUIPPABLEVG);
        
        cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCStoreConsts::EVENT_GOOD_UNEQUIPPED, eventDict);
    }

    void CCStoreEventDispatcher::onGoodUpgrade(CCVirtualGood *virtualGood, CCUpgradeVG *upgradeVG) {
        CCStoreInventory::sharedStoreInventory()->refreshOnGoodUpgrade(virtualGood, upgradeVG);
        
        cocos2d::__Dictionary *eventDict = cocos2d::__Dictionary::create();
        eventDict->setObject(virtualGood, CCStoreConsts::DICT_ELEMENT_GOOD);
        if (upgradeVG != NULL) {
            eventDict->setObject(upgradeVG, CCStoreConsts::DICT_ELEMENT_UPGRADEVG);
        }
        
        cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCStoreConsts::EVENT_GOOD_UPGRADE, eventDict);
    }

    void CCStoreEventDispatcher::onItemPurchased(CCPurchasableVirtualItem *purchasableVirtualItem, cocos2d::__String *payload) {
        onItemPurchased(purchasableVirtualItem, payload, false);
    }

    void CCStoreEventDispatcher::onItemPurchased(CCPurchasableVirtualItem *purchasableVirtualItem, cocos2d::__String *payload, bool alsoPush) {
        if (payload == NULL) {
            payload = cocos2d::__String::create("");
        }
        
        cocos2d::__Dictionary *eventDict = cocos2d::__Dictionary::create();
        eventDict->setObject(purchasableVirtualItem, CCStoreConsts::DICT_ELEMENT_PURCHASABLE);
        eventDict->setObject(payload, CCStoreConsts::DICT_ELEMENT_DEVELOPERPAYLOAD);
        
        cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCStoreConsts::EVENT_ITEM_PURCHASED, eventDict);

        if (alsoPush) {
            #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            
            cocos2d::__Dictionary *params = cocos2d::__Dictionary::create();
            params->setObject(cocos2d::__String::create("CCStoreEventDispatcher::pushOnItemPurchased"), "method");
            params->setObject(purchasableVirtualItem->getItemId(), "itemId");
            params->setObject(payload, "payload");
            CCNdkBridge::callNative (params, NULL);
            
            #endif
        }
    }

    void CCStoreEventDispatcher::onItemPurchaseStarted(CCPurchasableVirtualItem *purchasableVirtualItem) {
        onItemPurchaseStarted(purchasableVirtualItem, false);
    }

    void CCStoreEventDispatcher::onItemPurchaseStarted(CCPurchasableVirtualItem *purchasableVirtualItem, bool alsoPush) {
        cocos2d::__Dictionary *eventDict = cocos2d::__Dictionary::create();
        eventDict->setObject(purchasableVirtualItem, CCStoreConsts::DICT_ELEMENT_PURCHASABLE);
        
        cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCStoreConsts::EVENT_ITEM_PURCHASE_STARTED, eventDict);

        if (alsoPush) {
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            
            cocos2d::__Dictionary *params = cocos2d::__Dictionary::create();
            params->setObject(cocos2d::__String::create("CCStoreEventDispatcher::pushOnItemPurchaseStarted"), "method");
            params->setObject(purchasableVirtualItem->getItemId(), "itemId");
            CCNdkBridge::callNative (params, NULL);
            
        #endif
        }
    }

    void CCStoreEventDispatcher::onMarketPurchaseCancelled(CCPurchasableVirtualItem *purchasableVirtualItem) {
        cocos2d::__Dictionary *eventDict = cocos2d::__Dictionary::create();
        eventDict->setObject(purchasableVirtualItem, CCStoreConsts::DICT_ELEMENT_PURCHASABLE);
        
        cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCStoreConsts::EVENT_MARKET_PURCHASE_CANCELED, eventDict);
    }

    void CCStoreEventDispatcher::onMarketPurchaseDeferred(CCPurchasableVirtualItem *purchasableVirtualItem, cocos2d::__String *payload) {
        cocos2d::__Dictionary *eventDict = cocos2d::__Dictionary::create();
        eventDict->setObject(purchasableVirtualItem, CCStoreConsts::DICT_ELEMENT_PURCHASABLE);
        eventDict->setObject(payload, CCStoreConsts::DICT_ELEMENT_DEVELOPERPAYLOAD);

        cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCStoreConsts::EVENT_MARKET_PURCHASE_DEFERRED, eventDict);
    }

    void CCStoreEventDispatcher::onMarketPurchase(CCPurchasableVirtualItem *purchasableVirtualItem, cocos2d::__Bool *restored, cocos2d::__String *payload, cocos2d::__Dictionary *extraInfo) {

        cocos2d::__Dictionary *eventDict = cocos2d::__Dictionary::create();
        eventDict->setObject(purchasableVirtualItem, CCStoreConsts::DICT_ELEMENT_PURCHASABLE);
        eventDict->setObject(restored, CCStoreConsts::DICT_ELEMENT_IS_RESTORED);
        eventDict->setObject(payload, CCStoreConsts::DICT_ELEMENT_DEVELOPERPAYLOAD);
        eventDict->setObject(extraInfo, CCStoreConsts::DICT_ELEMENT_EXTRA_INFO);

        cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCStoreConsts::EVENT_MARKET_PURCHASE, eventDict);
    }

    void CCStoreEventDispatcher::onMarketPurchaseStarted(CCPurchasableVirtualItem *purchasableVirtualItem) {
        cocos2d::__Dictionary *eventDict = cocos2d::__Dictionary::create();
        eventDict->setObject(purchasableVirtualItem, CCStoreConsts::DICT_ELEMENT_PURCHASABLE);
        
        cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCStoreConsts::EVENT_MARKET_PURCHASE_STARTED, eventDict);
    }

    void CCStoreEventDispatcher::onVerificationStarted(CCPurchasableVirtualItem *purchasableVirtualItem) {
        cocos2d::__Dictionary *eventDict = cocos2d::__Dictionary::create();
        eventDict->setObject(purchasableVirtualItem, CCStoreConsts::DICT_ELEMENT_PURCHASABLE);

        cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCStoreConsts::EVENT_VERIFICATION_STARTED, eventDict);
    }

    void CCStoreEventDispatcher::onMarketPurchaseVerification(CCPurchasableVirtualItem *purchasableVirtualItem) {
        cocos2d::__Dictionary *eventDict = cocos2d::__Dictionary::create();
        eventDict->setObject(purchasableVirtualItem, CCStoreConsts::DICT_ELEMENT_PURCHASABLE);
        
        cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCStoreConsts::EVENT_MARKET_PURCHASE_VERIFICATION, eventDict);
    }

    void CCStoreEventDispatcher::onRestoreTransactionsFinished(bool success) {
        cocos2d::__Dictionary *eventDict = cocos2d::__Dictionary::create();
        eventDict->setObject(cocos2d::__Bool::create(success), CCStoreConsts::DICT_ELEMENT_SUCCESS);
        
        cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCStoreConsts::EVENT_RESTORE_TRANSACTION_FINISHED, eventDict);
    }

    void CCStoreEventDispatcher::onRestoreTransactionsStarted() {
        cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCStoreConsts::EVENT_RESTORE_TRANSACTION_STARTED);
    }

    void CCStoreEventDispatcher::onUnexpectedStoreError(cocos2d::__Integer *errorCode) {
        onUnexpectedStoreError(errorCode, false);
    }

    void CCStoreEventDispatcher::onUnexpectedStoreError(cocos2d::__Integer *errorCode, bool alsoPush) {
        cocos2d::__Dictionary *eventDict = cocos2d::__Dictionary::create();
        eventDict->setObject(errorCode, CCStoreConsts::DICT_ELEMENT_ERROR_CODE);
        
        cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCStoreConsts::EVENT_UNEXPECTED_STORE_ERROR, eventDict);

        if (alsoPush) {
            #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
                        
            cocos2d::__Dictionary *params = cocos2d::__Dictionary::create();
            params->setObject(cocos2d::__String::create("CCStoreEventDispatcher::pushOnUnexpectedStoreError"), "method");
            params->setObject(errorCode, "errorCode");
            CCNdkBridge::callNative (params, NULL);
            
            #endif
        }
    }

    void CCStoreEventDispatcher::onSoomlaStoreInitialized() {
        onSoomlaStoreInitialized(false);
    }

    void CCStoreEventDispatcher::onSoomlaStoreInitialized(bool alsoPush) {
        cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCStoreConsts::EVENT_SOOMLA_STORE_INITIALIZED);

        CCStoreInventory::sharedStoreInventory()->refreshLocalInventory();

        if (alsoPush) {
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            
            cocos2d::__Dictionary *params = cocos2d::__Dictionary::create();
            params->setObject(cocos2d::__String::create("CCStoreEventDispatcher::pushOnSoomlaStoreInitialized"), "method");
            CCNdkBridge::callNative (params, NULL);
            
        #endif
        }
    }

    void CCStoreEventDispatcher::onMarketItemsRefreshed(cocos2d::__Array *marketItems) {
        cocos2d::__Dictionary *eventDict = cocos2d::__Dictionary::create();
        eventDict->setObject(marketItems, CCStoreConsts::DICT_ELEMENT_MARKET_ITEMS);
        
        cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCStoreConsts::EVENT_MARKET_ITEMS_REFRESHED, eventDict);
    }

    void CCStoreEventDispatcher::onMarketItemsRefreshStarted() {
        cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCStoreConsts::EVENT_MARKET_ITEMS_REFRESH_STARTED);
    }

    void CCStoreEventDispatcher::onMarketItemsRefreshFailed(cocos2d::__String *errorMessage) {
        if (errorMessage == NULL) {
            errorMessage = cocos2d::__String::create("");
        }
        cocos2d::__Dictionary *eventDict = cocos2d::__Dictionary::create();
        eventDict->setObject(errorMessage, CCStoreConsts::DICT_ELEMENT_ERROR_MESSAGE);
        
        cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCStoreConsts::EVENT_MARKET_ITEMS_REFRESH_FAILED, eventDict);
    }

    void CCStoreEventDispatcher::onPurchaseVerificationStarted
    ( cocos2d::__String *itemType, cocos2d::__String *signature,
      cocos2d::__String *originalJson ) {

        cocos2d::__Dictionary *eventDict = cocos2d::__Dictionary::create();
        eventDict->setObject
            ( itemType, CCStoreConsts::DICT_ELEMENT_ITEM_TYPE );
        eventDict->setObject
            ( signature, CCStoreConsts::DICT_ELEMENT_SIGNATURE );
        eventDict->setObject
            ( originalJson, CCStoreConsts::DICT_ELEMENT_ORIGINAL_JSON );
        
        cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent
            ( CCStoreConsts::EVENT_PURCHASE_VERIFICATION_STARTED, eventDict );
    }
    
    void CCStoreEventDispatcher::onPurchaseVerified
    ( cocos2d::__String *itemType, cocos2d::__String *signature,
      cocos2d::__String *originalJson ) {

        cocos2d::__Dictionary *params = cocos2d::__Dictionary::create();
        params->setObject
            ( cocos2d::__String::create
              ("CCStoreEventDispatcher::pushOnPurchaseVerified"),
              "method");
        params->setObject( itemType, "itemType" );
        params->setObject( originalJson, "originalJson" );
        params->setObject( signature, "signature" );
        CCNdkBridge::callNative( params, nullptr );
    }

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    void CCStoreEventDispatcher::onMarketRefund(CCPurchasableVirtualItem *purchasableVirtualItem) {
        cocos2d::__Dictionary *eventDict = cocos2d::__Dictionary::create();
        eventDict->setObject(purchasableVirtualItem, CCStoreConsts::DICT_ELEMENT_PURCHASABLE);
        
        cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCStoreConsts::EVENT_MARKET_REFUND, eventDict);
    }

    void CCStoreEventDispatcher::onIabServiceStarted() {
        cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCStoreConsts::EVENT_IAB_SERVICE_STARTED);
    }

    void CCStoreEventDispatcher::onIabServiceStopped() {
        cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCStoreConsts::EVENT_IAB_SERVICE_STOPPED);
    }
#endif

}
