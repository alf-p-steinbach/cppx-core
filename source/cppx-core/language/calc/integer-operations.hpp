#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/language/syntax/macro-use.hpp>
//#include <cppx-core/language/tmp/basic-type-traits.hpp>         // cppx::is_unsigned_

#include <c/limits.hpp>     // INT_MAX
#include <c/stdint.hpp>     // ::(uintXX_t)
#include <c/stdlib.hpp>     // ::(div_t, div)
#include <type_traits>      // std::is_unsigned_v

// Using explicit `using` declarations instead of `inline` namespace to avoid ambiguity
// elsewhere for the nested namespace name `impl`.
namespace cppx::math
{
    template< class Int = int >
    inline auto is_even( const Int x )
        -> bool
    { return x % 2 == 0; }

    template< class Int = int >
    inline auto is_odd( const Int x )
        -> bool
    { return x % 2 == 1; }

    template< class Int = int >
    inline auto idiv( const Int a, const Int b ) noexcept
        -> Int
    {
        const div_t r = ::div( a, b );
        return (r.quot < 0 and r.rem != 0? r.quot - 1 : r.quot);
    }

    inline auto imod( const int a, const int b ) noexcept
        -> int
    { return a - b*idiv( a, b ); }

    template< class Int = int >
    inline auto isquared( const Int x )
        -> Int
    { return x*x; }

    template< class Int = int >
    inline auto icubed( const Int x )
        -> Int
    { return x*x*x; }
}  // namespace cppx::math

namespace cppx
{
    CPPX_USE_FROM_NAMESPACE( math,
        is_even, is_odd, idiv, imod, isquared, icubed
        );
}  // namespace cppx
