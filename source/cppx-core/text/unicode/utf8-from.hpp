#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <cppx-core-language/tmp/Enable_if_.hpp>            // cppx::Enable_if_
#include <cppx-core-language/tmp/type-checkers.hpp>         // cppx::(is_a_byte_char_type_)
#include <cppx-core/text/unicode/utf8-Generator.hpp>        // cppx::utf8::Generator
#include <cppx-core/text/unicode/utf8-n_bytes_for.hpp>      // cppx::utf8::n_bytes_for

namespace cppx::utf8
{
    CPPX_USE_STD( basic_string, basic_string_view, iterator_traits, move, next, string, string_view );

    template< class Char >
    inline auto from_string_view( const basic_string_view<Char>& ws )
        -> string
    {
        if( is_empty( ws ) ) { return ""; }

        // Assume UTF-8 encoding for byte string, UTF-16 (or UTF-32) for larger units.
        if constexpr( is_a_byte_char_type_<Char> )
        {
            return string( ws.begin(), ws.end() );
        }
        else
        {
            string result( n_bytes_for( ws ), '\0' );
            Generator().utf8_from_codes( CPPX_ITEMS_OF( ws ), result.begin() );
            return result;
        }
    }

    template< class Char >
    inline auto from( const P_<const Char> s )
        -> string
    { return from_string_view<Char>( s ); }

    template< class Char >
    inline auto from( const basic_string<Char>& s )
        -> string
    { return from_string_view<Char>( s ); }

    inline auto from( string s )
        -> string
    { return move( s ); }

    template< class Char >
    inline auto from( const basic_string_view<Char>& s )
        -> string
    { return from_string_view<Char>( s ); }

}  // namespace cppx::utf8
