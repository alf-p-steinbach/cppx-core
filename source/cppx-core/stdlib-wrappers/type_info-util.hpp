#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <cppx-core-language/syntax/macro-use.hpp>              // CPPX_USE_...
#include <cppx-core-language/tmp/Type_carrier_.hpp>             // cppx::Type_carrier_
#include <cppx-core-language/tmp/type-modifiers.hpp>            // cppx::Unref_
#include <cppx-core-language/type-checking/type_name_from.hpp>  // cppx::type_name_from

#include <string>       // std::string
#include <utility>      // std::forward

#ifdef __GNUC__
#   include  <cxxabi.h>
#endif

namespace cppx
{
    CPPX_USE_STD( forward, string );

    // An `operator<<` for stream output is defined by <cppx-core/io/type_name_of_.output.hpp>.
    template< class Type >
    struct Type_name_of_
    {
        auto value() const
            -> string
        {
            // Wrapping the type keeps any top level CV-qualification in the result.
            const string raw = type_name_from( typeid( Type_carrier_<Type> ) );
            const int i_first = 1 + raw.find_first_of( '<' );
            const int i_beyond = raw.find_last_of( '>' );
            return raw.substr( i_first, i_beyond - i_first );
        }

        operator string() const { return value(); }
    };

    template< class Type >
    constexpr auto type_name_of_ = Type_name_of_<Type>();

    template< class Type >
    inline auto type_name_of( Type&& expr )
        -> string
    { return type_name_of_<Unref_<decltype( forward<Type>( expr ) )>>(); }

}  // namespace cppx
