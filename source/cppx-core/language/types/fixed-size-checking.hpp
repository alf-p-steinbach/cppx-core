#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
/// \file
/// \brief Static size checkers:
/// \make_name_ref{cppx,bits_per_},
/// \make_name_ref{cppx,array_size_of} (raw array, `array` and `bitset`) and
/// \make_name_ref{cppx,length_of_literal} (any kind of string literal).

#include <cppx-core/language/syntax/macro-use.hpp>              // CPPX_USE_STD
#include <cppx-core/language/syntax/type-builders.hpp>          // cppx::(Raw_array_of_, P_)
#include <cppx-core/language/system/size-types.hpp>             // cppx::Size
#include <cppx-core/language/bit-level/bits_per_.hpp>           // cppx::(bits_per_)

#include <array>            // std::array
#include <bitset>           // std::bitset
#include <iterator>         // std::(begin, end, size)

namespace cppx
{
    CPPX_USE_STD( array, bitset );

    using cppx::bits_per_;

    template< class Item, size_t n >
    constexpr auto array_size_of( const Raw_array_of_<n, Item>& ) noexcept
        -> Size
    { return n; }

    template< class Item, size_t n >
    constexpr auto array_size_of( const array<Item, n>& ) noexcept
        -> Size
    { return n; }

    template< class Item, size_t n >
    constexpr auto array_size_of( const bitset<n>& ) noexcept
        -> Size
    { return n; }

    template< class Char, Size n >
    constexpr inline auto length_of_literal( Raw_array_of_<n, const Char>& s ) noexcept
        -> Size
    { return n - 1; }

}  // namespace cppx
