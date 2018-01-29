#include <lib/preprocessor/seq/for_each.hpp>
#include <lib/preprocessor/seq/enum.hpp>
#include <lib/preprocessor/seq/size.hpp>
#include <lib/preprocessor/seq/seq.hpp>
#include <lib/preprocessor/stringize.hpp>

#define BetterChainLIB_REFLECT_MEMBER_OP( r, OP, elem ) \
  OP t.elem 

/**
 *  @def BetterChainLIB_SERIALIZE(TYPE,MEMBERS)
 *
 *  @brief Specializes betterchain::reflector for TYPE where
 *         type inherits other reflected classes
 *
 *  @param INHERITS - a sequence of base class names (basea)(baseb)(basec)
 *  @param MEMBERS - a sequence of member names.  (field1)(field2)(field3)
 */
#define BetterChainLIB_SERIALIZE( TYPE,  MEMBERS ) \
 template<typename DataStream> \
 friend DataStream& operator << ( DataStream& ds, const TYPE& t ){ \
    return ds BOOST_PP_SEQ_FOR_EACH( BetterChainLIB_REFLECT_MEMBER_OP, <<, MEMBERS );\
 }\
 template<typename DataStream> \
 friend DataStream& operator >> ( DataStream& ds, TYPE& t ){ \
    return ds BOOST_PP_SEQ_FOR_EACH( BetterChainLIB_REFLECT_MEMBER_OP, >>, MEMBERS );\
 } 


#define BetterChainLIB_SERIALIZE_DERIVED( TYPE, BASE, MEMBERS ) \
 template<typename DataStream> \
 friend DataStream& operator << ( DataStream& ds, const TYPE& t ){ \
    ds << static_cast<const BASE&>(t); \
    return ds BOOST_PP_SEQ_FOR_EACH( BetterChainLIB_REFLECT_MEMBER_OP, <<, MEMBERS );\
 }\
 template<typename DataStream> \
 friend DataStream& operator >> ( DataStream& ds, TYPE& t ){ \
    ds >> static_cast<BASE&>(t); \
    return ds BOOST_PP_SEQ_FOR_EACH( BetterChainLIB_REFLECT_MEMBER_OP, >>, MEMBERS );\
 } 
