#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/language/types/byte-types.hpp>          // cppx::bits_per_byte

#include <limits>           // std::numeric_limits

namespace cppx
{
    template< class Type >
    constexpr int bits_per_             = sizeof( Type )*bits_per_byte;

    // Note: on modern computers this is generally `bits_per_<Type> - std::is_signed_v<Type>`.
    template< class Type >
    constexpr int magnitude_bits_per_   = std::numeric_limits<Type>::digits;

}  // namespace cppx
