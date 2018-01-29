/**
 *  @file
 *  @copyright defined in BetterChain/LICENSE.txt
 */

#include <lib/betterchain.hpp>
#include <lib/token.hpp>
#include <lib/db.hpp>
#include <lib/generic_currency.hpp>


namespace currency {
   typedef betterchain::generic_currency< betterchain::token<N(currency),S(4,CUR)> > contract;
}
