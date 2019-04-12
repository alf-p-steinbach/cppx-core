#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <cppx-core/collections/is_in.hpp>                          // cppx::is_in
#include <cppx-core/io/monospaced_bullet_block.hpp>                 // cppx::monospaced_bullet_block
#include <cppx-core/language/syntax/macro-use.hpp>                  // CPPX_USE_STD

//#include <c/stdio.hpp>      // FILE, fflush, fprintf, stderr, stdout
#include <iostream>         // std::(cerr, clog, endl)
#include <string_view>      // std::(string_view)

namespace cppx
{
    namespace debug
    {
        CPPX_USE_STD( cerr, cout, clog, endl, ostream, string_view );

        inline auto put_stderr_line( const string_view s ) noexcept
            -> Truth
        {
            if( not is_empty( s ) )
            {
                fprintf( stderr, "%.*s\n", int( s.length() ), s.data() );
            }
            fflush( stderr );
            return !!ferror( stderr );
        }

        inline auto put_line(
            ostream&                    stream,
            const string_view           s
            ) noexcept
            -> Truth
        {
            if( is_in( { &cerr, &clog }, &stream ) )
            {
                // Going down to the C level avoids effect where last '\n' is chopped off.
                stream.flush();
                return put_stderr_line( s );
            }
            else
            {
                const std::ios::iostate original_x_flags = stream.exceptions();
                stream << s << endl;
                const Truth ok = not stream.fail();
                if( original_x_flags ) { stream.exceptions( original_x_flags ); }
                return ok;
            }
        }

        inline auto put_line( const string_view s ) noexcept
            -> Truth
        { return put_line( cerr, s ); }

        inline auto put_block_to(
            ostream&                    stream,
            const string_view           bullet,
            const string_view           s
            )
            -> Truth
        { return put_line( stream, monospaced_bullet_block( s, bullet ) ); }

        inline auto put_info_block(
            const string_view           s,
            ostream&                    stream = clog
            )
            -> Truth
        { return put_block_to( stream, "i", s ); }

        inline auto put_error_block(
            const string_view           s,
            ostream&                    stream = cerr
            )
            -> Truth
        { return put_block_to( stream, best_effort::right_arrow_str, s ); }

    }  // namespace debug
}  // namespace cppx
