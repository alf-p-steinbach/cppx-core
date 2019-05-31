#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
/// \file
/// \brief
/// \make_name_ref{cppx,Byte},
/// \make_name_ref{cppx,Signed_byte} and
/// \make_name_ref{cppx,bits_per_byte}, + `std::byte` support definitions
/// \make_name_ref{cppx,as_number} and
/// \make_name_ref{cppx,as_std_byte}.
///
/// \sa Related: the <cppx-core/language/\make_ref{bits_per_.hpp}> header 
/// defines the general bit size function template `bits_per_byte`.

#include <cppx-core/language/syntax/macro-use.hpp>          // CPPX_USE_STD

#include <c/limits.hpp>     // CHAR_BIT
#include <c/stddef.hpp>     // std::byte

namespace cppx
{
    /// Default choice of byte type.
    using Byte              = unsigned char;
    using Signed_byte       = signed char;

    /// \brief Usually 8, but e.g. 16 on some DSPs.
    constexpr int bits_per_byte = CHAR_BIT;

    // Conversions to/from C++17 `std::byte`:
    inline auto as_number( const std::byte value )
        -> Byte
    { return std::to_integer<Byte>( value ); }

    inline auto as_std_byte( const Byte value )
        -> std::byte
    { return std::byte( value ); }

    // Documented in the <all.hpp> header.
    namespace system
    {
        CPPX_USE_CPPX( Byte, Signed_byte, bits_per_byte, as_number, as_std_byte );
    }
}  // namespace cppx
