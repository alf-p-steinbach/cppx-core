#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
/// \file
/// \brief
/// \make_name_ref{cppx,bits_per_} and
/// \make_name_ref{cppx,magnitude_bits_per_}.

#include <cppx-core/language/syntax/macro-use.hpp>          // CPPX_USE_CPPX
#include <cppx-core/language/system/Byte.hpp>               // cppx::bits_per_byte

#include <limits>           // std::numeric_limits 

namespace cppx
{
    CPPX_USE_STD( numeric_limits );

    /// \brief The number of bits per object/value of the specified type.
    template< class Type >
    constexpr int bits_per_             = sizeof( Type )*bits_per_byte;

    /// \brief The number of bits that determine the magnitude, i.e. the number of value
    /// representation bits minus a sign bit, if any.
    ///
    /// On 2019 computers this is generally `bits_per_<Type> - std::is_signed_v<Type>`.
    ///
    template< class Type >
    constexpr int magnitude_bits_per_   = numeric_limits<Type>::digits;

    struct Bitness{ enum Enum {
        _16 = 16, _32 = 32, _64 = 64, _128 = 128, system = bits_per_<void*>
        }; };
    static_assert(
        Bitness::system == 16 or
        Bitness::system == 32 or
        Bitness::system == 64 or
        Bitness::system == 128
        );

    namespace bitlevel
    {
        CPPX_USE_CPPX( bits_per_, magnitude_bits_per_, Bitness );
    }  // namespace bitlevel
}  // namespace cppx
