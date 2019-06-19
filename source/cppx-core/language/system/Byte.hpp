#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
/// \file
/// \brief
/// \make_name_ref{cppx,Byte},
/// \make_name_ref{cppx,Signed_byte},
/// \make_name_ref{cppx,bytes_per_},
/// \make_name_ref{cppx,as_byte_ptr},
/// \make_name_ref{cppx,as_signedbyte_ptr},
/// \make_name_ref{cppx,as_char_ptr} and
/// \make_name_ref{cppx,bits_per_byte}, + `std::byte` support definitions
/// \make_name_ref{cppx,as_number} and
/// \make_name_ref{cppx,as_std_byte}.
///
/// \sa Related: the <cppx-core/language/\make_ref{bits_per_.hpp}> header 
/// defines the general bit size function template `bits_per_byte`.

#include <cppx-core/language/syntax/macro-use.hpp>          // CPPX_USE_STD
#include <cppx-core/language/system/size-types.hpp>         // cppx::Size
#include <cppx-core/language/syntax/type-assemblers.hpp>    // cppx::P_

#include <c/limits.hpp>     // CHAR_BIT
#include <c/stddef.hpp>     // std::byte

namespace cppx
{
    /// \brief Default choice of byte type.
    using Byte              = unsigned char;
    using Signed_byte       = signed char;

    /// \brief The number of bytes per instance of a type.
    template< class Type > constexpr Size bytes_per_ = sizeof( Type );

    inline auto as_byte_ptr( const P_<Signed_byte> p )          -> P_<Byte>;
    inline auto as_byte_ptr( const P_<const Signed_byte> p )    -> P_<const Byte>;
    inline auto as_byte_ptr( const P_<char> p )                 -> P_<Byte>;
    inline auto as_byte_ptr( const P_<const char> p )           -> P_<const Byte>;
    inline auto as_signedbyte_ptr( const P_<Byte> p )           -> P_<Signed_byte>;
    inline auto as_signedbyte_ptr( const P_<const Byte> p )     -> P_<const Signed_byte>;
    inline auto as_signedbyte_ptr( const P_<char> p )           -> P_<Signed_byte>;
    inline auto as_signedbyte_ptr( const P_<const char> p )     -> P_<const Signed_byte>;
    inline auto as_char_ptr( const P_<Byte> p )                 -> P_<char>;
    inline auto as_char_ptr( const P_<const Byte> p )           -> P_<const char>;
    inline auto as_char_ptr( const P_<Signed_byte> p )          -> P_<char>;
    inline auto as_char_ptr( const P_<const Signed_byte> p )    -> P_<const char>;

    /// \brief Usually 8, but e.g. 16 on some DSPs.
    constexpr int bits_per_byte = CHAR_BIT;

    // Conversions to/from C++17 `std::byte`:
    inline auto as_number( const std::byte value ) -> Byte;
    inline auto as_std_byte( const Byte value ) -> std::byte;

    // Documented in the <all.hpp> header.
    namespace system
    {
        CPPX_USE_CPPX(
            Byte, Signed_byte,
            as_byte_ptr, as_signedbyte_ptr, bits_per_byte, as_number, as_std_byte
            );
    }

    //------------------------------------------------------- impl

    inline auto as_byte_ptr( const P_<Signed_byte> p )
        -> P_<Byte>
    { return reinterpret_cast<P_<Byte>>( p ); }

    inline auto as_byte_ptr( const P_<const Signed_byte> p )
        -> P_<const Byte>
    { return reinterpret_cast<P_<const Byte>>( p ); }

    inline auto as_byte_ptr( const P_<char> p )
        -> P_<Byte>
    { return reinterpret_cast<P_<Byte>>( p ); }

    inline auto as_byte_ptr( const P_<const char> p )
        -> P_<const Byte>
    { return reinterpret_cast<P_<const Byte>>( p ); }

    inline auto as_signedbyte_ptr( const P_<Byte> p )
        -> P_<Signed_byte>
    { return reinterpret_cast<P_<Signed_byte>>( p ); }

    inline auto as_signedbyte_ptr( const P_<const Byte> p )
        -> P_<const Signed_byte>
    { return reinterpret_cast<P_<const Signed_byte>>( p ); }

    inline auto as_signedbyte_ptr( const P_<char> p )
        -> P_<Signed_byte>
    { return reinterpret_cast<P_<Signed_byte>>( p ); }

    inline auto as_signedbyte_ptr( const P_<const char> p )
        -> P_<const Signed_byte>
    { return reinterpret_cast<P_<const Signed_byte>>( p ); }

    inline auto as_char_ptr( const P_<Byte> p )
        -> P_<char>
    { return reinterpret_cast<P_<char>>( p ); }

    inline auto as_char_ptr( const P_<const Byte> p )
        -> P_<const char>
    { return reinterpret_cast<P_<const char>>( p ); }

    inline auto as_char_ptr( const P_<Signed_byte> p )
        -> P_<char>
    { return reinterpret_cast<P_<char>>( p ); }

    inline auto as_char_ptr( const P_<const Signed_byte> p )
        -> P_<const char>
    { return reinterpret_cast<P_<const char>>( p ); }

    inline auto as_number( const std::byte value )
        -> Byte
    { return std::to_integer<Byte>( value ); }

    inline auto as_std_byte( const Byte value )
        -> std::byte
    { return std::byte( value ); }

}  // namespace cppx
