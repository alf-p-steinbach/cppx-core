#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core-language/syntax/macro-use.hpp>              // CPPX_USE_STD
#include <cppx-core-language/syntax/type-builders.hpp>          // cppx::Raw_array_of_
#include <cppx-core-language/system-dependent/size-types.hpp>   // cppx::Size
#include <cppx-core-language/types/Truth.hpp>                   // cppx::Truth

#include <algorithm>            // std::(binary_search, find)
#include <bitset>               // std::bitset
#include <initializer_list>     // std::initializer_list
#include <iterator>             // std::(begin, end)
#include <string_view>          // std::string_view

namespace cppx
{
    CPPX_USE_STD(
        basic_string_view, begin, binary_search, bitset, end, find, initializer_list
        );

    template< class Char >
    inline auto is_in( const basic_string_view<Char>& sv, const Char ch ) noexcept
        -> Truth
    { return 0 <= static_cast<Size>( sv.find( ch ) ); }

    template< class Item, class Value >
    inline auto is_in( const initializer_list<Item>& items, const Value& v ) noexcept
        -> Truth
    {
        for( auto& item : items )
        {
            if( item == v ) { return true; }
        }
        return false;
    }

    template< size_t n >
    inline auto is_in( const bitset<n>& bits, const int i ) noexcept
        -> Truth
    { return !!bits[i]; }


    //-------------------------------------------------------- Arrays

    template< class It, class Arg >
    auto is_in_span( const It begin, const It end, const Arg& v )
        -> Truth
    { return find( begin, end, v ) != end; }

    template< class Key, Size n, class Arg >
    auto is_in( Raw_array_of_<n, const Key>& a, const Arg& v )
        -> Truth
    { return is_in_range( begin( a ), end( a ), v ); }

    template< class It, class Arg >
    auto is_in_sorted_span( const It begin, const It end, const Arg& v )
        -> Truth
    { return binary_search( begin, end, v ); }

    template< class Key, Size n, class Arg >
    auto is_in_sorted( Raw_array_of_<n, const Key>& a, const Arg& v )
        -> Truth
    { return is_in_sorted_range( begin( a ), end( a ), v ); }

}  // namespace cppx
