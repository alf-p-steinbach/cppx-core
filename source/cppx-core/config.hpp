#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

namespace cppx
{
    constexpr bool  check_the_execution_character_set       = true;
    // Header <cppx-core/text/ascii/ascii-fallback-symbols.hpp>

#ifdef CPPX_USE_ASCII_PLEASE
    constexpr bool  use_ascii_substitutes                   = true;
    // Header <cppx-core/text/unicode/assert-utf8-execution-character-set.hpp>
#else
    constexpr bool  use_ascii_substitutes                   = false;
    // Header <cppx-core/text/unicode/assert-utf8-execution-character-set.hpp>
#endif

}  // namespace cppx
