#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <cppx-core/collections/Span_util.hpp>                  // cppx::(Span_, all_but_first_of)
#include <cppx-core/text/data/Symbol_strings.hpp>               // cppx::best_effort::*
#include <cppx-core/text/unicode/utf8-iteration.hpp>            // cppx::utf8::(n_code_points_in, *)

#include <cppx-core-language/syntax/collection-util.hpp>        // cppx::is_empty
#include <cppx-core-language/syntax/string-expressions.hpp>     // cppx::spaces
#include <cppx-core-language/syntax/type-builders.hpp>          // cppx::P_
#include <cppx-core-language/text/ascii-character-util.hpp>     // cppx::*
#include <cppx-core-language/text/string_view-util.hpp>         // cppx::(ptr_to_first_in, ptr_to_beyond)

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

    inline auto at_left_in( const int width, const string_view& s )
        -> string
    { return string( s ) + spaces( width - int( utf8::n_code_points_in( s ) ) ); }

    inline auto at_left_in( const int width, const char ch )
        -> string
    { return ch + spaces( width - 1 ); }

    inline auto at_right_in( const int width, const string_view& s )
        -> string
    { return spaces( width - int( utf8::n_code_points_in( s ) ) ) + string( s ); }

    inline auto at_right_in( const int width, const char ch )
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

    inline auto split() -> void; // TODO

    template< class Iterator >      // TODO: Enable_if_
    inline auto joined(
        const Span_<Iterator>       range,
        const string_view&          separator = " "
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
