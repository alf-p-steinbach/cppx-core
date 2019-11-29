#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <cppx-core-language/ascii/ascii-character-util.hpp>        // cppx::*
#include <cppx-core-language/syntax/general-string-builders.hpp>    // cppx::spaces
#include <cppx-core/collections/Span_util.hpp>                      // cppx::(Span_, all_but_first_of)
#include <cppx-core/collections/is_empty.hpp>                       // cppx::is_empty
#include <cppx-core-language/syntax/type-builders.hpp>              // cppx::P_
#include <cppx-core/text/data/Symbol_strings.hpp>                   // cppx::best_effort::*
#include <cppx-core/text/pointers-from-string_view.hpp>             // cppx::(p_first_of, p_beyond_of)
#include <cppx-core/text/unicode/utf8-iteration.hpp>                // cppx::utf8::(n_code_points_in, *)

#include <iterator>             // std::next
#include <utility>              // std::move

namespace cppx
{
    CPPX_USE_STD( basic_string_view, move, next, string, string_view );

    //----------------------------------------  Adjustment (mostly for console output):
    //
    // This is not at all perfect, especially wrt. Unicode character modifiers, but the
    // simpleton approach of counting code points for character positions is usually Good
    // Enough™, and it plays nicely with console windows that do not compose characters.

    inline auto at_left( const int width, const string_view& s )
        -> string
    { return string( s ) + spaces( width - int( utf8::n_code_points_in( s ) ) ); }

    inline auto at_left( const int width, const char ch )
        -> string
    { return ch + spaces( width - 1 ); }

    inline auto at_right( const int width, const string_view& s )
        -> string
    { return spaces( width - int( utf8::n_code_points_in( s ) ) ) + string( s ); }

    inline auto at_right( const int width, const char ch )
        -> string
    { return spaces( width - 1 ) + ch; }

    //----------------------------------------  Misc:

    // Uses simple straight ASCII quotes if CPPX_ASCII_PLEASE is defined.
    inline auto quoted( const string_view& sv )
        -> string
    {
        string s;
        s = cppx::best_effort::left_quote_str;
        s += sv;
        s += cppx::best_effort::right_quote_str;
        return s;
    }

    inline auto quoted( const char ch )
        -> string
    { return quoted( string_view( &ch, 1 ) ); }

    inline auto trimmed( const string_view& sv )
        -> string_view
    {
        if( is_empty( sv ) )
        {
            return sv;
        }
        P_<const char> p_first      = p_first_of( sv );
        P_<const char> p_beyond     = p_beyond_of( sv );
        while( p_first != p_beyond and ascii::is_whitespace( *p_first ) )
        {
            ++p_first;
        }
        while( p_beyond != p_first and ascii::is_whitespace( *p_beyond ) )
        {
            --p_beyond;
        }
        return string_view( p_first, p_beyond - p_first );
    }

    inline auto trimmed( const string& s )
        -> string
    { return string( trimmed( string_view( s ) ) ); }

    inline auto trimmed( string&& s )
        -> string
    {
        const string_view t = trimmed( string_view( s ) );
        if( t.length() == s.length() )
        {
            return move( s );
        }
        else
        {
            return string( t );
        }
    }

    inline auto split() -> void; // TODO

}  // namespace cppx
