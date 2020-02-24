set( cocos2dx_core_source_root "${source_root}/cocos2dx-core/Soomla" )
set( cocos2dx_core_sources
  ${cocos2dx_core_source_root}/CCCoreBridge.cpp
  ${cocos2dx_core_source_root}/CCCoreConsts.cpp
  ${cocos2dx_core_source_root}/CCCoreEventDispatcher.cpp
  ${cocos2dx_core_source_root}/CCDomainFactory.cpp
  ${cocos2dx_core_source_root}/CCDomainHelper.cpp
  ${cocos2dx_core_source_root}/CCError.cpp
  ${cocos2dx_core_source_root}/CCJsonHelper.cpp
  ${cocos2dx_core_source_root}/CCNdkBridge.cpp
  ${cocos2dx_core_source_root}/CCSchedule.cpp
  ${cocos2dx_core_source_root}/CCSoomla.cpp
  ${cocos2dx_core_source_root}/CCSoomlaConfigBuilder.cpp
  ${cocos2dx_core_source_root}/CCSoomlaEventDispatcher.cpp
  ${cocos2dx_core_source_root}/CCSoomlaUtils.cpp
  ${cocos2dx_core_source_root}/data/CCBridgelessKeyValueStorage.cpp
  ${cocos2dx_core_source_root}/data/CCKeyValueStorage.cpp
  ${cocos2dx_core_source_root}/data/CCRewardStorage.cpp
  ${cocos2dx_core_source_root}/domain/CCDomain.cpp
  ${cocos2dx_core_source_root}/domain/CCSoomlaEntity.cpp
  ${cocos2dx_core_source_root}/jsb/jsb_soomla.cpp
  ${cocos2dx_core_source_root}/jsb/JSBinding.cpp
  ${cocos2dx_core_source_root}/NativeImpl/CCNativeCoreBridge.cpp
  ${cocos2dx_core_source_root}/NativeImpl/CCNativeKeyValueStorage.cpp
  ${cocos2dx_core_source_root}/NativeImpl/CCNativeRewardStorage.cpp
  ${cocos2dx_core_source_root}/rewards/CCAggregateReward.cpp
  ${cocos2dx_core_source_root}/rewards/CCBadgeReward.cpp
  ${cocos2dx_core_source_root}/rewards/CCRandomReward.cpp
  ${cocos2dx_core_source_root}/rewards/CCReward.cpp
  ${cocos2dx_core_source_root}/rewards/CCSequenceReward.cpp
  )

if( TARGET_IOS )
  set(
    cocos2dx_core_native_source_root
    "${source_root}/cocos2dx-core/development/soomla-native/projects/cocos2dx-ios-core/CoreCocos2dx" )
  set( cocos2dx_core_native_sources
    ${cocos2dx_core_native_source_root}/CCCoreBridgeBinderIos.mm
    ${cocos2dx_core_native_source_root}/CCNdkBridgeIos.mm
    ${cocos2dx_core_native_source_root}/CommonConsts.mm
    ${cocos2dx_core_native_source_root}/CoreBridge.mm
    ${cocos2dx_core_native_source_root}/DomainFactory.mm
    ${cocos2dx_core_native_source_root}/DomainHelper.mm
    ${cocos2dx_core_native_source_root}/NdkGlue.mm
    )

  set(
    cocos2dx_store_native_source_root
    "${source_root}/cocos2dx-store/development/soomla-native/projects/cocos2dx-ios-store/SoomlaCocos2dx/StoreBridge" )
  set( cocos2dx_store_native_sources
    ${cocos2dx_store_native_source_root}/CCStoreBridgeBinderIos.mm
    ${cocos2dx_store_native_source_root}/StoreAssetsBridge.mm
    ${cocos2dx_store_native_source_root}/StoreBridge.mm
    ${cocos2dx_store_native_source_root}/StoreTypeConsts.mm
    )

  set( compilation_unit_extension mm )
else()
  set( compilation_unit_extension cpp )
endif()

set( cocos2dx_store_source_root "${source_root}/cocos2dx-store/Soomla" )
set( cocos2dx_store_sources
  ${cocos2dx_store_source_root}/CCSoomlaStore.cpp
  ${cocos2dx_store_source_root}/CCStoreBridge.cpp
  ${cocos2dx_store_source_root}/CCStoreConsts.cpp
  ${cocos2dx_store_source_root}/CCStoreEventDispatcher.cpp
  ${cocos2dx_store_source_root}/CCStoreInventory.cpp
  ${cocos2dx_store_source_root}/config/CCSoomlaStoreConfigBuilder.cpp
  ${cocos2dx_store_source_root}/config/CCSoomlaStoreGpConfigBuilder.cpp
  ${cocos2dx_store_source_root}/config/CCSoomlaStoreIosConfigBuilder.cpp
  ${cocos2dx_store_source_root}/data/CCStoreInfo.cpp
  ${cocos2dx_store_source_root}/data/CCVirtualCurrencyStorage.cpp
  ${cocos2dx_store_source_root}/data/CCVirtualGoodsStorage.cpp
  ${cocos2dx_store_source_root}/data/CCVirtualItemStorage.cpp
  ${cocos2dx_store_source_root}/domain/CCMarketItem.cpp
  ${cocos2dx_store_source_root}/domain/CCPurchasableVirtualItem.cpp
  ${cocos2dx_store_source_root}/domain/CCVirtualCategory.cpp
  ${cocos2dx_store_source_root}/domain/CCVirtualItem.cpp
  ${cocos2dx_store_source_root}/domain/virtualCurrencies/CCVirtualCurrency.cpp
  ${cocos2dx_store_source_root}/domain/virtualCurrencies/CCVirtualCurrencyPack.cpp
  ${cocos2dx_store_source_root}/domain/virtualGoods/CCEquippableVG.cpp
  ${cocos2dx_store_source_root}/domain/virtualGoods/CCLifetimeVG.cpp
  ${cocos2dx_store_source_root}/domain/virtualGoods/CCSingleUsePackVG.cpp
  ${cocos2dx_store_source_root}/domain/virtualGoods/CCSingleUseVG.cpp
  ${cocos2dx_store_source_root}/domain/virtualGoods/CCUpgradeVG.cpp
  ${cocos2dx_store_source_root}/domain/virtualGoods/CCVirtualGood.cpp
  ${cocos2dx_store_source_root}/NativeImpl/CCNativeSoomlaStore.cpp
  ${cocos2dx_store_source_root}/NativeImpl/CCNativeStoreBridge.cpp
  ${cocos2dx_store_source_root}/NativeImpl/CCNativeStoreInfo.cpp
  ${cocos2dx_store_source_root}/NativeImpl/CCNativeVirtualCurrencyStorage.cpp
  ${cocos2dx_store_source_root}/NativeImpl/CCNativeVirtualGoodsStorage.cpp
  ${cocos2dx_store_source_root}/PurchaseTypes/CCPurchaseType.cpp
  ${cocos2dx_store_source_root}/PurchaseTypes/CCPurchaseWithMarket.cpp
  ${cocos2dx_store_source_root}/PurchaseTypes/CCPurchaseWithVirtualItem.cpp
  ${cocos2dx_store_source_root}/rewards/CCVirtualItemReward.cpp
  )

make_compilation_unit(
  compilation_unit_file
  soomla-cocos2dx.${compilation_unit_extension}
  ${cocos2dx_core_sources}
  ${cocos2dx_core_native_sources}
  ${cocos2dx_store_sources}
  ${cocos2dx_store_native_sources}
  )

add_library( soomla_cocos2dx ${compilation_unit_file} )

target_include_directories(
  soomla_cocos2dx
  PUBLIC
  $<BUILD_INTERFACE:${cocos2dx_core_source_root}>
  $<BUILD_INTERFACE:${cocos2dx_core_native_source_root}>
  $<BUILD_INTERFACE:${cocos2dx_store_source_root}>
  $<BUILD_INTERFACE:${cocos2dx_store_native_source_root}>
  $<INSTALL_INTERFACE:${header_install_dir}/soomla>
  )

if( ${CMAKE_BUILD_TYPE} STREQUAL "release" )
  set( soomla_debug SOOMLA_DEBUG=false )
else()
  set( soomla_debug SOOMLA_DEBUG=true )
endif()

target_compile_definitions(
  soomla_cocos2dx
  PUBLIC
  ${soomla_debug}
  )

target_link_libraries( soomla_cocos2dx cocos2dx::cocos2dx )

if( TARGET_IOS )
  target_link_libraries( soomla_cocos2dx soomla_ios )
endif()

target_link_libraries( soomla_cocos2dx jansson )

install(
  TARGETS soomla_cocos2dx
  DESTINATION ${library_install_dir}
  EXPORT soomla
  )

install(
  DIRECTORY ${cocos2dx_core_source_root}/ ${cocos2dx_store_source_root}/
  DESTINATION ${header_install_dir}/soomla
  PATTERN *.h
  )
