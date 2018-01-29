/**
 *  @file
 *  @copyright defined in BetterChain/LICENSE.txt
 */
#include <skeleton.hpp>

/**
 *  The init() and apply() methods must have C calling convention so that the blockchain can lookup and
 *  call these methods.
 */
extern "C" {

    /**
     *  This method is called once when the contract is published or updated.
     */
    void init()  {
       betterchain::print( "Init World!\n" );
    }

    /// The apply method implements the dispatch of events to this contract
    void apply( uint64_t code, uint64_t action ) {
       betterchain::print( "Hello World: ", betterchain::name(code), "->", betterchain::name(action), "\n" );
    }

} // extern "C"
