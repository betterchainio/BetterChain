/**
 *  @file
 *  @copyright defined in BetterChain/LICENSE.txt
 */
#pragma once

#include <fc/exception/exception.hpp>
#include <betterchain/chain/exceptions.hpp>

#define BETTERCHAIN_DECLARE_INTERNAL_EXCEPTION( exc_name, seqnum, msg )  \
   FC_DECLARE_DERIVED_EXCEPTION(                                      \
      internal_ ## exc_name,                                          \
      betterchain::chain::internal_exception,                            \
      3990000 + seqnum,                                               \
      msg                                                             \
      )

namespace betterchain { namespace chain {

FC_DECLARE_DERIVED_EXCEPTION( internal_exception, betterchain::chain::chain_exception, 3990000, "internal exception" )

BETTERCHAIN_DECLARE_INTERNAL_EXCEPTION( verify_auth_max_auth_exceeded, 1, "Exceeds max authority fan-out" )
BETTERCHAIN_DECLARE_INTERNAL_EXCEPTION( verify_auth_account_not_found, 2, "Auth account not found" )

} } // betterchain::chain
