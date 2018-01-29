/**
 *  @file
 *  @copyright defined in BetterChain/LICENSE.txt
 */
#pragma once
#include <appbase/application.hpp>
#include <betterchain/chain/asset.hpp>
#include <betterchain/chain/authority.hpp>
#include <betterchain/chain/account_object.hpp>
#include <betterchain/chain/block.hpp>
#include <betterchain/chain/chain_controller.hpp>
#include <betterchain/chain/contracts/contract_table_objects.hpp>
#include <betterchain/chain/transaction.hpp>
#include <betterchain/chain/contracts/abi_serializer.hpp>

#include <boost/container/flat_set.hpp>

namespace fc { class variant; }

namespace betterchain {
   using chain::chain_controller;
   using std::unique_ptr;
   using namespace appbase;
   using chain::name;
   using chain::uint128_t;
   using chain::public_key_type;
   using fc::optional;
   using boost::container::flat_set;
   using chain::asset;
   using chain::authority;
   using chain::account_name;
   using chain::contracts::abi_def;
   using chain::contracts::abi_serializer;

namespace chain_apis {
struct empty{};

struct permission {
   name              perm_name;
   name              parent;
   authority         required_auth;
};

class read_only {
   const chain_controller& db;

public:
   static const string KEYi64;
   static const string KEYstr;
   static const string KEYi128i128;
   static const string KEYi64i64i64;
   static const string PRIMARY;
   static const string SECONDARY;
   static const string TERTIARY;
   
   read_only(const chain_controller& db)
      : db(db) {}

   using get_info_params = empty;

   struct get_info_results {
      string                  server_version;
      uint32_t                head_block_num = 0;
      uint32_t                last_irreversible_block_num = 0;
      chain::block_id_type    head_block_id;
      fc::time_point_sec      head_block_time;
      account_name            head_block_producer;
      string                  recent_slots;
      double                  participation_rate = 0;
   };
   get_info_results get_info(const get_info_params&) const;

   struct producer_info {
      name                       producer_name;
   };


   struct get_account_results {
      name                       account_name;
      asset                      betterchain_balance = asset(0,BETTERCHAIN_SYMBOL);
      asset                      staked_balance;
      asset                      unstaking_balance;
      fc::time_point_sec         last_unstaking_time;
      vector<permission>         permissions;
      optional<producer_info>    producer;
   };
   struct get_account_params {
      name account_name;
   };
   get_account_results get_account( const get_account_params& params )const;


   struct get_code_results {
      name                   account_name;
      string                 wast;
      fc::sha256             code_hash;
      optional<abi_def>      abi;
   };

   struct get_code_params {
      name account_name;
   };
   get_code_results get_code( const get_code_params& params )const;



   struct abi_json_to_bin_params {
      name         code;
      name         action;
      fc::variant  args;
   };
   struct abi_json_to_bin_result {
      vector<char>   binargs;
      vector<name>   required_scope;
      vector<name>   required_auth;
   };
      
   abi_json_to_bin_result abi_json_to_bin( const abi_json_to_bin_params& params )const;


   struct abi_bin_to_json_params {
      name         code;
      name         action;
      vector<char> binargs;
   };
   struct abi_bin_to_json_result {
      fc::variant    args;
      vector<name>   required_scope;
      vector<name>   required_auth;
   };
      
   abi_bin_to_json_result abi_bin_to_json( const abi_bin_to_json_params& params )const;


   struct get_required_keys_params {
      fc::variant transaction;
      flat_set<public_key_type> available_keys;
   };
   struct get_required_keys_result {
      flat_set<public_key_type> required_keys;
   };

   get_required_keys_result get_required_keys( const get_required_keys_params& params)const;


   struct get_block_params {
      string block_num_or_id;
   };

   struct get_block_results : public chain::signed_block {
      get_block_results( const chain::signed_block& b )
      :signed_block(b),
      id(b.id()),
      block_num(b.block_num()),
      ref_block_prefix( id._hash[1] )
      {}

      chain::block_id_type id;
      uint32_t             block_num = 0;
      uint32_t             ref_block_prefix = 0;
   };

   get_block_results get_block(const get_block_params& params) const;

   struct get_table_rows_params {
      bool        json = false;
      name        scope;
      name        code;
      name        table;
//      string      table_type;
      string      table_key;
      string      lower_bound;
      string      upper_bound;
      uint32_t    limit = 10;
    };

   struct get_table_rows_result {
      vector<fc::variant> rows; ///< one row per item, either encoded as hex String or JSON object 
      bool                more = false; ///< true if last element in data is not the end and sizeof data() < limit
   };

   get_table_rows_result get_table_rows( const get_table_rows_params& params )const;

   struct get_currency_balance_params {
      name             code;
      name             account;
      optional<string> symbol;
   };

   vector<asset> get_currency_balance( const get_currency_balance_params& params )const;

   struct get_currency_stats_params {
      name             code;
      optional<string> symbol;
   };

   struct get_currency_stats_result {
      asset        supply;
   };

   fc::variant get_currency_stats( const get_currency_stats_params& params )const;

   void copy_row(const chain::contracts::key_value_object& obj, vector<char>& data)const {
      data.resize( sizeof(uint64_t) + obj.value.size() );
      memcpy( data.data(), &obj.primary_key, sizeof(uint64_t) );
      memcpy( data.data()+sizeof(uint64_t), obj.value.data(), obj.value.size() );
   }

   void copy_row(const chain::contracts::keystr_value_object& obj, vector<char>& data)const {
      data.resize( obj.primary_key.size() + obj.value.size() + 8 );
      fc::datastream<char*> ds(data.data(), data.size());
      fc::raw::pack(ds, obj.primary_key);
      ds.write(obj.value.data(), obj.value.size());
      data.resize(ds.tellp());
   }

   void copy_row(const chain::contracts::key128x128_value_object& obj, vector<char>& data)const {
      data.resize( 2*sizeof(uint128_t) + obj.value.size() );
      memcpy( data.data(), &obj.primary_key, sizeof(uint128_t) );
      memcpy( data.data()+sizeof(uint128_t), &obj.secondary_key, sizeof(uint128_t) );
      memcpy( data.data()+2*sizeof(uint128_t), obj.value.data(), obj.value.size() );
   }

   void copy_row(const chain::contracts::key64x64x64_value_object& obj, vector<char>& data)const {
      data.resize( 3*sizeof(uint64_t) + obj.value.size() );
      memcpy( data.data(), &obj.primary_key, sizeof(uint64_t) );
      memcpy( data.data()+sizeof(uint64_t), &obj.secondary_key, sizeof(uint64_t) );
      memcpy( data.data()+2*sizeof(uint64_t), &obj.tertiary_key, sizeof(uint64_t) );
      memcpy( data.data()+3*sizeof(uint64_t), obj.value.data(), obj.value.size() );
   }

   template<typename IndexType, typename Scope, typename Function>
   void walk_table(const name& scope, const name& code, const name& table, Function f) const
   {
      const auto& d = db.get_database();
      const auto* t_id = d.find<chain::contracts::table_id_object, chain::contracts::by_scope_code_table>(boost::make_tuple(scope, code, table));
      if (t_id != nullptr) {
         const auto &idx = d.get_index<IndexType, Scope>();
         decltype(t_id->id) next_tid(t_id->id._id + 1);
         auto lower = idx.lower_bound(boost::make_tuple(t_id->id));
         auto upper = idx.lower_bound(boost::make_tuple(next_tid));

         for (auto itr = lower; itr != upper; ++itr) {
            if (!f(*itr)) {
               break;
            }
         }
      }
   }
 
   template <typename IndexType, typename Scope>
   read_only::get_table_rows_result get_table_rows_ex( const read_only::get_table_rows_params& p, const abi_def& abi )const {
      read_only::get_table_rows_result result;
      const auto& d = db.get_database();

      abi_serializer abis;
      abis.set_abi(abi);
      const auto* t_id = d.find<chain::contracts::table_id_object, chain::contracts::by_scope_code_table>(boost::make_tuple(p.scope, p.code, p.table));
      if (t_id != nullptr) {
         const auto &idx = d.get_index<IndexType, Scope>();
         decltype(t_id->id) next_tid(t_id->id._id + 1);
         auto lower = idx.lower_bound(boost::make_tuple(t_id->id));
         auto upper = idx.lower_bound(boost::make_tuple(next_tid));

         if (p.lower_bound.size()) {
            lower = idx.lower_bound(boost::make_tuple(t_id->id, fc::variant(
               p.lower_bound).as<typename IndexType::value_type::key_type>()));
         }
         if (p.upper_bound.size()) {
            upper = idx.lower_bound(boost::make_tuple(t_id->id, fc::variant(
               p.upper_bound).as<typename IndexType::value_type::key_type>()));
         }

         vector<char> data;

         auto end = fc::time_point::now() + fc::microseconds(1000 * 10); /// 10ms max time

         unsigned int count = 0;
         auto itr = lower;
         for (itr = lower; itr != upper; ++itr) {
            copy_row(*itr, data);

            if (p.json) {
               result.rows.emplace_back(abis.binary_to_variant(abis.get_table_type(p.table), data));
            } else {
               result.rows.emplace_back(fc::variant(data));
            }

            if (++count == p.limit || fc::time_point::now() > end) {
               break;
            }
         }
         if (itr != upper) {
            result.more = true;
         }
      }
      return result;
   }
      
};

class read_write {
   chain_controller& db;
   uint32_t skip_flags;
public:
   read_write(chain_controller& db, uint32_t skip_flags) : db(db), skip_flags(skip_flags) {}

   using push_block_params = chain::signed_block;
   using push_block_results = empty;
   push_block_results push_block(const push_block_params& params);

   using push_transaction_params = fc::variant_object;
   struct push_transaction_results {
      chain::transaction_id_type  transaction_id;
      fc::variant                 processed;
   };
   push_transaction_results push_transaction(const push_transaction_params& params);


   using push_transactions_params  = vector<push_transaction_params>;
   using push_transactions_results = vector<push_transaction_results>;
   push_transactions_results push_transactions(const push_transactions_params& params);
};
} // namespace chain_apis

class chain_plugin : public plugin<chain_plugin> {
public:
   APPBASE_PLUGIN_REQUIRES()

   chain_plugin();
   virtual ~chain_plugin();

   virtual void set_program_options(options_description& cli, options_description& cfg) override;

   void plugin_initialize(const variables_map& options);
   void plugin_startup();
   void plugin_shutdown();

   chain_apis::read_only get_read_only_api() const { return chain_apis::read_only(chain()); }
   chain_apis::read_write get_read_write_api();

   bool accept_block(const chain::signed_block& block, bool currently_syncing);
   void accept_transaction(const chain::signed_transaction& trx);

   bool block_is_on_preferred_chain(const chain::block_id_type& block_id);

   // return true if --skip-transaction-signatures passed to betterchaind
   bool is_skipping_transaction_signatures() const;

   // Only call this in plugin_initialize() to modify chain_controller constructor configuration
   chain_controller::controller_config& chain_config();
   // Only call this after plugin_startup()!
   chain_controller& chain();
   // Only call this after plugin_startup()!
   const chain_controller& chain() const;

  void get_chain_id (chain::chain_id_type &cid) const;

  static const uint32_t            default_received_block_transaction_execution_time;
  static const uint32_t            default_transaction_execution_time;
  static const uint32_t            default_create_block_transaction_execution_time;

private:
   unique_ptr<class chain_plugin_impl> my;
};

}

FC_REFLECT( betterchain::chain_apis::permission, (perm_name)(parent)(required_auth) )
FC_REFLECT(betterchain::chain_apis::empty, )
FC_REFLECT(betterchain::chain_apis::read_only::get_info_results,
  (server_version)(head_block_num)(last_irreversible_block_num)(head_block_id)(head_block_time)(head_block_producer)
  (recent_slots)(participation_rate))
FC_REFLECT(betterchain::chain_apis::read_only::get_block_params, (block_num_or_id))
  
FC_REFLECT_DERIVED( betterchain::chain_apis::read_only::get_block_results, (betterchain::chain::signed_block), (id)(block_num)(ref_block_prefix) );
FC_REFLECT( betterchain::chain_apis::read_write::push_transaction_results, (transaction_id)(processed) )
  
FC_REFLECT( betterchain::chain_apis::read_only::get_table_rows_params, (json)(scope)(code)(table)(table_key)(lower_bound)(upper_bound)(limit) )
FC_REFLECT( betterchain::chain_apis::read_only::get_table_rows_result, (rows)(more) );

FC_REFLECT( betterchain::chain_apis::read_only::get_currency_balance_params, (code)(account)(symbol));
FC_REFLECT( betterchain::chain_apis::read_only::get_currency_stats_params, (code)(symbol));
FC_REFLECT( betterchain::chain_apis::read_only::get_currency_stats_result, (supply));

FC_REFLECT( betterchain::chain_apis::read_only::get_account_results, (account_name)(betterchain_balance)(staked_balance)(unstaking_balance)(last_unstaking_time)(permissions)(producer) )
FC_REFLECT( betterchain::chain_apis::read_only::get_code_results, (account_name)(code_hash)(wast)(abi) )
FC_REFLECT( betterchain::chain_apis::read_only::get_account_params, (account_name) )
FC_REFLECT( betterchain::chain_apis::read_only::get_code_params, (account_name) )
FC_REFLECT( betterchain::chain_apis::read_only::producer_info, (producer_name) )
FC_REFLECT( betterchain::chain_apis::read_only::abi_json_to_bin_params, (code)(action)(args) )
FC_REFLECT( betterchain::chain_apis::read_only::abi_json_to_bin_result, (binargs)(required_scope)(required_auth) )
FC_REFLECT( betterchain::chain_apis::read_only::abi_bin_to_json_params, (code)(action)(binargs) )
FC_REFLECT( betterchain::chain_apis::read_only::abi_bin_to_json_result, (args)(required_scope)(required_auth) )
FC_REFLECT( betterchain::chain_apis::read_only::get_required_keys_params, (transaction)(available_keys) )
FC_REFLECT( betterchain::chain_apis::read_only::get_required_keys_result, (required_keys) )
