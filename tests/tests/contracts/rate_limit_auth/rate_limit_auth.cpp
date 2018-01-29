/**
 *  @file
 *  @copyright defined in BetterChain/LICENSE.txt
 */
#include <lib/message.h>
#include <lib/types.hpp>
#include <currency/currency.hpp>

extern "C" {
    void init()
    {
    }

    void test_auths(const currency::transfer& auth)
    {
       require_auth( auth.from );
       require_auth( auth.to );
    }

    /// The apply method implements the dispatch of events to this contract
    void apply( uint64_t code, uint64_t action )
    {
       if( code == N(test1) || code == N(test5) )
       {
          if( action == N(transfer) )
          {
             test_auths( betterchain::current_message< currency::transfer >() );
          }
       }
    }
}
