#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <cppx-core/data/Symbol_strings.hpp>                // cppx::best_effort::*
#include <cppx-core/collections/Span_.hpp>                  // cppx::(Span_, all_but_first_of)
#include <cppx-core/collections/is_empty.hpp>               // cppx::is_empty
#include <cppx-core/language/syntax/type-assemblers.hpp>    // cppx::P_
#include <cppx-core/text/ascii/ascii-util.hpp>              // cppx::*
#include <cppx-core/text/pointers-from-string_view.hpp>     // cppx::(p_first_of, p_beyond_of)
#include <cppx-core/text/unicode/utf8-iteration.hpp>        // cppx::utf8::(n_code_points_in, *)

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

    inline auto spaces( const int n )
        -> string
    { return (n <= 0? "" : string( n, ' ')); }

    inline namespace string_repeat
    {
        inline auto repeated( const int n, const string_view& s )
            -> string
        {
            if( n <= 0 ) { return ""; }

            string result;
            result.reserve( n*s.length() );
            for( int i = 1; i <= n; ++i )
            {
                result += s;
            }
            return result;
        }

        inline auto operator*( const int n, const string_view& s )
            -> string
        { return repeated( n, s ); }
    }

    inline auto left( const string_view& s, const int width )
        -> string
    { return string( s ) + spaces( width - utf8::n_code_points_in( s ) ); }

    inline auto right( const string_view& s, const int width )
        -> string
    { return spaces( width - utf8::n_code_points_in( s ) ) + string( s ); }


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

    template< class Iterator >
    inline auto joined(
        const Span_<Iterator>       range,
        const string&               separator = " "
        ) -> string
    {
        if( is_empty( range ) ) { return ""; }

        string result = range.front();
        for( const auto& item : all_but_first_of( range ) )
        {
            result += separator;
            result += item;
        }
        return result;
    }

}  // namespace cppx
