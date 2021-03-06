﻿#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core-language/syntax/declarations.hpp>                   // CPPX_USE_STD
#include <cppx-core-language/type-checking/fixed-size-checking.hpp>     // cppx::*
#include <cppx-core-language/syntax/type-builders.hpp>                  // cppx::P_

#include <bitset>           // std::bitset
#include <iterator>         // std::(begin, end, size)
#include <string>           // std::(basic_string, char_traits)
#include <string_view>      // std::basic_string_view

namespace cppx
{
    CPPX_USE_STD( basic_string, basic_string_view, bitset, char_traits, size );

    template< class Collection >
    constexpr auto n_items_of( const Collection& c ) noexcept
        -> Size
    { return size( c ); }

    template< size_t n >
    auto n_items_of( const bitset<n>& bits ) noexcept
        -> Size
    { return bits.count(); }

    template< class Char >
    inline auto length_of( const P_<const Char> s ) noexcept
        -> Size
    { return char_traits<Char>::length( s ); }

    template< class Char >
    inline auto length_of( const basic_string<Char>& s ) noexcept
        -> Size
    { return s.length(); }

    template< class Char >
    inline auto length_of( const basic_string_view<Char>& sv ) noexcept
        -> Size
    { return sv.length(); }

}  // namespace cppx
