#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/collections/Span_.hpp>                  // cppx::span_of
#include <cppx-core/language/syntax/macro-items_of.hpp>     // CPPX_ITEMS_OF
#include <cppx-core/language/syntax/repeat_times.hpp>       // cppx::repeat_times
#include <cppx-core/language/syntax/type-builders.hpp>      // cppx::P_
#include <cppx-core/parameters/buffer_size_for_.hpp>        // cppx::Call_operator_for_
#include <cppx-core/text/data/hex-digits.hpp>               // cppx::hex_digits*

namespace cppx {

    struct Function_byte_to_hex_in
    {
        static auto the_function(
            const P_<char>              buffer,
            const Byte                  value,
            const P_<const char>        hex_digits  = hex_digits_uppercase
            ) -> Size
        {
            constexpr int base = 0x10;
            char* p_end = buffer + hex_digits_per_byte;
            Byte remaining_part = value;
            repeat_times( hex_digits_per_byte, [&]{
                *--p_end = hex_digits[remaining_part % base];
                remaining_part /= Byte( base ); // Cast suppresses an MSVC sillywarning.
                } );
            return hex_digits_per_byte;
        }

        static constexpr auto its_buffer_size()
            -> Size
        { return hex_digits_per_byte; }
    };

    // buffer, value, {optional} hex_digits
    constexpr auto byte_to_hex_in = Call_operator_for_<Function_byte_to_hex_in>();

    struct Function_byte_span_to_hex_in
    {
        static auto the_function(
            const P_<char>              buffer,
            const P_<const Byte>        p_first,
            const P_<const Byte>        p_beyond,
            const P_<const char>        hex_digits  = hex_digits_uppercase
            ) -> Size
        {
            char* p = buffer;
            for( const Byte value: span_of( p_first, p_beyond ) ) {
                byte_to_hex_in( p, value, hex_digits );
                p += buffer_size_for( byte_to_hex_in );
            }
            return p - buffer;
        }

        static constexpr auto its_buffer_size( const int n_bytes )
            -> Size
        { return n_bytes*hex_digits_per_byte; }
    };

    // buffer, p_first, p_beyond, {optional} hex_digits 
    constexpr auto byte_span_to_hex_in = Call_operator_for_<Function_byte_span_to_hex_in>();

}  // namespace cppx
