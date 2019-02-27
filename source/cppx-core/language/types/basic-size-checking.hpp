#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/language/syntax/macro-use.hpp>              // CPPX_USE_STD
#include <cppx-core/language/syntax/type-assemblers.hpp>        // cppx::(Raw_array_of_, P_)
#include <cppx-core/language/types/signed-size-types.hpp>       // cppx::Size

#include <c/string.hpp>     // strlen
#include <iterator>         // std::(begin, end, size)

namespace cppx
{
    template< class Item, size_t n >
    constexpr auto array_size_of( Raw_array_of_<n, const Item>& ) noexcept
        -> Size
    { return n; }

    template< class Char >
    inline auto length_of( const P_<const Char> s ) noexcept
        -> Size
    { return strlen( s ); }

    template< class Char, Size n >
    constexpr inline auto length_of_literal( Raw_array_of_<n, const Char>& s ) noexcept
        -> Size
    { return n - 1; }

}  // namespace cppx
