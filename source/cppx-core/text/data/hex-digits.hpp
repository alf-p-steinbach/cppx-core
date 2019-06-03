#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/language/syntax/macro-use.hpp>          // CPPX_USE_STD
#include <cppx-core/language/calc/integer-operations.hpp>   // cppx::div_up
#include <cppx-core/language/system/Byte.hpp>               // cppx::bits_per_byte

namespace cppx {

    constexpr char  hex_digits_uppercase[]  = "0123456789ABCDEF";
    constexpr char  hex_digits_lowercase[]  = "0123456789abcdef";
    constexpr int   hex_digits_per_byte     = div_up( bits_per_byte, 4 );

}  // namespace cppx
