/**
 *  @file
 *  @copyright defined in BetterChain/LICENSE.txt
 */
#pragma once
#include <betterchain/chain/types.hpp>
#include <betterchain/chain/authority.hpp>
#include <betterchain/chain/block_timestamp.hpp>
#include <betterchain/chain/contracts/types.hpp>

#include "multi_index_includes.hpp"

namespace betterchain { namespace chain {

   class account_object : public chainbase::object<account_object_type, account_object> {
      OBJECT_CTOR(account_object,(code)(abi))

      id_type              id;
      account_name         name;
      uint8_t              vm_type      = 0;
      uint8_t              vm_version   = 0;
      digest_type          code_version;
      block_timestamp_type creation_date;

      shared_vector<char>  code;
      shared_vector<char>  abi;

      void set_abi( const betterchain::chain::contracts::abi_def& a ) {
         // Added resize(0) here to avoid bug in boost vector container
         abi.resize( 0 );
         abi.resize( fc::raw::pack_size( a ) );
         fc::datastream<char*> ds( abi.data(), abi.size() );
         fc::raw::pack( ds, a );
      }
   };
   using account_id_type = account_object::id_type;

   struct by_name;
   using account_index = chainbase::shared_multi_index_container<
      account_object,
      indexed_by<
         ordered_unique<tag<by_id>, member<account_object, account_object::id_type, &account_object::id>>,
         ordered_unique<tag<by_name>, member<account_object, account_name, &account_object::name>>
      >
   >;

} } // betterchain::chain

CHAINBASE_SET_INDEX_TYPE(betterchain::chain::account_object, betterchain::chain::account_index)


FC_REFLECT(betterchain::chain::account_object, (name)(vm_type)(vm_version)(code_version)(code)(creation_date))
