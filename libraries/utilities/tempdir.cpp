/**
 *  @file
 *  @copyright defined in BetterChain/LICENSE.txt
 */

#include <betterchain/utilities/tempdir.hpp>

#include <cstdlib>

namespace betterchain { namespace utilities {

fc::path temp_directory_path()
{
   const char* betterchain_tempdir = getenv("BETTERCHAIN_TEMPDIR");
   if( betterchain_tempdir != nullptr )
      return fc::path( betterchain_tempdir );
   return fc::temp_directory_path() / "betterchain-tmp";
}

} } // betterchain::utilities
