install(
  EXPORT soomla
  DESTINATION lib/cmake/soomla/
  FILE soomla-config-generated.cmake
  )

install(
  FILES ${CMAKE_CURRENT_LIST_DIR}/soomla-config.cmake
  DESTINATION lib/cmake/soomla/
  )
