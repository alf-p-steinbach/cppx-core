#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/core-language/syntax/macro_use.hpp>             // CPPX_USE_STD
#include <cppx-core/core-language/signed-sizes.hpp>                 // cppx::Size
#include <cppx-core/meta-type/type-builders.hpp>                    // cppx::P_

#include <bitset>           // std::bitset
#include <iterator>         // std::(begin, end, size)
#include <string>           // std::(char_traits)
#include <string_view>      // std::basic_string_view

// Convenience/completeness include:
#include <cppx-core/core-language/bit-level/byte-types.hpp>         // cppx::bits_per_

namespace cppx
{
    CPPX_USE_STD( basic_string, basic_string_view, bitset, char_traits, size );

    // Note: cppx::bits_per_<T> is provided by the "core-language/bit-level/bytes.hpp" header.

    template< class Item, size_t n >
    constexpr auto array_size_of( Item (&)[n] ) noexcept
        -> Size
    { return n; }

    template< class Collection >
    constexpr auto n_items_in( const Collection& c ) noexcept
        -> Size
    { return size( c ); }

    template< size_t n >
    auto n_items_in( const bitset<n>& bits ) noexcept
        -> Size
    { return bits.count(); }

    template< class Char >
    inline auto length_of( const basic_string<Char>& s ) noexcept
        -> Size
    { return s.length(); }

    template< class Char >
    inline auto length_of( const basic_string_view<Char>& sv ) noexcept
        -> Size
    { return sv.length(); }

    template< class Char >
    inline auto length_of( const P_<const Char> s ) noexcept
        -> Size
    { return char_traits<Char>::length( s ); }

}  // namespace cppx
