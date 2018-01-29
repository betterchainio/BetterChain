/**
 *  @file
 *  @copyright defined in BetterChain/LICENSE.txt
 */
#pragma once

#include <betterchain/chain/apply_context.hpp>

#include <betterchain/chain/types.hpp>

namespace betterchain { namespace chain { namespace contracts { 

   /**
    * @defgroup native_action_handlers Native Action Handlers
    */
   ///@{
   void apply_betterchain_newaccount(apply_context& context);

   void apply_betterchain_updateauth(apply_context&);
   void apply_betterchain_deleteauth(apply_context&);
   void apply_betterchain_linkauth(apply_context&);
   void apply_betterchain_unlinkauth(apply_context&);

   void apply_betterchain_postrecovery(apply_context&);
   void apply_betterchain_passrecovery(apply_context&);
   void apply_betterchain_vetorecovery(apply_context&);

   void apply_betterchain_transfer(apply_context& context);
   void apply_betterchain_lock(apply_context& context);
   void apply_betterchain_claim(apply_context&);
   void apply_betterchain_unlock(apply_context&);

   void apply_betterchain_okproducer(apply_context&);
   void apply_betterchain_setproducer(apply_context&);
   void apply_betterchain_setproxy(apply_context&);

   void apply_betterchain_setcode(apply_context&);
   void apply_betterchain_setabi(apply_context&);

   void apply_betterchain_nonce(apply_context&);
   void apply_betterchain_onerror(apply_context&);
   ///@}  end action handlers


   share_type get_betterchain_balance( const chainbase::database& db, const account_name& account );

} } } /// namespace betterchain::contracts
