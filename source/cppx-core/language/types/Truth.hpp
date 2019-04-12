#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
//
// A boolean type without implicit conversion from integral or pointer types.

#include <cppx-core/language/tmp/basic-Enable_if_.hpp>      // cppx::Enable_if_
#include <cppx-core/language/syntax/macro-use.hpp>          // CPPX_USE_STD

#include <type_traits>      // std::is_same_type_v

namespace cppx
{
    CPPX_USE_STD( is_same_v );

    class Truth
    {
        bool        m_value;

    public:
        explicit operator bool() const { return m_value; }

        template<
            class Arg,
            class = Enable_if_<is_same_v<Arg, bool>>
        >
        Truth( const Arg value ): m_value( value ) {}
    };
}  // namespace cppx
