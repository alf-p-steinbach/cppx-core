#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <cppx-core/collections/Range_.hpp>                     // cppx::Range_
#include <cppx-core/language/syntax/type-assemblers.hpp>        // cppx::P_
#include <cppx-core/language/syntax/macro-use.hpp>              // CPPX_USE_...
#include <cppx-core/text/ascii/ascii-util.hpp>                  // cppx::ascii::*

#include <functional>   // std::invoke
#include <stdlib.h>     // free
#include <string>       // std::string
#include <typeinfo>     // std::type_info

#ifdef __GNUG__
#   include  <cxxabi.h>
#endif

namespace cppx
{
    CPPX_USE_STD( invoke, string, type_info );

    inline auto type_name_of( const type_info& info )
        -> string;

    template< class Type >
    inline auto type_name_of_()
        -> string
    { return type_name_of( typeid( Type ) ); }

#ifdef __GNUG__
    inline auto type_name_of( const type_info& info )
        -> string
    {
        struct Malloc_string
        {
            P_<const char> p_chars;
            ~Malloc_string() { free( const_cast<P_<char>>( p_chars ) ); }
        };

        const P_<const char> mangled_name = info.name();
        int status = 0;
        const Malloc_string demangled = { ::abi::__cxa_demangle(
            info.name(),
            nullptr,            // Output buffer
            nullptr,            // length
            &status
            ) };
        return (status == 0? demangled.p_chars : mangled_name);
    }
#else
    namespace impl {
        inline auto is_ascii_separator( const char ch )
            -> bool
        {
            if( not ascii::contains( ch ) ) {
                return false;
            }

            const bool is_ascii_namechar =
                is_in( Range_( '0', '9' ), ch ) or
                is_in( Range_( 'A', 'Z' ), ch ) or
                is_in( Range_( 'a', 'z' ), ch ) or
                ch == '_';
            return not is_ascii_namechar;
        };
    }  // namespace impl

    inline auto type_name_of( const type_info& info )
        -> string
    {
        const string elaborated = string( info.name() ) + '\0';

        string result;
        string part;
        bool is_in_name = false;

        for( char ch: elaborated ) {
            if( impl::is_ascii_separator( ch ) ) {
                if( is_in_name ) {
                    if( part == "struct" or part == "class" or part == "enum" ) {
                        if( ascii::is_whitespace( ch ) ) {
                            ch = '\0';
                        }
                    } else {
                        result += part;
                    }
                    part = "";
                    is_in_name = false;
                }
                if( ch != '\0' ) {
                    result += ch;
                }
            } else {
                is_in_name = true;
                part += ch;
            }
        }
        return result;
    }
#endif

}  // namespace cppx
