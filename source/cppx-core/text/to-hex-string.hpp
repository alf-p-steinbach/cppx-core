#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/language/syntax/macro-use.hpp>      // CPPX_USE_STD
#include <cppx-core/text/to-hex-in-buffer.hpp>          // cppx::*
#include <cppx-core/text/remove_leading_zeroes_in.hpp>  // cppx::remove_leading_zeroes_in

#include <string>           // std::string

namespace cppx {
    CPPX_USE_STD( string );

    inline auto to_hex( const Pointer_bytes& bytes )
        -> string
    {
        const int result_length = buffer_size_for( pointer_to_hex_in, bytes.size() );
        string result( result_length, '\0' );
        pointer_to_hex_in( result.data(), bytes );
        return result;
    }

    inline auto to_hex_numeral( const Pointer_bytes& bytes )
        -> string
    {
        string hex_digits = to_hex( bytes );
        remove_leading_zeroes_in( hex_digits );
        return hex_digits;
    }

}  // namespace cppx
