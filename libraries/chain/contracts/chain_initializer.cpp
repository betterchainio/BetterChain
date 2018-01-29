/**
 *  @file
 *  @copyright defined in BetterChain/LICENSE.txt
 */
#include <betterchain/chain/contracts/chain_initializer.hpp>
#include <betterchain/chain/contracts/objects.hpp>
#include <betterchain/chain/contracts/betterchain_contract.hpp>
#include <betterchain/chain/contracts/types.hpp>

#include <betterchain/chain/producer_object.hpp>
#include <betterchain/chain/permission_object.hpp>

#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/algorithm/copy.hpp>

namespace betterchain { namespace chain { namespace contracts {

time_point chain_initializer::get_chain_start_time() {
   return genesis.initial_timestamp;
}

chain_config chain_initializer::get_chain_start_configuration() {
   return genesis.initial_configuration;
}

producer_schedule_type chain_initializer::get_chain_start_producers() {
   producer_schedule_type result;
   std::transform(genesis.initial_producers.begin(), genesis.initial_producers.end(), result.producers.begin(),
                  [](const auto& p) { return producer_key{p.owner_name,p.block_signing_key}; });
   return result;
}

void chain_initializer::register_types(chain_controller& chain, chainbase::database& db) {
   // Install the native contract's indexes; we can't do anything until our objects are recognized
   db.add_index<staked_balance_multi_index>();
   db.add_index<producer_votes_multi_index>();

#define SET_APP_HANDLER( contract, scope, action, nspace ) \
   chain._set_apply_handler( #contract, #scope, #action, &BOOST_PP_CAT(contracts::apply_, BOOST_PP_CAT(contract, BOOST_PP_CAT(_,action) ) ) )

   SET_APP_HANDLER( betterchain, betterchain, setproducer, betterchain );
   SET_APP_HANDLER( betterchain, betterchain, newaccount, betterchain );
   SET_APP_HANDLER( betterchain, betterchain, transfer, betterchain );
   SET_APP_HANDLER( betterchain, betterchain, lock, betterchain );
   SET_APP_HANDLER( betterchain, betterchain, claim, betterchain );
   SET_APP_HANDLER( betterchain, betterchain, unlock, betterchain );
   SET_APP_HANDLER( betterchain, betterchain, okproducer, betterchain );
   SET_APP_HANDLER( betterchain, betterchain, setproxy, betterchain );
   SET_APP_HANDLER( betterchain, betterchain, setcode, betterchain );
   SET_APP_HANDLER( betterchain, betterchain, setabi, betterchain );
   SET_APP_HANDLER( betterchain, betterchain, updateauth, betterchain );
   SET_APP_HANDLER( betterchain, betterchain, deleteauth, betterchain );
   SET_APP_HANDLER( betterchain, betterchain, linkauth, betterchain );
   SET_APP_HANDLER( betterchain, betterchain, unlinkauth, betterchain );
   SET_APP_HANDLER( betterchain, betterchain, nonce, betterchain );
   SET_APP_HANDLER( betterchain, betterchain, onerror, betterchain );
   SET_APP_HANDLER( betterchain, betterchain, postrecovery, betterchain );
   SET_APP_HANDLER( betterchain, betterchain, passrecovery, betterchain );
   SET_APP_HANDLER( betterchain, betterchain, vetorecovery, betterchain );
}


abi_def chain_initializer::betterchain_contract_abi()
{
   abi_def betterchain_abi;
   betterchain_abi.types.push_back( type_def{"account_name","name"} );
   betterchain_abi.types.push_back( type_def{"share_type","int64"} );
   betterchain_abi.types.push_back( type_def{"onerror","bytes"} );
   betterchain_abi.actions.push_back( action_def{name("transfer"), "transfer"} );
   betterchain_abi.actions.push_back( action_def{name("lock"), "lock"} );
   betterchain_abi.actions.push_back( action_def{name("unlock"), "unlock"} );
   betterchain_abi.actions.push_back( action_def{name("claim"), "claim"} );
   betterchain_abi.actions.push_back( action_def{name("okproducer"), "okproducer"} );
   betterchain_abi.actions.push_back( action_def{name("setproducer"), "setproducer"} );
   betterchain_abi.actions.push_back( action_def{name("setproxy"), "setproxy"} );
   betterchain_abi.actions.push_back( action_def{name("setcode"), "setcode"} );
   betterchain_abi.actions.push_back( action_def{name("setabi"), "setabi"} );
   betterchain_abi.actions.push_back( action_def{name("linkauth"), "linkauth"} );
   betterchain_abi.actions.push_back( action_def{name("unlinkauth"), "unlinkauth"} );
   betterchain_abi.actions.push_back( action_def{name("updateauth"), "updateauth"} );
   betterchain_abi.actions.push_back( action_def{name("deleteauth"), "deleteauth"} );
   betterchain_abi.actions.push_back( action_def{name("newaccount"), "newaccount"} );
   betterchain_abi.actions.push_back( action_def{name("postrecovery"), "postrecovery"} );
   betterchain_abi.actions.push_back( action_def{name("passrecovery"), "passrecovery"} );
   betterchain_abi.actions.push_back( action_def{name("vetorecovery"), "vetorecovery"} );
   betterchain_abi.actions.push_back( action_def{name("onerror"), "onerror"} );
   betterchain_abi.actions.push_back( action_def{name("nonce"), "nonce"} );

   // ACTION PAYLOADS
   betterchain_abi.structs.emplace_back( struct_def {
      "transfer", "", {
         {"from", "account_name"},
         {"to", "account_name"},
         {"amount", "uint64"},
         {"memo", "string"},
      }
   });

   betterchain_abi.structs.emplace_back( struct_def {
      "lock", "", {
         {"from", "account_name"},
         {"to", "account_name"},
         {"amount", "share_type"},
      }
   });

   betterchain_abi.structs.emplace_back( struct_def {
      "unlock", "", {
         {"account", "account_name"},
         {"amount", "share_type"},
      }
   });

   betterchain_abi.structs.emplace_back( struct_def {
      "claim", "", {
         {"account", "account_name"},
         {"amount", "share_type"},
      }
   });

   betterchain_abi.structs.emplace_back( struct_def {
      "okproducer", "", {
         {"voter", "account_name"},
         {"producer", "account_name"},
         {"approve", "int8"},
      }
   });

   betterchain_abi.structs.emplace_back( struct_def {
      "setproducer", "", {
         {"name", "account_name"},
         {"key", "public_key"},
         {"configuration", "chain_config"},
      }
   });

   betterchain_abi.structs.emplace_back( struct_def {
      "setproxy", "", {
         {"stakeholder", "account_name"},
         {"proxy", "account_name"},
      }
   });

   betterchain_abi.structs.emplace_back( struct_def {
      "setcode", "", {
         {"account", "account_name"},
         {"vmtype", "uint8"},
         {"vmversion", "uint8"},
         {"code", "bytes"}
      }
   });

   betterchain_abi.structs.emplace_back( struct_def {
      "setabi", "", {
         {"account", "account_name"},
         {"abi", "abi_def"}
      }
   });

   betterchain_abi.structs.emplace_back( struct_def {
      "updateauth", "", {
         {"account", "account_name"},
         {"permission", "permission_name"},
         {"parent", "permission_name"},
         {"data", "authority"},
      }
   });

   betterchain_abi.structs.emplace_back( struct_def {
      "linkauth", "", {
         {"account", "account_name"},
         {"code", "account_name"},
         {"type", "action_name"},
         {"requirement", "permission_name"},
      }
   });

   betterchain_abi.structs.emplace_back( struct_def {
      "unlinkauth", "", {
         {"account", "account_name"},
         {"code", "account_name"},
         {"type", "action_name"},
      }
   });

   betterchain_abi.structs.emplace_back( struct_def {
      "deleteauth", "", {
         {"account", "account_name"},
         {"permission", "permission_name"},
      }
   });

   betterchain_abi.structs.emplace_back( struct_def {
      "newaccount", "", {
         {"creator", "account_name"},
         {"name", "account_name"},
         {"owner", "authority"},
         {"active", "authority"},
         {"recovery", "authority"},
         {"deposit", "asset"},
      }
   });

   betterchain_abi.structs.emplace_back( struct_def {
      "postrecovery", "", {
         {"account", "account_name"},
         {"data", "authority"},
         {"memo", "string"},
      }
   });

   betterchain_abi.structs.emplace_back( struct_def {
      "passrecovery", "", {
         {"account", "account_name"},
      }
   });

   betterchain_abi.structs.emplace_back( struct_def {
      "vetorecovery", "", {
         {"account", "account_name"},
      }
   });

   betterchain_abi.structs.emplace_back( struct_def {
      "nonce", "", {
         {"value", "name"}
      }
   });

   // DATABASE RECORDS
   betterchain_abi.structs.emplace_back( struct_def {
      "account", "", {
         {"key",     "name"},
         {"balance", "uint64"},
      }
   });

   betterchain_abi.structs.emplace_back( struct_def {
      "pending_recovery", "", {
         {"account",    "name"},
         {"request_id", "uint32"},
         {"update",     "updateauth"},
         {"memo",       "string"}
      }
   });

   betterchain_abi.tables.emplace_back( table_def {
      "currency", "i64", {
         "key"
      }, {
         "name"
      },
      "account"
   });

   betterchain_abi.tables.emplace_back( table_def {
      "recovery", "i64", {
         "account",
      }, {
         "name"
      },
      "pending_recovery"
   });


   return betterchain_abi;
}

// forward declared method from betterchain contract
void intialize_betterchain_tokens(chainbase::database& db, const account_name& system_account, share_type initial_tokens);


std::vector<action> chain_initializer::prepare_database( chain_controller& chain,
                                                         chainbase::database& db) {
   std::vector<action> messages_to_process;

   /// Create the native contract accounts manually; sadly, we can't run their contracts to make them create themselves
   auto create_native_account = [this, &db](account_name name, auto liquid_balance) {
      db.create<account_object>([this, &name](account_object& a) {
         a.name = name;
         a.creation_date = genesis.initial_timestamp;

         if( name == config::system_account_name ) {
            a.set_abi(betterchain_contract_abi());
         }
      });
      const auto& owner = db.create<permission_object>([&name](permission_object& p) {
         p.owner = name;
         p.name = "owner";
         p.auth.threshold = 1;
      });
      db.create<permission_object>([&name, &owner](permission_object& p) {
         p.owner = name;
         p.parent = owner.id;
         p.name = "active";
         p.auth.threshold = 1;
      });
      intialize_betterchain_tokens(db, name, liquid_balance);
      db.create<staked_balance_object>([&](auto& sb) { sb.owner_name = name; });
      db.create<bandwidth_usage_object>([&](auto& sb) { sb.owner = name; });
   };
   create_native_account(config::system_account_name, config::initial_token_supply);

   // Queue up messages which will run contracts to create the initial accounts
   for (const auto& acct : genesis.initial_accounts) {
      action message( {{config::system_account_name, config::active_name}},
                      newaccount{ config::system_account_name, acct.name,
                                                             authority(acct.owner_key),
                                                             authority(acct.active_key),
                                                             authority(acct.owner_key),
                                                             acct.staking_balance});

      messages_to_process.emplace_back(move(message));

      if (acct.liquid_balance > 0) {
         message = action( {{config::system_account_name, config::active_name}},
                           transfer{ .from = config::system_account_name, .to = acct.name,
                                     .amount = acct.liquid_balance.amount, .memo = "Genesis Allocation"});
         messages_to_process.emplace_back(move(message));
      }
   }

   // Create initial producers
   auto create_producer = boost::adaptors::transformed([config = genesis.initial_configuration](const auto& p) {
      return action( {{p.owner_name, config::active_name}},
                     setproducer(p.owner_name, p.block_signing_key, config));
   });
   boost::copy(genesis.initial_producers | create_producer, std::back_inserter(messages_to_process));

   // Create special accounts
   auto create_special_account = [this, &db](account_name name, const auto& owner, const auto& active) {
      db.create<account_object>([this, &name](account_object& a) {
         a.name = name;
         a.creation_date = genesis.initial_timestamp;
      });
      const auto& owner_permission = db.create<permission_object>([&owner, &name](permission_object& p) {
         p.name = config::owner_name;
         p.parent = 0;
         p.owner = name;
         p.auth = move(owner);
      });
      db.create<permission_object>([&active, &owner_permission](permission_object& p) {
         p.name = config::active_name;
         p.parent = owner_permission.id;
         p.owner = owner_permission.owner;
         p.auth = move(active);
      });
   };

   auto empty_authority = authority(0, {}, {});
   auto active_producers_authority = authority(config::producers_authority_threshold, {}, {});
   for(auto& p : genesis.initial_producers) {
      active_producers_authority.accounts.push_back({{p.owner_name, config::active_name}, 1});
   }

   create_special_account(config::nobody_account_name, empty_authority, empty_authority);
   create_special_account(config::producers_account_name, empty_authority, active_producers_authority);

   return messages_to_process;
}

} } } // namespace betterchain::chain::contracts
