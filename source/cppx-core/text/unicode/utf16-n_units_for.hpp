#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/iterators/Count_iterator_.hpp>
#include <cppx-core/text/unicode/utf16-Generator.hpp>

namespace cppx::utf16
{
    template< class Char >
    inline auto n_units_for( const basic_string_view<Char>& sv ) noexcept
        -> Size
    {
        //impl::Count_iterator it;
        //it = utf16::Generator().utf8_from_codes( CPPX_ITEMS( sv ), it );
        //return it.count();
        return 0;       // TODO:
    }

    //// Optimization.
    //inline auto utf8::n_bytes_for( const basic_string_view<char>& sv ) noexcept
    //    -> Size
    //{ return sv.size(); }

    //// Callability.
    //template< class Char >
    //inline auto utf8::n_bytes_for( const P_<Char> s ) noexcept
    //    -> Size
    //{ return utf8::n_bytes_for( basic_string_view<Char>( s ) ); }

    //template< class Char >
    //inline auto utf8::n_bytes_for( const basic_string<Char>& s ) noexcept
    //    -> Size
    //{ return utf8::n_bytes_for( basic_string_view<Char>( s ) ); }
}  // namespace cppx::utf16
