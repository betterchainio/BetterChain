/**
 *  @file
 *  @copyright defined in BetterChain/LICENSE.txt
 */
#pragma once

#include <betterchain/chain/contracts/genesis_state.hpp>
#include <betterchain/chain/contracts/types.hpp>
#include <betterchain/chain/chain_controller.hpp>

namespace betterchain { namespace chain {  namespace contracts {

   class chain_initializer 
   {

      public:
         chain_initializer(const genesis_state_type& genesis) : genesis(genesis) {}

         time_point              get_chain_start_time();
         chain::chain_config     get_chain_start_configuration();
         producer_schedule_type  get_chain_start_producers();

         void register_types(chain::chain_controller& chain, chainbase::database& db);


         std::vector<action> prepare_database(chain::chain_controller& chain, chainbase::database& db);

         static abi_def betterchain_contract_abi();

      private:
         genesis_state_type genesis;
   };

} } } // namespace betterchain::chain::contracts

