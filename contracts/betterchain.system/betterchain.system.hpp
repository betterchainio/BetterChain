/**
 *  @file
 *  @copyright defined in BetterChain/LICENSE.txt
 */
#include <lib/betterchain.hpp>
#include <lib/token.hpp>
#include <lib/db.hpp>
#include <lib/reflect.hpp>

#include <lib/generic_currency.hpp>
#include <lib/datastream.hpp>
#include <lib/serialize.hpp>

namespace betterchainsystem {

   template<account_name SystemAccount>
   class contract {
      public:
         static const account_name system_account = N(betterchain.system);
         typedef betterchain::generic_currency< betterchain::token<system_account,S(4,BetterChain)> > currency;

         ACTION( SystemAccount, regproducer ) {
            account_name producer_to_register;

            BetterChainLIB_SERIALIZE( regproducer, (producer_to_register) );
         };

         ACTION( SystemAccount, regproxy ) {
            account_name proxy_to_register;

            BetterChainLIB_SERIALIZE( regproxy, (proxy_to_register) );
         };

         static void on( const regproducer& reg ) {
            require_auth( reg.producer_to_register );
         }

         static void on( const regproxy& reg ) {
            require_auth( reg.proxy_to_register );
         }


         static void apply( account_name code, action_name act ) {
            if( !betterchain::dispatch<contract, 
//                   typename currency::transfer_memo, 
 //                  typename currency::issue,
                   regproducer,
                   regproxy
                   >( code, act) ) 
            {
               assert( false, "received unexpected action" );
            }
         } /// apply 
   };

} /// betterchainsystem 

