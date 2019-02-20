#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <cppx-core/text/string-util.hpp>       // cppx::(spaces, left)

namespace cppx
{
    CPPX_USE_STD( string, string_view );

    inline auto monospaced_bullet_block(
        const string_view&      s,
        const string_view&      bullet          = best_effort::bullet_str,
        const int               indent_size     = 4
        ) -> string
    {
        if( s.empty() ) { return ""; }
        const auto indent = spaces( indent_size );

        string formatted = left( bullet, indent_size );
        char prev_ch = '\0';
        for( const char ch : s )
        {
            if( prev_ch == '\n' ) { formatted += indent; }
            formatted += ch;
            prev_ch = ch;
        }
        return formatted;
    }

}  // namespace cppx
