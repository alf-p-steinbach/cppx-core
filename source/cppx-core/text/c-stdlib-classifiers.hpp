#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <cppx-core-language/types/system-dependent/Byte.hpp>   // cppx::Byte
#include <cppx-core-language/types/Truth.hpp>                   // cppx::Truth
#include <cppx-core-language/tmp/type-checkers.hpp>             // cppx::is_integral_
#include <cppx-core-language/tmp/type-modifiers.hpp>            // cppx::As_unsigned_

#include <c/ctype.hpp>          // isspace, iswspace

namespace cppx::cstdlib
{
    // Depends on the C level locale via the `setlocale` function.

    template< class Code >
    inline auto is_byte_space( const Code ch )
        -> Truth
    {
        static_assert( is_integral_<Code> );
        if constexpr( sizeof( Code ) > 1 ) {
            if( As_unsigned_<Code>( ch ) > max_byte ) {
                return false;
            }
        }
        return !!::isspace( Byte( ch ) );
    }

    template< class Code >
    inline auto is_wide_space( const Code ch )
        -> Truth
    {
        static_assert( is_integral_<Code> );
        if constexpr( sizeof( Code ) > sizeof( wchar_t ) ) {
            if( As_unsigned_<Code>( ch ) > wchar_t( -1 ) ) {
                return false;
            }
        }
        return !!::iswspace( wchar_t( ch ) );
    }

    // TODO: is_punctuation

}  // namespace cppx::cstdlib
