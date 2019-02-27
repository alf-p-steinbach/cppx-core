#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/collections/is_empty.hpp>                       // cppx::is_empty
#include <cppx-core/language/syntax/macro-use.hpp>                  // CPPX_USE_STD
#include <cppx-core/text/C_str_.hpp>                                // cppx::C_str

#include <exception>        // std::(exception, rethrow_exception)
#include <functional>       // std::function
#include <utility>          // std::move

namespace cppx
{
    CPPX_USE_STD( exception, function, move, rethrow_if_nested, string );

    inline void call_with_description_lines_from(
        const exception&                            x,
        const function<void( const C_str )>&        f
        )
    {
        f( x.what() );
        try
        {
            rethrow_if_nested( x );
        }
        catch( const exception& rx )
        {
            call_with_description_lines_from( rx, f );
        }
        catch( ... )
        {
            f( "<a non-standard exception>" );
        }
    }

    inline auto description_lines_from( const exception& x )
        -> string
    {
        string result;
        const auto add = [&]( const C_str s ) -> void
        {
            if( not is_empty( result ) )
            {
                result += '\n';
            }
            result += s;
        };
        call_with_description_lines_from( x, add );
        return result;
    }

}  // namespace cppx
