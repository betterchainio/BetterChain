/**
 *  @file
 *  @copyright defined in BetterChain/LICENSE.txt
 */

#include <lib/betterchain.hpp>

namespace asserter {
   struct PACKED(assertdef) {
      int8_t   condition;
      int8_t   message_length;
      char     message[];
   };
}