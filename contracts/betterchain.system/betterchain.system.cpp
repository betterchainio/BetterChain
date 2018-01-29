/**
 *  @file
 *  @copyright defined in BetterChain/LICENSE.txt
 */

#include <betterchain.system/betterchain.system.hpp> 

using namespace betterchainsystem;

extern "C" {

    /// The apply method implements the dispatch of events to this contract
    void apply( uint64_t code, uint64_t act ) {
       betterchainsystem::contract<N(betterchain.system)>::apply( code, act );
    }
}
