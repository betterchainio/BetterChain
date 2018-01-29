/**
 *  @file
 *  @copyright defined in BetterChain/LICENSE.txt
 */
#include "simpledb.hpp"
#include "simpledb.gen.hpp"

#include <lib/db.hpp>
#include <lib/types.hpp>
#include <lib/raw.hpp>

extern "C" {
   void init()  {

   }
   
   void apply( uint64_t code, uint64_t action ) {
      if( code == N(simpledb) ) {
         if( action == N(insertkv1) ) {
            // betterchainc push message simpledb insertkv1 '{"key":"a", "value":"aa"}' -S simpledb
            // betterchainc get table simpledb simpledb keyvalue1
            auto kv1 = betterchain::current_action<key_value1>();
            betterchain::print("Inserting key_value1\n");
            betterchain::dump(kv1);
            bytes b = betterchain::raw::pack(kv1.value);
            uint32_t err = store_str( N(simpledb), N(keyvalue1), (char *)kv1.key.get_data(), kv1.key.get_size(), (char*)b.data, b.len);
         } else if( action == N(insertkv2) ) {
            // betterchainc push message simpledb insertkv2 '{"key":"a", "value":{"name":"aaa", "age":10}}' -S simpledb
            // betterchainc get table simpledb simpledb keyvalue2
            auto kv2 = betterchain::current_action<key_value2>();
            betterchain::print("Inserting key_value2\n");
            betterchain::dump(kv2);
            bytes b = betterchain::raw::pack(kv2.value);
            uint32_t err = store_str( N(simpledb), N(keyvalue2), (char *)kv2.key.get_data(), kv2.key.get_size(), (char*)b.data, b.len);
         } else if( action == N(insert1) ) {
            // betterchainc push message simpledb insert1 '{"key":75}' -S simpledb
            // betterchainc get table simpledb simpledb record1
            auto tmp = betterchain::current_action<record1>();
            betterchain::print("Inserting record1\n");
            betterchain::dump(tmp);
            auto bytes = betterchain::raw::pack(tmp);
            store_i64( N(simpledb), N(record1), bytes.data, bytes.len);
         } else if(action == N(insert2)) {
            // betterchainc push message simpledb insert2 '{"key1":"75", "key2":"77"}' -S simpledb
            // betterchainc get table simpledb simpledb record2
            auto tmp = betterchain::current_action<record2>();
            betterchain::print("Inserting record2\n");
            betterchain::dump(tmp);
            auto bytes = betterchain::raw::pack(tmp);
            store_i128i128( N(simpledb), N(record2), bytes.data, bytes.len);
         } else if(action == N(insert3)) {
            // betterchainc push message simpledb insert3 '{"key1":75, "key2":77, "key3":79}' -S simpledb
            // betterchainc get table simpledb simpledb record3
            auto tmp = betterchain::current_action<record3>();
            betterchain::print("Inserting record3\n");
            betterchain::dump(tmp);
            auto bytes = betterchain::raw::pack(tmp);
            store_i64i64i64( N(simpledb), N(record3), bytes.data, bytes.len);
         } else {
            assert(0, "unknown message");
         }
      }
   }
}
