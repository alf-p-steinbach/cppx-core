#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/iterators/Count_iterator_.hpp>
#include <cppx-core/language/syntax/macro-use.hpp>
#include <cppx-core/text/unicode/utf16-Generator.hpp>

namespace cppx::utf16
{
    CPPX_USE_STD( basic_string, basic_string_view );

    template< class Char >
    inline auto n_units_for( const basic_string_view<Char>& sv ) noexcept
        -> Size
    {
        Count_iterator_<char16_t> it;
        it = Generator().utf16_from_bytes( CPPX_ITEMS_OF( sv ), it );
        return it.count();
    }

    //// Optimization.
    //inline auto utf8::n_bytes_for( const basic_string_view<char>& sv ) noexcept
    //    -> Size
    //{ return sv.size(); }

    // Callability.
    template< class Char >
    inline auto n_units_for( const P_<Char> s ) noexcept
        -> Size
    { return n_units_for( basic_string_view<Char>( s ) ); }

    template< class Char >
    inline auto n_units_for( const basic_string<Char>& s ) noexcept
        -> Size
    { return n_units_for( basic_string_view<Char>( s ) ); }

}  // namespace cppx::utf16
