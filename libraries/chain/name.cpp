#include <betterchain/chain/name.hpp>
#include <fc/variant.hpp>
#include <boost/algorithm/string.hpp>
#include <fc/exception/exception.hpp>

namespace betterchain { namespace chain { 

   void name::set( const char* str ) {
   try {
      const auto len = strnlen(str,14);
      FC_ASSERT( len <= 13 );
      value = string_to_name(str);
      FC_ASSERT( to_string() == string(str), "name not properly normalized", ("name",string(str))("normalized",to_string())  );
   }FC_CAPTURE_AND_RETHROW( (str) ) }

   name::operator string()const {
     static const char* charmap = ".12345abcdefghijklmnopqrstuvwxyz";

      string str(13,'.');

      uint64_t tmp = value;
      for( uint32_t i = 0; i <= 12; ++i ) {
         char c = charmap[tmp & (i == 0 ? 0x0f : 0x1f)];
         str[12-i] = c;
         tmp >>= (i == 0 ? 4 : 5);
      }

      boost::algorithm::trim_right_if( str, []( char c ){ return c == '.'; } );
      return str;
   }

} } /// betterchain::chain

namespace fc {
  void to_variant(const betterchain::chain::name& c, fc::variant& v) { v = std::string(c); }
  void from_variant(const fc::variant& v, betterchain::chain::name& check) { check = v.get_string(); }
} // fc
