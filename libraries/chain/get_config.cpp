/**
 *  @file
 *  @copyright defined in BetterChain/LICENSE.txt
 */

#include <betterchain/chain/get_config.hpp>
#include <betterchain/chain/config.hpp>
#include <betterchain/chain/types.hpp>

namespace betterchain { namespace chain {

fc::variant_object get_config()
{
   fc::mutable_variant_object result;

   result["block_interval_ms"] = config::block_interval_ms;
   result["producer_count"] = config::producer_count;
   /// TODO: add extra config parms
   return result;
}

} } // betterchain::chain
