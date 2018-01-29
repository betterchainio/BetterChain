
add_library( betterchain_egenesis_none
   egenesis_none.cpp
   include/betterchain/egenesis/egenesis.hpp
   )

target_link_libraries( betterchain_egenesis_none betterchain_chain fc )
target_include_directories( betterchain_egenesis_none
   PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

add_executable( embed_genesis
   embed_genesis.cpp
   )

target_link_libraries( embed_genesis betterchain_chain betterchain_egenesis_none fc )

set( embed_genesis_args
   -t "${CMAKE_CURRENT_SOURCE_DIR}/egenesis_brief.cpp.tmpl---${CMAKE_CURRENT_BINARY_DIR}/egenesis_brief.cpp"
   -t "${CMAKE_CURRENT_SOURCE_DIR}/egenesis_full.cpp.tmpl---${CMAKE_CURRENT_BINARY_DIR}/egenesis_full.cpp"
   )

MESSAGE( STATUS "egenesis: " ${BETTERCHAIN_EGENESIS_JSON} )

if( BETTERCHAIN_EGENESIS_JSON )
   list( APPEND embed_genesis_args --genesis-json "${BETTERCHAIN_EGENESIS_JSON}" )
endif( BETTERCHAIN_EGENESIS_JSON )

MESSAGE( STATUS "embed_genesis_args: " ${embed_genesis_args} )

add_custom_command(
   OUTPUT
      "${CMAKE_CURRENT_BINARY_DIR}/egenesis_brief.cpp"
      "${CMAKE_CURRENT_BINARY_DIR}/egenesis_full.cpp"
   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
   COMMAND embed_genesis ${embed_genesis_args}
   DEPENDS
      "${BETTERCHAIN_EGENESIS_JSON}"
      "${CMAKE_CURRENT_SOURCE_DIR}/egenesis_brief.cpp.tmpl"
      "${CMAKE_CURRENT_SOURCE_DIR}/egenesis_full.cpp.tmpl"
      embed_genesis )

add_library( betterchain_egenesis_brief "${CMAKE_CURRENT_BINARY_DIR}/egenesis_brief.cpp" include/betterchain/egenesis/egenesis.hpp )
add_library( betterchain_egenesis_full  "${CMAKE_CURRENT_BINARY_DIR}/egenesis_full.cpp" include/betterchain/egenesis/egenesis.hpp )

target_link_libraries( betterchain_egenesis_brief betterchain_chain fc )
target_link_libraries( betterchain_egenesis_full betterchain_chain fc )

target_include_directories( betterchain_egenesis_brief
   PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )
target_include_directories( betterchain_egenesis_full
   PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

INSTALL( TARGETS
   embed_genesis betterchain_egenesis_none betterchain_egenesis_brief betterchain_egenesis_full

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
