#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/collections/Value_bytes_.hpp>               // cppx::Value_bytes_
#include <cppx-core/language/tmp-support/basic-Enable_if_.hpp>  // cppx::Enable_if_
#include <cppx-core/language/tmp-support/basic-type-traits.hpp> // cppx::(is_integral_, is_trivially_copyable_)
#include <cppx-core/language/syntax/macro-use.hpp>              // CPPX_USE_STD
#include <cppx-core/text/to-hex-in-buffer.hpp>                  // cppx::*
#include <cppx-core/text/remove_leading_zeroes_in.hpp>          // cppx::remove_leading_zeroes_in

#include <c/assert.hpp>     // assert
#include <string>           // std::string

namespace cppx {
    CPPX_USE_STD( string );

    template< int capacity >
    inline auto hex_from_bytes(
        const Value_bytes_<capacity>&   bytes,
        const P_<const char>            hex_digits  = hex_digits_uppercase
        ) -> string
    {
        auto buffer = string( buffer_size_for( byte_span_to_hex_in, bytes.size() ), '\0' );
        const Size n_generated = byte_span_to_hex_in(
            buffer.data(), CPPX_ITEMS_OF( bytes ), hex_digits
            );
        assert( n_generated == buffer.size() ); (void) n_generated;
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
    { return hex_from_bytes<sizeof(value)>( value, hex_digits ); }

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
            static_assert( is_integral, "Only integral types supported for now" );
        }
    }

    inline auto to_hex(
        const Pointer_bytes&    bytes,
        const P_<const char>    hex_digits  = hex_digits_uppercase
        ) -> string
    {
        const int result_length = buffer_size_for( pointer_to_hex_in, bytes.size() );
        string result( result_length, '\0' );
        pointer_to_hex_in( result.data(), bytes, hex_digits );
        return result;
    }

    inline auto to_hex_numeral(
        const Pointer_bytes&        bytes,
        const P_<const char>        hex_digits  = hex_digits_uppercase
        ) -> string
    {
        string result = to_hex( bytes, hex_digits );
        remove_leading_zeroes_in( result );
        return result;
    }

}  // namespace cppx
