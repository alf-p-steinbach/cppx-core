#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <cppx-core-language/syntax/macro-items_of.hpp>         // CPPX_ITEMS_OF
#include <cppx-core-language/syntax/macro-use.hpp>              // CPPX_USE_STD
#include <cppx-core-language/syntax/Sequence_.hpp>              // cppx::Sequence_
#include <cppx-core-language/system/Byte.hpp>                   // cppx::Byte
#include <cppx-core-language/types/Truth.hpp>                   // cppx::Truth
#include <cppx-core-language/syntax/type-builders.hpp>          // cppx::(R_, P_)
#include <cppx-core-language/tmp/type-mutators.hpp>             // cppx::(Unsigned_)
#include <cppx-core-language/tmp/Enable_if_.hpp>                // cppx::Enable_if_
#include <cppx-core/meta-type/type-traits.hpp>                  // cppx::is_cpp03_char_type_
#include <cppx-core/text/data/ascii-character-names.hpp>        // cppx::ascii::/names/

#include <c/string.hpp>         // strlen
#include <c/ctype.hpp>          // isspace
#include <string>               // std::(string, wstring)
#include <string_view>          // std::string_view
#include <functional>           // std::invoke

namespace cppx::cstdlib
{
    // Depends on the C level locale (setlocale)

    template<
        class Char,
        class = Enable_if_< is_a_cpp03_char_type_<Char> or is_a_char_variant_type_<Char> >
        >
    inline auto is_space( const Char ch )
        -> Truth
    { return !!::isspace( static_cast<Byte>( ch ) ); }

    template<>
    inline auto is_space<wchar_t>( const wchar_t ch )
        -> Truth
    { return !!::iswspace( ch ); }

}  // namespace cppx::cstdlib

namespace cppx::ascii
{
    CPPX_USE_STD(
        basic_string, basic_string_view, invoke, string, string_view, wstring, wstring_view
        );

    //---------------------------------------- Is-ASCII checking:

    template< class Integer >
    inline auto contains( const Integer v )
        -> Truth
    { return (static_cast<Unsigned_<Integer>>( v ) <= ascii::last_char); }

    template< class It >
    inline auto contains_all_of( const It start, const It beyond )
        -> Truth
    {
        for( It it = start; it != beyond; ++it )
        {
            if( not contains( *it ) ) { return false; }
        }
        return true;
    }

    template< class Char, class = Enable_if_<is_a_cpp03_char_type_<Char>>>
    inline auto contains_all_of( const basic_string_view<Char>& sv )
        -> Truth
    { return contains_all_of( CPPX_ITEMS_OF( sv ) ); }

    template< class Char, class = Enable_if_<is_a_cpp03_char_type_<Char>>>
    inline auto contains_all_of( const P_<const Char> s )
        -> Truth
    { return contains_all_of( basic_string_view<Char>( s ) ); }

    template< class Char, class = Enable_if_<is_a_cpp03_char_type_<Char>>>
    inline auto contains_all_of( const basic_string<Char>& s )
        -> Truth
    { return contains_all_of( basic_string_view<Char>( s ) ); }


    //---------------------------------------- ascii::to_wide:

    template< class Char, class = Enable_if_<is_a_cpp03_char_type_<Char>>>
    inline auto to_wide( const basic_string_view<Char>& v )
        -> wstring
    { return wstring( v.begin(), v.end() ); }

    template< class Char, class = Enable_if_<is_a_cpp03_char_type_<Char>>>
    inline auto to_wide( const P_<const Char> s )
        -> wstring
    { return to_wide( basic_string_view<Char>( s ) ); }

    template< class Char, class = Enable_if_<is_a_cpp03_char_type_<Char>>>
    inline auto to_wide( const basic_string<Char>& s )
        -> wstring
    { return to_wide( basic_string_view<Char>( s ) ); }


    //----------------------------------------  Whitespace checking:

    // Is independent of locale
    template< class Char, class = Enable_if_<is_a_cpp03_char_type_<Char>>>
    inline auto is_whitespace( const Char ch )
        -> Truth
    { return ascii::contains( ch ) and cstdlib::is_space( ch ); }

    template< class Char, class = Enable_if_<is_a_cpp03_char_type_<Char>>>
    inline auto is_all_whitespace( const basic_string_view<Char>& sv )
        -> Truth
    {
        for( const Char ch : sv )
        {
            if( not is_whitespace( ch ) )
            {
                return false;
            }
        }
        return true;
    }

    template< class Char, class = Enable_if_<is_a_cpp03_char_type_<Char>>>
    inline auto is_all_whitespace( const basic_string<Char>& s )
        -> Truth
    { return is_all_whitespace( basic_string_view<Char>( s ) ); }

    template< class Char, class = Enable_if_<is_a_cpp03_char_type_<Char>>>
    inline auto is_all_whitespace( const P_<const Char> s )
        -> Truth
    { return is_all_whitespace( basic_string_view<Char>( s ) ); }

    inline auto whitespace_characters()
        -> const string&
    {
        static const string the_chars = invoke([]() -> string
        {
            string result;
            for( const int code: Sequence( 0, last_char ) )
            {
                if( is_whitespace( char( code ) ) )
                {
                    result += char( code );
                }
            }
            return result;
        } );

        return the_chars;
    }

    //----------------------------------------  Uppercase/lowercase:

    template< class Char, class = Enable_if_<is_a_cpp03_char_type_<Char>>>
    inline auto is_lowercase( const Char ch )
        -> Truth
    { return 'a' <= ch and ch <= 'z'; }

    template< class Char, class = Enable_if_<is_a_cpp03_char_type_<Char>>>
    inline auto is_uppercase( const Char ch )
        -> Truth
    { return 'A' <= ch and ch <= 'Z'; }

    template< class Char, class = Enable_if_<is_a_cpp03_char_type_<Char>>>
    inline auto to_lowercase( const Char ch )
        -> Char
    { return (is_uppercase( ch )? Char( ch - 'A' + 'a' ) : ch); }

    template< class Char, class = Enable_if_<is_a_cpp03_char_type_<Char>>>
    inline auto to_uppercase( const Char ch )
        -> Char
    { return (is_lowercase( ch )? Char( ch - 'a' + 'A' ) : ch); }

    template< class Char, class = Enable_if_<is_a_cpp03_char_type_<Char>>>
    inline auto to_lowercase( const basic_string_view<Char>& v )
        -> basic_string<Char>
    {
        basic_string<Char> result;
        result.reserve( v.size() );
        for( const Char ch : v )
        {
            result += to_lowercase( ch );
        }
        return result;
    }

    template< class Char, class = Enable_if_<is_a_cpp03_char_type_<Char>>>
    inline auto to_uppercase( const basic_string_view<Char>& v )
        -> basic_string<Char>
    {
        basic_string<Char> result;
        result.reserve( v.size() );
        for( const Char ch : v )
        {
            result += to_uppercase( ch );
        }
        return result;
    }

    template< class Char, class = Enable_if_<is_a_cpp03_char_type_<Char>>>
    inline auto to_lowercase( const P_<const Char> s )
        -> basic_string<Char>
    { return to_lowercase( basic_string_view<Char>( s ) ); }

    template< class Char, class = Enable_if_<is_a_cpp03_char_type_<Char>>>
    inline auto to_uppercase( const P_<const Char> s )
        -> basic_string<Char>
    { return to_uppercase( basic_string_view<Char>( s ) ); }

    template< class Char, class = Enable_if_<is_a_cpp03_char_type_<Char>>>
    inline auto to_lowercase( const basic_string<Char>& s )
        -> basic_string<Char>
    { return to_lowercase( basic_string_view<Char>( s ) ); }

    template< class Char, class = Enable_if_<is_a_cpp03_char_type_<Char>>>
    inline auto to_uppercase( const basic_string<Char>& s )
        -> basic_string<Char>
    { return to_uppercase( basic_string_view<Char>( s ) ); }


    //----------------------------------------  Other classification:

    inline auto is_letter( const char ch )
        -> bool
    { return is_lowercase( ch ) or is_uppercase( ch ); }

    inline auto is_digit( const char ch )
        -> bool
    { return '0' <= ch and ch <= '9'; }

    inline auto is_general_id_character( const char ch )
        -> bool
    { return is_letter( ch ) or is_digit( ch ) or ch == '_'; }


    //----------------------------------------  Misc:

    inline auto quoted( const string_view& sv )
        -> string
    {
        string s;
        s = "\"";
        s += sv;
        s += "\"";
        return s;
    }

    inline auto quoted( const char ch )
        -> string
    { return quoted( string_view( &ch, 1 ) ); }

}  // namespace cppx::ascii
