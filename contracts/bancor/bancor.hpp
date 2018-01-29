/**
 *  @file
 *  @copyright defined in BetterChain/LICENSE.txt
 */
#pragma once

#include <lib/betterchain.hpp>
#include <lib/token.hpp>
#include <lib/db.hpp>
#include <lib/reflect.hpp>
#include <lib/generic_currency.hpp>

#include <bancor/converter.hpp>
#include <currency/currency.hpp>

namespace bancor {
   typedef betterchain::generic_currency< betterchain::token<N(other),S(4,OTHER)> >  other_currency;
   typedef betterchain::generic_currency< betterchain::token<N(bancor),S(4,RELAY)> > relay_currency;
   typedef betterchain::generic_currency< betterchain::token<N(currency),S(4,CUR)> > cur_currency;

   typedef converter<relay_currency, other_currency, cur_currency > example_converter;
} /// bancor

