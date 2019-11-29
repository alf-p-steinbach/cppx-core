#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core-language/ascii/hex-digits.hpp>          // cppx::hex_digits*
#include <cppx-core-language/syntax/macro-items_of.hpp>     // CPPX_ITEMS_OF
#include <cppx-core-language/syntax/macro-repeat_times.hpp> // CPPX_REPEAT_TIMES
#include <cppx-core-language/syntax/type-builders.hpp>      // cppx::Type_
#include <cppx-core-language/types/C_buffer_param_.hpp>     // cppx::C_buffer_param_

#include <cppx-core/collections/Span_util.hpp>              // cppx::span_of
#include <cppx-core/parameters/buffer_size_for_.hpp>        // cppx::Call_operator_for_

namespace cppx {
    using Bufferptr_byte_to_hex     = C_buffer_param_<char, hex_digits_per_byte>;

    inline auto byte_to_hex_in(
        const Bufferptr_byte_to_hex     buffer,
        const Byte                      value,
        const Type_<const char*>        hex_digits  = hex_digits_uppercase
        ) -> Size
    {
        char* p_end = buffer.ptr() + hex_digits_per_byte;
        Byte remaining_part = value;
        CPPX_REPEAT_TIMES( hex_digits_per_byte ) {
            *--p_end = hex_digits[remaining_part % hex_base];
            remaining_part /= Byte( hex_base );      // Cast suppresses an MSVC sillywarning.
            }
        return hex_digits_per_byte;
    }

    inline auto byte_span_to_hex_in(
        const Bufferptr_byte_to_hex     buffer,
        const Type_<const Byte*>        p_first,
        const Type_<const Byte*>        p_beyond,
        const Type_<const char*>        hex_digits  = hex_digits_uppercase
        ) -> Size
    {
        char* p = buffer.ptr();
        for( const Byte value: span_of( p_first, p_beyond ) ) {
            byte_to_hex_in( Bufferptr_byte_to_hex( p ), value, hex_digits );
            p += Bufferptr_byte_to_hex::size_for_1();
        }
        return p - buffer;
    }
}  // namespace cppx
