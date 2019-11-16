#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
/// \file
/// \brief Common integer operations:
/// \make_name_ref{cppx,is_even},
/// \make_name_ref{cppx,is_odd},
/// \make_name_ref{cppx,intdiv},
/// \make_name_ref{cppx,intmod},
/// \make_name_ref{cppx,intsquare},
/// \make_name_ref{cppx,intcube},
/// \make_name_ref{cppx,intmin} and
/// \make_name_ref{cppx,intmax}.

#include <cppx-core/language/syntax/macro-use.hpp>              // CPPX_USE_CPPX
#include <cppx-core/language/types/Truth.hpp>                   // cppx::Truth
//#include <cppx-core/language/tmp/basic-type-traits.hpp>         // cppx::is_unsigned_

#include <c/limits.hpp>     // INT_MAX
#include <c/stdint.hpp>     // ::(uintXX_t)
#include <algorithm>        // std::max
#include <type_traits>      // std::(common_type_t, is_integral_v, is_unsigned_v)

namespace cppx
{
    template< class Int >
    inline auto is_even( const Int x )
        -> Truth
    { return x % 2 == 0; }

    template< class Int >
    inline auto is_odd( const Int x )
        -> Truth
    { return x % 2 == 1; }

    template< class Int >
    constexpr inline auto div_down( const Int a, const Int b ) noexcept
        -> Int
    {
        const Int q = a/b;
        return (q < 0 and a % b != 0? q - 1 : q);
    }

    template< class Int >
    constexpr inline auto div_up( const Int a, const Int b ) noexcept
        -> Int
    {
        const Int q = a/b;
        return (q >= 0 and a % b != 0? q + 1 : q);
    }

    inline auto intmod( const int a, const int b ) noexcept
        -> int
    { return a - b*div_down( a, b ); }

    template< class Int = int >
    inline auto intsquare( const Int x )
        -> Int
    { return x*x; }

    template< class Int = int >
    inline auto intcube( const Int x )
        -> Int
    { return x*x*x; }

    template< class... Ints >
    inline auto intmin( const Ints... args )
        -> std::common_type_t<Ints...>
    { 
        static_assert( (... and std::is_integral_v<Ints> ) );
        return std::min( {std::common_type_t<Ints...>( args )...} );
    }

    template< class... Ints >
    inline auto intmax( const Ints... args )
        -> std::common_type_t<Ints...>
    { 
        static_assert( (... and std::is_integral_v<Ints> ) );
        return std::max( {std::common_type_t<Ints...>( args )...} );
    }

    // Is documented in the `all.hpp` header.
    namespace calc
    {
        CPPX_USE_CPPX(
            is_even, is_odd, div_down, div_up, intmod, intsquare, intcube, intmin, intmax
        );
    }  // namespace calc
}  // namespace cppx
