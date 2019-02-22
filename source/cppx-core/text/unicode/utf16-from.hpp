#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <cppx-core/meta-template/Enable_if_.hpp>           // cppx::Enable_if_
#include <cppx-core/meta-type/type-traits.hpp>              // cppx::(is_same_type_)
#include <cppx-core/text/unicode/utf16-Generator.hpp>       // cppx::utf16::Generator
#include <cppx-core/text/unicode/utf16-n_units_for.hpp>     // cppx::utf16::n_units_for

namespace cppx::utf16
{
    CPPX_USE_STD( basic_string, basic_string_view, iterator_traits, move, next, string, string_view );

    template<
        class Char,
        class Result_char = char16_t,
        class = Enable_if_< magnitude_bits_per_<Result_char> >= 16 >
        >
    inline auto utf16_from_string_view( const basic_string_view<Char>& sv )
        -> basic_string<Result_char>
    {
        if( is_empty( sv ) ) { return {}; }

        // Assume UTF-8 encoding for byte string, UTF-16 (or UTF-32) for larger units.
        if constexpr( sizeof( Char ) > 1 )
        {
            static_assert( magnitude_bits_per_<Char> == 16 );   // TODO: Support UTF-32 input.
            return string( sv.begin(), sv.end() );
        }
        else
        {
            string result( utf16::n_units_for( sv ), Result_char() );
            utf16::Generator().utf16_from_bytes( CPPX_ITEMS( sv ), result.begin() );
            return result;
        }
    }

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
