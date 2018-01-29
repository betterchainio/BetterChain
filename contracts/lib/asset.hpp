#pragma once

namespace betterchain {

   static constexpr uint64_t string_to_symbol( uint8_t precision, const char* str ) {
      uint32_t len = 0;
      while( str[len] ) ++len;

      uint64_t result = 0;
      for( uint32_t i = 0; i < len; ++i ) {
         if( str[i] < 'A' || str[i] > 'Z' ) {
            /// ERRORS?
         } else {
            result |= (uint64_t(str[i]) << (8*(1+i)));
         }
      }

      result |= uint64_t(precision);
      return result;
   }

   #define S(P,X) ::betterchain::string_to_symbol(P,#X)

   typedef uint64_t symbol_name;

   struct asset {
      uint64_t     amount = 0;
      symbol_name  symbol = S(4,BetterChain);

      asset( uint64_t a = 0, uint64_t s = S(4,BetterChain))
      :amount(a),symbol(s){}


      template<typename DataStream>
      friend DataStream& operator << ( DataStream& ds, const asset& t ){
         return ds << t.amount << t.symbol;
      }
      template<typename DataStream>
      friend DataStream& operator >> ( DataStream& ds, asset& t ){
         return ds >> t.amount >> t.symbol;
      }
   };

} /// namespace betterchain 
