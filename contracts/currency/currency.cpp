/**
 *  @file
 *  @copyright defined in BetterChain/LICENSE.txt
 */

#include <currency/currency.hpp> /// defines transfer struct (abi)

extern "C" {
    /// The apply method implements the dispatch of events to this contract
    void apply( uint64_t code, uint64_t action ) {
       currency::contract::apply( code, action );
    }
}
