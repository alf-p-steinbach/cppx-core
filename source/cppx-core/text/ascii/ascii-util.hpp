#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <cppx-core/language/types/byte-types.hpp>              // cppx::Byte
#include <cppx-core/language/types/type-production.hpp>         // cppx::(R_, P_, Unsigned_)
#include <cppx-core/meta-template/enable_if_.hpp>               // cppx::Enable_if_
#include <cppx-core/meta-type/type-traits.hpp>                  // cppx::is_cpp03_char_type_
#include <cppx-core/syntax/macro-use.hpp>                       // CPPX_USE_STD
#include <cppx-core/text/ascii/ascii-character-names.hpp>

#include <c/string.hpp>          // strlen
#include <c/ctype.hpp>           // isspace
#include <string>                // std::(string, wstring)
#include <string_view>           // std::string_view
#include <type_traits>           // std::make_unsigned
#include <utility>               // std::(Enable_if_)

namespace cppx
{
    CPPX_USE_STD(
        basic_string, basic_string_view, make_unsigned_t, string, string_view,
        wstring, wstring_view
        );

    //---------------------------------------- Is-ASCII checking:
    namespace ascii_range
    {
        template< class Number >
        inline auto contains( const Number v )
            -> bool
        { return (static_cast<Unsigned_<Number>>( v ) <= ascii::last_char); }

        template< class It >
        inline auto contains_all( const It start, const It beyond )
            -> bool
        {
            for( It it = start; it != beyond; ++it )
            {
                if( not ascii_range::contains( *it ) ) { return false; }
            }
            return true;
        }
    }  // namespace ascii_range

    template< class Integer >
    inline auto is_ascii( const Integer ch )
        -> bool
    { return ascii_range::contains( ch ); }

    template< class Char, class = Enable_if_<is_a_cpp03_char_type_<Char>>>
    inline auto is_all_ascii( const basic_string_view<Char>& sv )
        -> bool
    { return ascii_range::contains_all( sv.begin(), sv.end() ); }

    template< class Char, class = Enable_if_<is_a_cpp03_char_type_<Char>>>
    inline auto is_all_ascii( const P_<const Char> s )
        -> bool
    { return is_all_ascii( basic_string_view<Char>( s ) ); }

    template< class Char, class = Enable_if_<is_a_cpp03_char_type_<Char>>>
    inline auto is_all_ascii( const basic_string<Char>& s )
        -> bool
    { return is_all_ascii( basic_string_view<Char>( s ) ); }


    //---------------------------------------- wide_from_ascii:

    template< class Char, class = Enable_if_<is_a_cpp03_char_type_<Char>>>
    inline auto wide_from_ascii( const basic_string_view<Char>& v )
        -> wstring
    { return wstring( v.begin(), v.end() ); }

    template< class Char, class = Enable_if_<is_a_cpp03_char_type_<Char>>>
    inline auto wide_from_ascii( const P_<const Char> s )
        -> wstring
    { return wide_from_ascii( basic_string_view<Char>( s ) ); }

    template< class Char, class = Enable_if_<is_a_cpp03_char_type_<Char>>>
    inline auto wide_from_ascii( const basic_string<Char>& s )
        -> wstring
    { return wide_from_ascii( basic_string_view<Char>( s ) ); }


    //----------------------------------------  Whitespace checking:

    // Depends on the C level locale (setlocale)
    namespace cstdlib
    {
        template<
            class Char,
            class = Enable_if_< is_a_cpp03_char_type_<Char> or is_a_char_variant_type_<Char> >
            >
        inline auto is_space( const Char ch )
            -> bool
        { return !!::isspace( static_cast<Byte>( ch ) ); }

        template<>
        inline auto is_space<wchar_t>( const wchar_t ch )
            -> bool
        { return !!::iswspace( ch ); }
    }  // namespace cstdlib

    // Is independent of locale
    template< class Char, class = Enable_if_<is_a_cpp03_char_type_<Char>>>
    inline auto is_ascii_whitespace( const Char ch )
        -> bool
    { return is_ascii( ch ) and cstdlib::is_space( ch ); }

    template< class Char, class = Enable_if_<is_a_cpp03_char_type_<Char>>>
    inline auto is_all_ascii_whitespace( const basic_string_view<Char>& sv )
        -> bool
    {
        for( const Char ch : sv )
        {
            if( not is_ascii_whitespace( ch ) )
            {
                return false;
            }
        }
        return true;
    }

    template< class Char, class = Enable_if_<is_a_cpp03_char_type_<Char>>>
    inline auto is_all_ascii_whitespace( const basic_string<Char>& s )
        -> bool
    { return is_all_ascii_whitespace( basic_string_view<Char>( s ) ); }

    template< class Char, class = Enable_if_<is_a_cpp03_char_type_<Char>>>
    inline auto is_all_ascii_whitespace( const P_<const Char> s )
        -> bool
    { return is_all_ascii_whitespace( basic_string_view<Char>( s ) ); }

    //----------------------------------------  Uppercase/lowercase:

    template< class Char, class = Enable_if_<is_a_cpp03_char_type_<Char>>>
    inline auto is_ascii_lowercase( const Char ch )
        -> bool
    { return 'a' <= ch and ch <= 'z'; }

    template< class Char, class = Enable_if_<is_a_cpp03_char_type_<Char>>>
    inline auto is_ascii_uppercase( const Char ch )
        -> bool
    { return 'A' <= ch and ch <= 'Z'; }

    template< class Char, class = Enable_if_<is_a_cpp03_char_type_<Char>>>
    inline auto ascii_to_lowercase( const Char ch )
        -> Char
    { return (is_ascii_uppercase( ch )? Char( ch - 'A' + 'a' ) : ch); }

    template< class Char, class = Enable_if_<is_a_cpp03_char_type_<Char>>>
    inline auto ascii_to_uppercase( const Char ch )
        -> Char
    { return (is_ascii_lowercase( ch )? Char( ch - 'a' + 'A' ) : ch); }

    template< class Char, class = Enable_if_<is_a_cpp03_char_type_<Char>>>
    inline auto ascii_to_lowercase( const basic_string_view<Char>& v )
        -> basic_string<Char>
    {
        basic_string<Char> result;
        result.reserve( v.size() );
        for( const Char ch : v )
        {
            result += ascii_to_lowercase( ch );
        }
        return result;
    }

    template< class Char, class = Enable_if_<is_a_cpp03_char_type_<Char>>>
    inline auto ascii_to_uppercase( const basic_string_view<Char>& v )
        -> basic_string<Char>
    {
        basic_string<Char> result;
        result.reserve( v.size() );
        for( const Char ch : v )
        {
            result += ascii_to_uppercase( ch );
        }
        return result;
    }

    template< class Char, class = Enable_if_<is_a_cpp03_char_type_<Char>>>
    inline auto ascii_to_lowercase( const P_<const Char> s )
        -> basic_string<Char>
    { return ascii_to_lowercase( basic_string_view<Char>( s ) ); }

    template< class Char, class = Enable_if_<is_a_cpp03_char_type_<Char>>>
    inline auto ascii_to_uppercase( const P_<const Char> s )
        -> basic_string<Char>
    { return ascii_to_uppercase( basic_string_view<Char>( s ) ); }

    template< class Char, class = Enable_if_<is_a_cpp03_char_type_<Char>>>
    inline auto ascii_to_lowercase( const basic_string<Char>& s )
        -> basic_string<Char>
    { return ascii_to_lowercase( basic_string_view<Char>( s ) ); }

    template< class Char, class = Enable_if_<is_a_cpp03_char_type_<Char>>>
    inline auto ascii_to_uppercase( const basic_string<Char>& s )
        -> basic_string<Char>
    { return ascii_to_uppercase( basic_string_view<Char>( s ) ); }


    //----------------------------------------  Misc:

    inline auto ascii_quoted( const string_view& sv )
        -> string
    {
        string s;
        s = "\"";
        s += sv;
        s += "\"";
        return s;
    }

    inline auto ascii_quoted( const char ch )
        -> string
    { return ascii_quoted( string_view( &ch, 1 ) ); }

}  // namespace cppx
