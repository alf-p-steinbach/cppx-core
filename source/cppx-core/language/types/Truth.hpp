#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
//
// A boolean type without implicit conversion from/to integral or pointer types.

#include <cppx-core/language/tmp/basic-Enable_if_.hpp>      // cppx::Enable_if_
#include <cppx-core/language/syntax/macro-use.hpp>          // CPPX_USE_STD

#include <type_traits>      // std::is_same_v

namespace cppx
{
    CPPX_USE_STD( is_same_v );

    class Truth
    {
        bool        m_value;

    public:
        // Implicit conversion to `bool`, because that's needed for template args.
        // Restricted via SFINAE because overload resolution, want predictability.
        template<
            class Result,
            class = Enable_if_<is_same_v<Result, bool>>
            >
        constexpr operator Result() const noexcept { return m_value; }

        // Construction SFINAE-restricted to `bool` argument.
        template<
            class Arg,
            class = Enable_if_<is_same_v<Arg, bool>>
            >
        constexpr Truth( const Arg value ) noexcept: m_value( value ) {}
    };
}  // namespace cppx
