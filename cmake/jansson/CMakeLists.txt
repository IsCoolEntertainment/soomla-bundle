set( jansson_source_root "${source_root}/jansson" )
set( jansson_sources
  ${jansson_source_root}/dump.c
  ${jansson_source_root}/error.c
  ${jansson_source_root}/hashtable.c
  ${jansson_source_root}/load.c
  ${jansson_source_root}/memory.c
  ${jansson_source_root}/pack_unpack.c
  ${jansson_source_root}/strbuffer.c
  ${jansson_source_root}/strconv.c
  ${jansson_source_root}/utf.c
  ${jansson_source_root}/value.c
  )

make_compilation_unit(
  compilation_unit_file
  jansson-unit.c
  ${jansson_sources}
  )

add_library( jansson ${compilation_unit_file} )
target_include_directories(
  jansson
  PUBLIC
  $<BUILD_INTERFACE:${jansson_source_root}>
  )

install(
  TARGETS jansson
  DESTINATION ${library_install_dir}
  EXPORT soomla
  )
