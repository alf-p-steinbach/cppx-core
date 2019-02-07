#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <iterator>         // std::(begin, end)

#ifndef CPPX_NO_DOLLARS
#   define  $items CPPX_ITEMS
#endif

// Careful, don't call with lvalue expression that has side effects.

#define CPPX_ITEMS( c ) \
    std::begin( cppx::lvalue_ref_to( c ) ), std::end( c )

namespace cppx
{
    template< class Type >
    inline auto lvalue_ref_to( Type& c )
        -> Type&
    { return c; }

}  // namespace cppx
