#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <cppx-core/meta-template/Enable_if_.hpp>           // cppx::Enable_if_
#include <cppx-core/meta-type/type-traits.hpp>              // cppx::(is_same_type_)
#include <cppx-core/text/unicode/utf8-Generator.hpp>        // cppx::utf8::Generator
#include <cppx-core/text/unicode/utf8-n_bytes_for.hpp>      // cppx::utf8::n_bytes_for

namespace cppx::utf16
{
    CPPX_USE_STD( basic_string, basic_string_view, iterator_traits, move, next, string, string_view );

    //template<
    //    class Char,
    //    class Result_char = char16_t,
    //    class = Enable_if_<true>        // TODO:
    //    >
    //inline auto utf16_from_string_view( const basic_string_view<Char>& ws )
    //    -> basic_string<Result_char>
    //{
    //    if( is_empty( ws ) ) { return ""; }

    //    // Assume UTF-8 encoding for byte string, UTF-16 (or UTF-32) for larger units.
    //    if constexpr( sizeof( Char ) == 1 )
    //    {
    //        return string( ws.begin(), ws.end() );
    //    }
    //    else
    //    {
    //        string result( utf8::n_bytes_for( ws ), '\0' );
    //        utf8::Generator().utf8_from_codes( CPPX_ITEMS( ws ), result.begin() );
    //        return result;
    //    }
    //}

#if 0
    template< class Char >
    inline auto utf8::from( const P_<const Char> s )
        -> string
    { return utf8::from_string_view<Char>( s ); }

    template< class Char >
    inline auto utf8::from( const basic_string<Char>& s )
        -> string
    { return utf8::from_string_view<Char>( s ); }

    inline auto utf8::from( string s )
        -> string
    { return move( s ); }

    template< class Char >
    inline auto utf8::from( const basic_string_view<Char>& s )
        -> string
    { return utf8::from_string_view<Char>( s ); }
#endif

}  // namespace cppx::utf16
