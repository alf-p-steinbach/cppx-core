#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

namespace cppx
{
    constexpr bool  check_the_execution_character_set
    #ifndef CPPX_NO_EXECUTION_CHARACTER_SET_CHECK_PLEASE
        = true;         // Default.
    #else
        = false;
    #endif
    // ↑ See <cppx-core/text/unicode/assert-utf8-execution-character-set.hpp>

    constexpr bool  use_ascii_substitutes
    #ifdef CPPX_ASCII_PLEASE
        = true;
    #else
        = false;        // Default.
    #endif
    // ↑ See <cppx-core/text/ascii/ascii-fallback-symbols.hpp>

}  // namespace cppx
