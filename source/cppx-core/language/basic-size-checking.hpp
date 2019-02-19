#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/language/syntax/macro-use.hpp>              // CPPX_USE_STD
#include <cppx-core/language/signed-sizes.hpp>                  // cppx::Size
#include <cppx-core/language/bit-level/byte-types.hpp>          // cppx::bits_per_byte
#include <cppx-core/language/type-builders.hpp>                 // cppx::(Array_of_, P_)

#include <c/string.hpp>     // strlen
#include <iterator>         // std::(begin, end, size)
#include <limits>           // std::numeric_limits

namespace cppx
{
    template< class Type >
    constexpr int bits_per_             = sizeof( Type )*bits_per_byte;

    // Note: on modern computers this is generally `bits_per_<Type> - std::is_signed_v<Type>`.
    template< class Type >
    constexpr int magnitude_bits_per_   = std::numeric_limits<Type>::digits;

    template< class Item, size_t n >
    constexpr auto array_size_of( Item (&)[n] ) noexcept
        -> Size
    { return n; }

    template< class Char >
    inline auto length_of( const P_<const Char> s ) noexcept
        -> Size
    { return strlen( s ); }

    template< class Char, Size n >
    constexpr inline auto length_of_literal( const Array_of_<n, const Char>& s ) noexcept
        -> Size
    { return n - 1; }

}  // namespace cppx
