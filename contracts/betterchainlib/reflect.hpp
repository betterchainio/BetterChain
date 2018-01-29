#pragma once
#include <lib/utility.hpp>
#include <lib/preprocessor/seq/for_each.hpp>
#include <lib/preprocessor/seq/enum.hpp>
#include <lib/preprocessor/seq/size.hpp>
#include <lib/preprocessor/seq/seq.hpp>
#include <lib/preprocessor/stringize.hpp>

namespace betterchain {
  template<typename T>
  struct reflector {
     typedef false_type is_reflected;
     typedef false_type is_enum;
  };

} /// betterchain



#define BetterChainLIB_REFLECT_VISIT_BASE(r, visitor, base) \
  betterchain::reflector<base>::visit( visitor );

#define BetterChainLIB_REFLECT_VISIT2_BASE(r, visitor, base) \
  betterchain::reflector<base>::visit( t, forward<Visitor>(visitor) );


#define BetterChainLIB_REFLECT_VISIT_MEMBER( r, visitor, elem ) \
{ typedef decltype((static_cast<type*>(nullptr))->elem) member_type;  \
   visitor( &type::elem ); \
}

#define BetterChainLIB_REFLECT_VISIT2_MEMBER( r, visitor, elem ) \
{ typedef decltype((static_cast<type*>(nullptr))->elem) member_type;  \
   visitor( t.elem ); \
}


#define BetterChainLIB_REFLECT_BASE_MEMBER_COUNT( r, OP, elem ) \
  OP betterchain::reflector<elem>::total_member_count

#define BetterChainLIB_REFLECT_MEMBER_COUNT( r, OP, elem ) \
  OP 1

#define BetterChainLIB_REFLECT_DERIVED_IMPL_INLINE( TYPE, INHERITS, MEMBERS ) \
template<typename Visitor>\
static inline void visit( Visitor&& v ) { \
    BOOST_PP_SEQ_FOR_EACH( BetterChainLIB_REFLECT_VISIT_BASE, v, INHERITS ) \
    BOOST_PP_SEQ_FOR_EACH( BetterChainLIB_REFLECT_VISIT_MEMBER, v, MEMBERS ) \
} \
template<typename Visitor>\
static inline void visit( const type& t, Visitor&& v ) { \
    BOOST_PP_SEQ_FOR_EACH( BetterChainLIB_REFLECT_VISIT2_BASE, v, INHERITS ) \
    BOOST_PP_SEQ_FOR_EACH( BetterChainLIB_REFLECT_VISIT2_MEMBER, v, MEMBERS ) \
} \
template<typename Visitor>\
static inline void visit( type& t, Visitor&& v ) { \
    BOOST_PP_SEQ_FOR_EACH( BetterChainLIB_REFLECT_VISIT2_BASE, v, INHERITS ) \
    BOOST_PP_SEQ_FOR_EACH( BetterChainLIB_REFLECT_VISIT2_MEMBER, v, MEMBERS ) \
}

#define BetterChainLIB_REFLECT_DERIVED_IMPL_EXT( TYPE, INHERITS, MEMBERS ) \
template<typename Visitor>\
void betterchain::reflector<TYPE>::visit( Visitor&& v ) { \
    BOOST_PP_SEQ_FOR_EACH( BetterChainLIB_REFLECT_VISIT_BASE, v, INHERITS ) \
    BOOST_PP_SEQ_FOR_EACH( BetterChainLIB_REFLECT_VISIT_MEMBER, v, MEMBERS ) \
}


/**
 *  @def BetterChainLIB_REFLECT(TYPE,MEMBERS)
 *  @brief Specializes betterchain::reflector for TYPE
 *
 *  @param MEMBERS - a sequence of member names.  (field1)(field2)(field3)
 *
 *  @see BetterChainLIB_REFLECT_DERIVED
 */
#define BetterChainLIB_REFLECT( TYPE, MEMBERS ) \
    BetterChainLIB_REFLECT_DERIVED( TYPE, BOOST_PP_SEQ_NIL, MEMBERS )

#define BetterChainLIB_REFLECT_TEMPLATE( TEMPLATE_ARGS, TYPE, MEMBERS ) \
    BetterChainLIB_REFLECT_DERIVED_TEMPLATE( TEMPLATE_ARGS, TYPE, BOOST_PP_SEQ_NIL, MEMBERS )

#define BetterChainLIB_REFLECT_EMPTY( TYPE ) \
    BetterChainLIB_REFLECT_DERIVED( TYPE, BOOST_PP_SEQ_NIL, BOOST_PP_SEQ_NIL )


#define BetterChainLIB_REFLECT_FWD( TYPE ) \
namespace betterchain { \
  template<> struct reflector<TYPE> {\
       typedef TYPE type; \
       typedef betterchain::true_type is_reflected; \
       enum  member_count_enum {  \
         local_member_count = BOOST_PP_SEQ_SIZE(MEMBERS), \
         total_member_count = local_member_count BOOST_PP_SEQ_FOR_EACH( BetterChainLIB_REFLECT_BASE_MEMBER_COUNT, +, INHERITS )\
       }; \
       template<typename Visitor> static void visit( Visitor&& v ); \
       template<typename Visitor> static void visit( const type& t, Visitor&& v ); \
       template<typename Visitor> static void visit( type& t, Visitor&& v ); \
  }; }


#define BetterChainLIB_REFLECT_DERIVED_IMPL( TYPE, MEMBERS ) \
    BetterChainLIB_REFLECT_IMPL_DERIVED_EXT( TYPE, BOOST_PP_SEQ_NIL, MEMBERS )

#define BetterChainLIB_REFLECT_IMPL( TYPE, MEMBERS ) \
    BetterChainLIB_REFLECT_DERIVED_IMPL_EXT( TYPE, BOOST_PP_SEQ_NIL, MEMBERS )



/**
 *  @def BetterChainLIB_REFLECT_DERIVED(TYPE,INHERITS,MEMBERS)
 *
 *  @brief Specializes betterchain::reflector for TYPE where
 *         type inherits other reflected classes
 *
 *  @param INHERITS - a sequence of base class names (basea)(baseb)(basec)
 *  @param MEMBERS - a sequence of member names.  (field1)(field2)(field3)
 */
#define BetterChainLIB_REFLECT_DERIVED( TYPE, INHERITS, MEMBERS ) \
namespace betterchain {  \
template<> struct reflector<TYPE> {\
    typedef TYPE type; \
    typedef betterchain::true_type  is_reflected; \
    typedef betterchain::false_type is_enum; \
    enum  member_count_enum {  \
      local_member_count = 0  BOOST_PP_SEQ_FOR_EACH( BetterChainLIB_REFLECT_MEMBER_COUNT, +, MEMBERS ),\
      total_member_count = local_member_count BOOST_PP_SEQ_FOR_EACH( BetterChainLIB_REFLECT_BASE_MEMBER_COUNT, +, INHERITS )\
    }; \
    BetterChainLIB_REFLECT_DERIVED_IMPL_INLINE( TYPE, INHERITS, MEMBERS ) \
}; }
#define BetterChainLIB_REFLECT_DERIVED_TEMPLATE( TEMPLATE_ARGS, TYPE, INHERITS, MEMBERS ) \
namespace betterchain {  \
template<BOOST_PP_SEQ_ENUM(TEMPLATE_ARGS)> struct reflector<TYPE> {\
    typedef TYPE type; \
    typedef betterchain::true_type  is_defined; \
    typedef betterchain::false_type is_enum; \
    enum  member_count_enum {  \
      local_member_count = 0  BOOST_PP_SEQ_FOR_EACH( BetterChainLIB_REFLECT_MEMBER_COUNT, +, MEMBERS ),\
      total_member_count = local_member_count BOOST_PP_SEQ_FOR_EACH( BetterChainLIB_REFLECT_BASE_MEMBER_COUNT, +, INHERITS )\
    }; \
    BetterChainLIB_REFLECT_DERIVED_IMPL_INLINE( TYPE, INHERITS, MEMBERS ) \
}; }
