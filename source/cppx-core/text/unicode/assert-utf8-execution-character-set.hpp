#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

// This header is conditionally included from the top level "_all_.hpp" header. To avoid
// that, to use a non-UTF-8 execution character set, you can either just not use
// `_all_.hpp_`, or define `CPPX_NO_CHARSET_ASSERTION_PLEASE` before including it.

#include <cppx-core/config.hpp>     // cppx::check_the_basic_execution_character_set

namespace cppx
{
    constexpr auto the_execution_character_set_is_utf8()
        -> bool
    {
        constexpr auto& slashed_o = "ø";
        return (sizeof( slashed_o ) == 3 and slashed_o[0] == '\xC3' and slashed_o[1] == '\xB8');
    }
}  // namespace cppx

static_assert(
    not cppx::check_the_execution_character_set
        or cppx::the_execution_character_set_is_utf8(),
    "The execution character set must be UTF-8 (e.g. MSVC option \"/utf-8\")."
    );
