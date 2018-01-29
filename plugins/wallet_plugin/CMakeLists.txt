file(GLOB HEADERS "include/betterchain/wallet_plugin/*.hpp")
add_library( wallet_plugin
             wallet.cpp
             wallet_plugin.cpp
             wallet_manager.cpp
             ${HEADERS} )

target_link_libraries( wallet_plugin betterchain_chain appbase )
target_include_directories( wallet_plugin PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   wallet_plugin

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
install( FILES ${HEADERS} DESTINATION "include/betterchain/wallet_plugin" )
