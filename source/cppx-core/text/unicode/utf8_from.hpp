#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <cppx-core/meta-template/Enable_if_.hpp>           // cppx::Enable_if_
#include <cppx-core/meta-type/type-traits.hpp>              // cppx::(is_same_type_)
#include <cppx-core/text/unicode/n_utf8_bytes_for.hpp>      // cppx::n_utf8_bytes_for
#include <cppx-core/text/unicode/To_bytes.hpp>               // cppx::To_bytes

namespace cppx
{
    CPPX_USE_STD( basic_string, basic_string_view, iterator_traits, move, next, string, string_view );

    template< class Char >
    inline auto utf8_from_string_view( const basic_string_view<Char>& ws )
        -> string
    {
        if( is_empty( ws ) ) { return ""; }

        // Assume UTF-8 encoding for byte string, UTF-16 (or UTF-32) for larger units.
        if constexpr( sizeof( Char ) == 1 )
        {
            return string( ws.begin(), ws.end() );
        }
        else
        {
            string result( n_utf8_bytes_for( ws ), '\0' );
            To_bytes().utf8_from_codes( CPPX_ITEMS( ws ), result.begin() );
            return result;
        }
    }

    template< class Char >
    inline auto utf8_from( const P_<const Char> s )
        -> string
    { return utf8_from_string_view<Char>( s ); }

    template< class Char >
    inline auto utf8_from( const basic_string<Char>& s )
        -> string
    { return utf8_from_string_view<Char>( s ); }

    inline auto utf8_from( string s )
        -> string
    { return move( s ); }

    template< class Char >
    inline auto utf8_from( const basic_string_view<Char>& s )
        -> string
    { return utf8_from_string_view<Char>( s ); }

}  // namespace cppx
