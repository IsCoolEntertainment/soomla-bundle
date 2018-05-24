cmake_minimum_required( VERSION 3.9 )

set( CMAKE_CXX_STANDARD 11 )
set( source_root ${CMAKE_CURRENT_LIST_DIR}/.. )

set( CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules"
  )

include( install )
include( platform )
include( unity-build )

find_package( cocos2dx )

if( TARGET_IOS )
  add_subdirectory( ios )
endif()

add_subdirectory( jansson )
add_subdirectory( cocos )
