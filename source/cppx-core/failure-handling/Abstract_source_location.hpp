#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
//
// This astract class is used by cppx::fail. It can't use things that use cppx::fail.
// Line and character position indexing is 1-based.
//
// A similar class has been proposed for the standard library, see
// <url: https://en.cppreference.com/w/cpp/experimental/source_location>


#include <cppx-core/collections/is_empty.hpp>               // cppx::is_empty
#include <cppx-core-language/syntax/declarations.hpp>       // CPPX_WITH
#include <cppx-core/text/data/Symbol_strings.hpp>           // cppx::best_effort::*

#include <string>                   // std::string
#include <string_view>              // std::string_view

namespace cppx
{
    CPPX_USE_STD( string, string_view, to_string );

    class Abstract_source_location
    {
        static     // Uses simple straight ASCII quotes if CPPX_ASCII_PLEASE is defined.
        inline auto quoted( const string& s )
            -> string
        {
            string result;

            result = best_effort::left_quote_str;
            result += s;
            result += best_effort::right_quote_str;
            return result;
        }

    public:
        virtual auto filename() const               -> string       = 0;    // Empty if none
        virtual auto linenumber() const             -> int          = 0;    // 0 if none.
        virtual auto character_position() const     -> int          = 0;    // 0 if none.
        virtual auto function_name() const          -> string       = 0;    // Empty if none.

        auto function_name_or_unspecified() const
            -> string
        {
            string name = function_name();
            return is_empty( name )? string( "<unspecified function>" ) : move( name );
        }

        auto file_and_line() const
            -> string
        {
            return string()
                + "File " + quoted( filename() ) + " at line " + to_string( linenumber() );
        }

        auto file_line_and_pos() const
            -> string
        {
            const int pos = character_position();
            string s = file_and_line();
            s += " position ";
            if( pos <= 0 )
            {
                s += "<unspecified position>";
            }
            else
            {
                s += to_string( pos );
            }
            return s;
        }

        auto failpoint_spec() const
            -> string
        {
            return file_and_line() + ", in function " + function_name_or_unspecified();
        }

        operator string() const { return failpoint_spec(); }

        virtual ~Abstract_source_location() {}
    };

    inline auto to_string( const Abstract_source_location& loc )
        -> string
    { return loc.operator string(); }

}  // namespace cppx
