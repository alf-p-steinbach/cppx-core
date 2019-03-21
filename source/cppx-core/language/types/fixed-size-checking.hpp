#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/language/syntax/macro-use.hpp>              // CPPX_USE_STD
#include <cppx-core/language/syntax/type-assemblers.hpp>        // cppx::(Raw_array_of_, P_)
#include <cppx-core/language/types/signed-size-types.hpp>       // cppx::Size

#include <array>            // std::array
#include <bitset>           // std::bitset
#include <iterator>         // std::(begin, end, size)

namespace cppx
{
    CPPX_USE_STD( array, bitset );

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
