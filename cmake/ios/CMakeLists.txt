set( ios_core_source_root "${source_root}/ios-core/SoomlaiOSCore" )
set( ios_core_sources
  ${ios_core_source_root}/data/JSONConsts.m
  ${ios_core_source_root}/data/KeyValDatabase.m
  ${ios_core_source_root}/data/KeyValueStorage.m
  ${ios_core_source_root}/data/RewardStorage.m
  ${ios_core_source_root}/rewards/BadgeReward.m
  ${ios_core_source_root}/rewards/RandomReward.m
  ${ios_core_source_root}/rewards/Reward.m
  ${ios_core_source_root}/rewards/SequenceReward.m
  ${ios_core_source_root}/Schedule.m
  ${ios_core_source_root}/Soomla.m
  ${ios_core_source_root}/SoomlaConfig.m
  ${ios_core_source_root}/SoomlaEntity.m
  ${ios_core_source_root}/SoomlaEventHandling.m
  ${ios_core_source_root}/SoomlaUtils.m
  ${ios_core_source_root}/util/DictionaryFactory.m
  )

set( ios_store_source_root "${source_root}/ios-store/SoomlaiOSStore" )
set( ios_store_sources
  ${ios_store_source_root}/data/StorageManager.m
  ${ios_store_source_root}/data/StoreInfo.m
  ${ios_store_source_root}/data/StoreJSONConsts.m
  ${ios_store_source_root}/data/VirtualCurrencyStorage.m
  ${ios_store_source_root}/data/VirtualGoodStorage.m
  ${ios_store_source_root}/data/VirtualItemStorage.m
  ${ios_store_source_root}/domain/MarketItem.m
  ${ios_store_source_root}/domain/PurchasableVirtualItem.m
  ${ios_store_source_root}/domain/VirtualCategory.m
  ${ios_store_source_root}/domain/virtualCurrencies/VirtualCurrency.m
  ${ios_store_source_root}/domain/virtualCurrencies/VirtualCurrencyPack.m
  ${ios_store_source_root}/domain/virtualGoods/EquippableVG.m
  ${ios_store_source_root}/domain/virtualGoods/LifetimeVG.m
  ${ios_store_source_root}/domain/virtualGoods/SingleUsePackVG.m
  ${ios_store_source_root}/domain/virtualGoods/SingleUseVG.m
  ${ios_store_source_root}/domain/virtualGoods/UpgradeVG.m
  ${ios_store_source_root}/domain/virtualGoods/VirtualGood.m
  ${ios_store_source_root}/domain/VirtualItem.m
  ${ios_store_source_root}/exceptions/InsufficientFundsException.m
  ${ios_store_source_root}/exceptions/NotEnoughGoodsException.m
  ${ios_store_source_root}/exceptions/VirtualItemNotFoundException.m
  ${ios_store_source_root}/PurchaseTypes/PurchaseType.m
  ${ios_store_source_root}/PurchaseTypes/PurchaseWithMarket.m
  ${ios_store_source_root}/PurchaseTypes/PurchaseWithVirtualItem.m
  ${ios_store_source_root}/rewards/VirtualItemReward.m
  ${ios_store_source_root}/SoomlaStore.m
  ${ios_store_source_root}/SoomlaVerification.m
  ${ios_store_source_root}/StoreConfig.m
  ${ios_store_source_root}/StoreEventHandling.m
  ${ios_store_source_root}/StoreInventory.m
  )

make_compilation_unit(
  compilation_unit_file
  soomla-ios.m
  ${ios_core_sources}
  ${ios_store_sources}
  )

add_library( soomla_ios ${compilation_unit_file} )

target_include_directories(
  soomla_ios
  PUBLIC
  $<BUILD_INTERFACE:${ios_core_source_root}>
  $<BUILD_INTERFACE:${ios_store_source_root}>
  $<INSTALL_INTERFACE:${header_install_dir}/soomla>
  )

target_include_directories(
  soomla_ios
  PRIVATE
  $<BUILD_INTERFACE:${source_root}/ios-core/libs/keeva/headers/Keeva>
  )

install(
  TARGETS soomla_ios
  DESTINATION ${library_install_dir}
  EXPORT soomla
  )

install(
  DIRECTORY ${ios_core_source_root}/ ${ios_store_source_root}/
  DESTINATION ${header_install_dir}/soomla
  PATTERN *.h
  )

install(
  FILES ${source_root}/ios-core/libs/keeva/libKeeva.a
  DESTINATION ${library_install_dir}
  )

target_link_libraries(
  soomla_ios
  PUBLIC
  $<INSTALL_INTERFACE:Keeva>
  )
