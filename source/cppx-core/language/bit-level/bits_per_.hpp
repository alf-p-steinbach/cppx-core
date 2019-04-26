#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
/// \file
/// \brief `bits_per_` and `magnitude_bits_per_`.

#include <cppx-core/language/syntax/macro-use.hpp>          // CPPX_USE_CPPX

#include <c/limits.hpp>     // CHAR_BIT
#include <limits>           // std::numeric_limits 

namespace cppx
{
    CPPX_USE_STD( numeric_limits );

    const int bits_per_byte = CHAR_BIT;     /// Usually 8, but e.g. 16 on some DSPs.

    /// \brief The number of bits per object/value of the specified type.
    ///
    /// On 2019 computers this is generally `bits_per_<Type> - std::is_signed_v<Type>`.
    ///
    template< class Type >
    constexpr int bits_per_             = sizeof( Type )*bits_per_byte;

    /// \brief The number of bits that determine the magnitude, i.e. the number of value
    /// representation bits minus a sign bit, if any.
    ///
    /// On 2019 computers this is generally `bits_per_<Type> - std::is_signed_v<Type>`.
    ///
    template< class Type >
    constexpr int magnitude_bits_per_   = numeric_limits<Type>::digits;

    namespace bitlevel
    {
        CPPX_USE_CPPX( bits_per_, magnitude_bits_per_ );
    }  // namespace bitlevel
}  // namespace cppx
