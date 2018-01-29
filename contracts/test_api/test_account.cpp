/**
 *  @file test_account.cpp
 *  @copyright defined in BetterChain/LICENSE.txt
 */

#include <lib/account.hpp>
#include <lib/betterchain.hpp>
#include <lib/system.h>

#include "test_api.hpp"

/// must match #define in betterchain/types/asset.hpp
#define BETTERCHAIN_SYMBOL  (int64_t(4) | (uint64_t('E') << 8) | (uint64_t('O') << 16) | (uint64_t('S') << 24))

unsigned int test_account::test_balance_acc1()
{
   betterchain::print("test_balance_acc1\n");
   betterchain::account::account_balance b;

   b.account = N(acc1);
   WASM_ASSERT(betterchain::account::get(b), "account_balance_get should have found \"acc1\"");

   WASM_ASSERT(b.account == N(acc1), "account_balance_get should not change the account");
   WASM_ASSERT(b.betterchain_balance.amount == 24, "account_balance_get should have set a balance of 24");
   WASM_ASSERT(b.betterchain_balance.symbol == BETTERCHAIN_SYMBOL, "account_balance_get should have a set a balance symbol of BetterChain");
   WASM_ASSERT(b.staked_balance.amount == 23, "account_balance_get should have set a staked balance of 23");
   WASM_ASSERT(b.staked_balance.symbol == BETTERCHAIN_SYMBOL, "account_balance_get should have a set a staked balance symbol of BetterChain");
   WASM_ASSERT(b.unstaking_balance.amount == 14, "account_balance_get should have set a unstaking balance of 14");
   WASM_ASSERT(b.unstaking_balance.symbol == BETTERCHAIN_SYMBOL, "account_balance_get should have a set a unstaking balance symbol of BetterChain");
   WASM_ASSERT(b.last_unstaking_time == 55, "account_balance_get should have set a last unstaking time of 55");
   return WASM_TEST_PASS;
}
