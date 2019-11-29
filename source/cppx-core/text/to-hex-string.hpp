#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/collections/Value_bytes_.hpp>                   // cppx::Value_bytes_

#include <cppx-core-language/syntax/macro-use.hpp>                  // CPPX_USE_STD
#include <cppx-core-language/text/remove_leading_zeroes_in.hpp>     // cppx::remove_leading_zeroes_in
#include <cppx-core-language/text/to-hex-in-buffer.hpp>             // cppx::*
#include <cppx-core-language/tmp/Enable_if_.hpp>                    // cppx::Enable_if_
#include <cppx-core-language/tmp/type-traits.hpp>                   // cppx::(is_xxx_)

#include <c/assert.hpp>     // assert
#include <string>           // std::string

namespace cppx {
    CPPX_USE_STD( string );

    template< int capacity >
    inline auto hex_from_value_bytes(
        const Value_bytes_<capacity>&   bytes,
        const P_<const char>            hex_digits  = hex_digits_uppercase
        ) -> string
    {
        auto buffer = string( buffer_size_for( byte_span_to_hex_in, bytes.size() ), '\0' );
        const Size n_generated = byte_span_to_hex_in(
            buffer.data(), CPPX_ITEMS_OF( bytes ), hex_digits
            );
        assert( n_generated == Size( buffer.size() ) ); (void) n_generated;
        return buffer;
    }

    template<
        class Integer,
        class = Enable_if_<is_integral_<Integer>>
        >
    inline auto hex_from_integer(
        const Integer           value,
        const P_<const char>    hex_digits  = hex_digits_uppercase
        ) -> string
    { return hex_from_value_bytes<sizeof(value)>( value, hex_digits ); }

    template<
        class Copyable,
        class = Enable_if_<is_trivially_copyable_<Copyable>>
        >
    inline auto hex_from_value(
        const Copyable&         value,
        const P_<const char>    hex_digits  = hex_digits_uppercase
        ) -> string
    {
        constexpr bool is_integral = is_integral_<Copyable>;
        if constexpr( is_integral ) {
            return hex_from_integer( value, hex_digits );
        } else {
            static_assert( is_integral, "For now `hex_from_value` only supports integral types" );
        }
    }

    template< class Type >
    inline auto to_hex(
        const Type&             value,
        const P_<const char>    hex_digits  = hex_digits_uppercase
        ) -> string
    {
        if constexpr( is_pointer_<Type> ) {
            return hex_from_pointer_bytes( value, hex_digits );
        } else if constexpr( is_scalar_<Type> ) {
            return hex_from_value( value, hex_digits );
        } else {
            constexpr bool ok = is_pointer_<Type> or is_scalar_<Type>;
            static_assert( ok, "For now `to_hex` only supports pointers and scalars" );
        }
    }

    template< class Type >
    inline auto to_hex_numeral(
        const Type&             value,
        const P_<const char>    hex_digits  = hex_digits_uppercase
        ) -> string
    {
        string result = to_hex( value, hex_digits );
        remove_leading_zeroes_in( result );
        return result;
    }

}  // namespace cppx
