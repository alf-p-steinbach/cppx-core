#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/core-language/syntax/macro_use.hpp>             // CPPX_USE_STD
#include <cppx-core/meta-type/type-builders.hpp>                    // cppx::P_

#include <iterator>         // std::(begin, end)
#include <type_traits>      // std::(true_type, false_type)
#include <utility>          // std::(declval)

namespace cppx
{
    CPPX_USE_STD( begin, end, declval, true_type, false_type );

    template< class Collection >
    class Has_method_empty_
    {
        template< class C, int x = sizeof( declval<C>().empty() == true ) >
        static auto test( const C& ) -> true_type;

        static auto test( ... ) -> false_type;

    public:
        static constexpr bool value = decltype(
            test( declval<Collection>() )
            )::value;
    };

    template< class Collection >
    constexpr bool has_method_empty_ = Has_method_empty_<Collection>::value;

    template< class Collection >
    inline auto is_empty( const Collection& c )
        -> bool
    {
        if constexpr( has_method_empty_<Collection> )
        {
            return c.empty();
        }
        else
        {
            return begin( c ) == end( c );
        }
    }

    inline auto is_empty( const P_<const char> s )
        -> bool
    { return s[0] == '\0'; }

    inline auto is_empty( const P_<const wchar_t> s )
        -> bool
    { return s[0] == L'\0'; }

    inline auto is_empty( const P_<const char16_t> s )
        -> bool
    { return s[0] == u'\0'; }

    inline auto is_empty( const P_<const char32_t> s )
        -> bool
    { return s[0] == U'\0'; }

}  // namespace cppx
