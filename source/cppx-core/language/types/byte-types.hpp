#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
/// \file
/// \brief
/// \make_name_ref{cppx,Byte} and
/// \make_name_ref{cppx,Signed_byte}, + `std::byte` support definitions
/// \make_name_ref{cppx,as_number} and
/// \make_name_ref{cppx,as_std_byte}.
///
/// \sa The <cppx-core/language/\make_ref{bits_per_.hpp}> header 
/// defines general bit size functionality, including `bits_per_byte`.

#include <cppx-core/language/syntax/macro-use.hpp>          // CPPX_USE_STD

#include <c/stddef.hpp>                 // std::byte

namespace cppx
{
    /// Default choice of byte type.
    using Byte              = unsigned char;
    using Signed_byte       = signed char;

    inline auto as_number( const std::byte value )
        -> Byte
    { return std::to_integer<Byte>( value ); }

    inline auto as_std_byte( const Byte value )
        -> std::byte
    { return std::byte( value ); }

    /// \brief `Byte`, `Signed_byte`, `as_number`, `as_std_byte`
    namespace byte_types
    {
        CPPX_USE_CPPX( Byte, Signed_byte, as_number, as_std_byte );
    }

    namespace cpp17
    {
        /// Defines `cpp17::byte` as an alias for the C++17 `std::byte`, useful in some
        /// contexts. The `std::byte` type is not a character type, so it will not be
        /// presented as a character when output to an iostream. To output it as a number
        /// use `std::to_integer`, or `cppx::as_number`.
        CPPX_USE_STD( byte, to_integer );
    }

}  // namespace cppx
