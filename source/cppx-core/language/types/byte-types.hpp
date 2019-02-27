#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
//
// cppx::cpp17::byte, cppx::Byte and cppx::Signed_byte

#include <cppx-core/language/syntax/macro-use.hpp>          // CPPX_USE_STD

#include <c/limits.hpp>                 // CHAR_BIT
#include <c/stddef.hpp>                 // std::byte

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
    }

}  // namespace cppx
