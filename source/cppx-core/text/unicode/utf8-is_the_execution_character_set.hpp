#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/language/types/Truth.hpp>                   // cppx::Truth

namespace cppx::utf8
{
    constexpr auto is_the_execution_character_set()
        -> Truth
    {
        constexpr auto& slashed_o = "ø";
        return (sizeof( slashed_o ) == 3 and slashed_o[0] == '\xC3' and slashed_o[1] == '\xB8');
    }
}  // namespace cppx::utf8
