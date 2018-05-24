package com.soomla.store.events;

import com.soomla.events.SoomlaEvent;
import com.soomla.store.billing.IabPurchase;

public class PurchaseVerificationStartedEvent extends SoomlaEvent {

    public PurchaseVerificationStartedEvent( IabPurchase purchase ) {
        super(null);
        Purchase = purchase;
    }

    public IabPurchase Purchase;
}
