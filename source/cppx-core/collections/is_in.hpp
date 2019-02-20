#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/language/types/signed-size-types.hpp>           // cppx::Size
#include <cppx-core/syntax/macro-use.hpp>                           // CPPX_USE_STD

#include <bitset>               // std::bitset
#include <initializer_list>     // std::initializer_list
#include <iterator>             // std::(begin, end)
#include <string_view>          // std::string_view

namespace cppx
{
    CPPX_USE_STD( basic_string_view, begin, bitset, end, initializer_list );

    template< class Char >
    inline auto is_in( const basic_string_view<Char>& sv, const Char ch ) noexcept
        -> bool
    { return 0 <= static_cast<Size>( sv.find( ch ) ); }

    template< class Item, class Value >
    inline auto is_in( const initializer_list<Item>& items, const Value& v ) noexcept
        -> bool
    {
        for( auto& item : items )
        {
            if( item == v ) { return true; }
        }
        return false;
    }

    template< size_t n >
    inline auto is_in( const bitset<n>& bits, const int i ) noexcept
        -> bool
    { return !!bits[i]; }

}  // namespace cppx
