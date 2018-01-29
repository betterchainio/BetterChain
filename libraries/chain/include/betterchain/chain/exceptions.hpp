/**
 *  @file
 *  @copyright defined in BetterChain/LICENSE.txt
 */
#pragma once

#include <fc/exception/exception.hpp>
#include <betterchain/chain/protocol.hpp>
#include <betterchain/utilities/exception_macros.hpp>

namespace betterchain { namespace chain {

   FC_DECLARE_EXCEPTION( chain_exception, 3000000, "blockchain exception" )
   FC_DECLARE_DERIVED_EXCEPTION( database_query_exception,          betterchain::chain::chain_exception, 3010000, "database query exception" )
   FC_DECLARE_DERIVED_EXCEPTION( block_validate_exception,          betterchain::chain::chain_exception, 3020000, "block validation exception" )
   FC_DECLARE_DERIVED_EXCEPTION( transaction_exception,             betterchain::chain::chain_exception, 3030000, "transaction validation exception" )
   FC_DECLARE_DERIVED_EXCEPTION( action_validate_exception,         betterchain::chain::chain_exception, 3040000, "message validation exception" )
   FC_DECLARE_DERIVED_EXCEPTION( utility_exception,                 betterchain::chain::chain_exception, 3070000, "utility method exception" )
   FC_DECLARE_DERIVED_EXCEPTION( undo_database_exception,           betterchain::chain::chain_exception, 3080000, "undo database exception" )
   FC_DECLARE_DERIVED_EXCEPTION( unlinkable_block_exception,        betterchain::chain::chain_exception, 3090000, "unlinkable block" )
   FC_DECLARE_DERIVED_EXCEPTION( black_swan_exception,              betterchain::chain::chain_exception, 3100000, "black swan" )
   FC_DECLARE_DERIVED_EXCEPTION( unknown_block_exception,           betterchain::chain::chain_exception, 3110000, "unknown block" )

   FC_DECLARE_DERIVED_EXCEPTION( block_tx_output_exception,         betterchain::chain::block_validate_exception, 3020001, "transaction outputs in block do not match transaction outputs from applying block" )
   FC_DECLARE_DERIVED_EXCEPTION( block_concurrency_exception,       betterchain::chain::block_validate_exception, 3020002, "block does not guarantee concurrent exection without conflicts" )
   FC_DECLARE_DERIVED_EXCEPTION( block_lock_exception,              betterchain::chain::block_validate_exception, 3020003, "shard locks in block are incorrect or mal-formed" )

   FC_DECLARE_DERIVED_EXCEPTION( tx_missing_auth,                   betterchain::chain::transaction_exception, 3030001, "missing required authority" )
   FC_DECLARE_DERIVED_EXCEPTION( tx_missing_sigs,                   betterchain::chain::transaction_exception, 3030002, "signatures do not satisfy declared authorizations" )
   FC_DECLARE_DERIVED_EXCEPTION( tx_irrelevant_auth,                betterchain::chain::transaction_exception, 3030003, "irrelevant authority included" )
   FC_DECLARE_DERIVED_EXCEPTION( tx_irrelevant_sig,                 betterchain::chain::transaction_exception, 3030004, "irrelevant signature included" )
   FC_DECLARE_DERIVED_EXCEPTION( tx_duplicate_sig,                  betterchain::chain::transaction_exception, 3030005, "duplicate signature included" )
   FC_DECLARE_DERIVED_EXCEPTION( invalid_committee_approval,        betterchain::chain::transaction_exception, 3030006, "committee account cannot directly approve transaction" )
   FC_DECLARE_DERIVED_EXCEPTION( insufficient_fee,                  betterchain::chain::transaction_exception, 3030007, "insufficient fee" )
   FC_DECLARE_DERIVED_EXCEPTION( tx_missing_recipient,              betterchain::chain::transaction_exception, 3030009, "missing required recipient" )
   FC_DECLARE_DERIVED_EXCEPTION( checktime_exceeded,                betterchain::chain::transaction_exception, 3030010, "allotted processing time was exceeded" )
   FC_DECLARE_DERIVED_EXCEPTION( tx_duplicate,                      betterchain::chain::transaction_exception, 3030011, "duplicate transaction" )
   FC_DECLARE_DERIVED_EXCEPTION( unknown_transaction_exception,     betterchain::chain::transaction_exception, 3030012, "unknown transaction" )
   FC_DECLARE_DERIVED_EXCEPTION( tx_scheduling_exception,           betterchain::chain::transaction_exception, 3030013, "transaction failed during sheduling" )
   FC_DECLARE_DERIVED_EXCEPTION( tx_unknown_argument,               betterchain::chain::transaction_exception, 3030014, "transaction provided an unknown value to a system call" )
   FC_DECLARE_DERIVED_EXCEPTION( tx_resource_exhausted,             betterchain::chain::transaction_exception, 3030015, "transaction exhausted allowed resources" )
   FC_DECLARE_DERIVED_EXCEPTION( page_memory_error,                 betterchain::chain::transaction_exception, 3030016, "error in WASM page memory" )
   FC_DECLARE_DERIVED_EXCEPTION( unsatisfied_permission,            betterchain::chain::transaction_exception, 3030017, "Unsatisfied permission" )
   FC_DECLARE_DERIVED_EXCEPTION( tx_msgs_auth_exceeded,             betterchain::chain::transaction_exception, 3030018, "Number of transaction messages per authorized account has been exceeded" )
   FC_DECLARE_DERIVED_EXCEPTION( tx_msgs_code_exceeded,             betterchain::chain::transaction_exception, 3030019, "Number of transaction messages per code account has been exceeded" )
   FC_DECLARE_DERIVED_EXCEPTION( wasm_execution_error,              betterchain::chain::transaction_exception, 3030020, "Runtime Error Processing WASM" )

   FC_DECLARE_DERIVED_EXCEPTION( account_name_exists_exception,     betterchain::chain::action_validate_exception, 3040001, "account name already exists" )
   FC_DECLARE_DERIVED_EXCEPTION( invalid_pts_address,               betterchain::chain::utility_exception, 3060001, "invalid pts address" )
   FC_DECLARE_DERIVED_EXCEPTION( insufficient_feeds,                betterchain::chain::chain_exception, 37006, "insufficient feeds" )

   FC_DECLARE_DERIVED_EXCEPTION( pop_empty_chain,                   betterchain::chain::undo_database_exception, 3070001, "there are no blocks to pop" )


   #define BETTERCHAIN_RECODE_EXC( cause_type, effect_type ) \
      catch( const cause_type& e ) \
      { throw( effect_type( e.what(), e.get_log() ) ); }

} } // betterchain::chain
