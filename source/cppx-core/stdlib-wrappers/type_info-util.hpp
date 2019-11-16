#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <cppx-core/collections/Range_.hpp>                     // cppx::Range_
#include <cppx-core/language/syntax/type-builders.hpp>          // cppx::P_
#include <cppx-core/language/syntax/macro-use.hpp>              // CPPX_USE_...
#include <cppx-core/language/tmp/Type_carrier_.hpp>             // cppx::Type_carrier_
#include <cppx-core/language/tmp/type-mutators.hpp>             // cppx::Unref_
#include <cppx-core/text/ascii/ascii-util.hpp>                  // cppx::ascii::*

#include <functional>   // std::invoke
#include <stdlib.h>     // free
#include <string>       // std::string
#include <typeinfo>     // std::type_info
#include <utility>      // std::forward

#ifdef __GNUG__
#   include  <cxxabi.h>
#endif

namespace cppx
{
    CPPX_USE_STD( forward, invoke, string, type_info );

    inline auto type_name_from_info( const type_info& info )
        -> string;

    // An `operator<<` for stream output is defined by <cppx-core/io/type_name_of_.output.hpp>.
    template< class Type >
    struct Type_name_of_
    {
        auto value() const
            -> string
        {
            // Wrapping the type keeps any top level CV-qualification in the result.
            const string raw = type_name_from_info( typeid( Type_carrier_<Type> ) );
            const int i_first = 1 + raw.find_first_of( '<' );
            const int i_beyond = raw.find_last_of( '>' );
            return raw.substr( i_first, i_beyond - i_first );
        }

        auto operator()() const -> string { return value(); }
        operator string() const { return value(); }
    };

    template< class Type >
    constexpr auto type_name_of_ = Type_name_of_<Type>();

    template< class Type >
    inline auto type_name_of( Type&& expr )
        -> string
    { return type_name_of_<Unref_<decltype( forward<Type>( expr ) )>>(); }

#ifdef __GNUG__
    inline auto type_name_from_info( const type_info& info )
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

    inline auto type_name_from_info( const type_info& info )
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
