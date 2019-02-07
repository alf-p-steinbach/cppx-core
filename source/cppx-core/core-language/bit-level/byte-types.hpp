#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
//
// cppx::cpp17::byte, cppx::Byte and cppx::Signed_byte

#include <cppx-core/core-language/syntax/macro_use.hpp>     // CPPX_USE_STD

#include <c/limits.hpp>                 // CHAR_BIT
#include <c/stddef.hpp>                 // std::byte
#include <limits>                       // std::numeric_limits

namespace cppx
{
    // Defines cpp17::byte as an alias for std::byte, useful in some contexts.
    namespace cpp17
    {
        CPPX_USE_STD( byte );
    }

    inline namespace byte_types
    {
        using Byte              = unsigned char;
        using Signed_byte       = signed char;

        const int bits_per_byte     = CHAR_BIT;

        template< class Type >
        constexpr int bits_per_             = sizeof( Type )*bits_per_byte;

        // Note: this is generally `bits_per_<Type> - std::is_signed_v<Type>`.
        template< class Type >
        constexpr int magnitude_bits_per_   = std::numeric_limits<Type>::digits;
    }

}  // namespace cppx
