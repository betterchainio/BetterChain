/**
 *  @file
 *  @copyright defined in BetterChain/LICENSE.txt
 */
#include <currency/currency.hpp>

namespace exchange {

   using currency::currency_tokens;
   using betterchain_tokens = betterchain::tokens;

   //@abi action cancelbuy cancelsell
   struct order_id {
      account_name name    = 0;
      uint64_t    number  = 0;
   };

   typedef betterchain::price<betterchain_tokens,currency_tokens>     price;

   //@abi table
   struct PACKED( bid ) {
      order_id           buyer;
      price              at_price;
      betterchain::tokens      quantity;
      time               expiration;

      void print() {
         betterchain::print( "{ quantity: ", quantity, ", price: ", at_price, " }" );
      }
   };
   static_assert( sizeof(bid) == 32+12, "unexpected padding" );

   //@abi table 
   struct PACKED( ask ) {
      order_id         seller;
      price            at_price;
      currency_tokens  quantity;
      time             expiration;

      void print() {
         betterchain::print( "{ quantity: ", quantity, ", price: ", at_price, " }" );
      }
   };
   static_assert( sizeof(ask) == 32+12, "unexpected padding" );

   //@abi table i64
   struct PACKED( account ) {
      account( account_name o = account_name() ):owner(o){}

      account_name       owner;
      betterchain_tokens         betterchain_balance;
      currency_tokens    currency_balance;
      uint32_t           open_orders = 0;

      bool is_empty()const { return ! ( bool(betterchain_balance) | bool(currency_balance) | open_orders); }
   };

   using accounts = betterchain::table<N(exchange),N(exchange),N(account),account,uint64_t>;

   TABLE2(bids,exchange,exchange,bids,bid,bids_by_id,order_id,bids_by_price,price);
   TABLE2(asks,exchange,exchange,asks,ask,asks_by_id,order_id,asks_by_price,price);



   //@abi action buy
   struct buy_order : public bid  { uint8_t fill_or_kill = false; };

   //@abi action sell
   struct sell_order : public ask { uint8_t fill_or_kill = false; };


   inline account get_account( account_name owner ) {
      account owned_account(owner);
      accounts::get( owned_account );
      return owned_account;

   }
}

