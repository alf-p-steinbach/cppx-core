#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <cppx-core-language/tmp/Enable_if_.hpp>            // cppx::Enable_if_
#include <cppx-core-language/tmp/type-checkers.hpp>         // cppx::(is_same_type_)
#include <cppx-core/text/unicode/utf16-Generator.hpp>       // cppx::utf16::Generator
#include <cppx-core/text/unicode/utf16-n_units_for.hpp>     // cppx::utf16::n_units_for

namespace cppx::utf16
{
    CPPX_USE_STD(
        basic_string, basic_string_view, string, string_view, u16string, wstring,
        iterator_traits, move, next
        );

    template<
        class Char,
        class Result_char = char16_t,
        class = Enable_if_< magnitude_bits_per_<Result_char> >= 16 >
        >
    inline auto from_string_view( const basic_string_view<Char>& sv )
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
            basic_string<Result_char> result( n_units_for( sv ), Result_char() );
            Generator().utf16_from_bytes( CPPX_ITEMS_OF( sv ), result.begin() );
            return result;
        }
    }

    template< class Char >
    inline auto from( const P_<const Char> s )
        -> u16string
    { return from_string_view<Char>( s ); }

    template< class Char >
    inline auto from( const basic_string<Char>& s )
        -> u16string
    { return from_string_view<Char>( s ); }

    inline auto from( u16string s )
        -> u16string
    { return move( s ); }

    template< class Char >
    inline auto from( const basic_string_view<Char>& s )
        -> u16string
    { return from_string_view<Char>( s ); }

    template< class Char >
    inline auto wide_from( const P_<const Char> s )
        -> wstring
    { return from_string_view<Char, wchar_t>( s ); }

    template< class Char >
    inline auto wide_from( const basic_string<Char>& s )
        -> wstring
    { return from_string_view<Char, wchar_t>( s ); }

    //inline auto wide_from( wstring s )
    //    -> wstring
    //{ return move( s ); }

    template< class Char >
    inline auto wide_from( const basic_string_view<Char>& s )
        -> wstring
    { return from_string_view<Char, wchar_t>( s ); }
}  // namespace cppx::utf16
