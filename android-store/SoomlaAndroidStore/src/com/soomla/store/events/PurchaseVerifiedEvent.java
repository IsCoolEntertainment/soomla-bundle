package com.soomla.store.events;

import com.soomla.events.SoomlaEvent;
import com.soomla.store.billing.IabPurchase;

public class PurchaseVerifiedEvent extends SoomlaEvent {

    public PurchaseVerifiedEvent(IabPurchase purchase) {
        super(null);
        Purchase = purchase;
    }

    public IabPurchase Purchase;
}
