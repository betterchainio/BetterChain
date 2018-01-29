file(GLOB HEADERS "include/betterchain/tester/*.hpp")

## SORT .cpp by most likely to change / break compile
add_library( betterchain_testing
             tester.cpp
             ${HEADERS}
        )

target_link_libraries( betterchain_testing betterchain_chain betterchain_utilities fc chainbase Logging IR WAST WASM Runtime )
target_include_directories( betterchain_testing
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_BINARY_DIR}/include"
                                   "${CMAKE_CURRENT_SOURCE_DIR}/../wasm-jit/Include"
                            )

if(MSVC)
  set_source_files_properties( db_init.cpp db_block.cpp database.cpp block_log.cpp PROPERTIES COMPILE_FLAGS "/bigobj" )
endif(MSVC)

INSTALL( TARGETS
   betterchain_testing

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
INSTALL( FILES ${HEADERS} DESTINATION "include/betterchain/chain" )
