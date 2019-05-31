#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

// This header is conditionally included from the top level "all.hpp" header. To avoid
// that, to use a non-UTF-8 execution character set, you can either just not use
// `_all_.hpp_`, or define `CPPX_NO_CHARSET_ASSERTION_PLEASE` before including it.

#include <cppx-core/config.hpp>     // cppx::check_the_basic_execution_character_set
#include <cppx-core/text/unicode/utf8-is_the_execution_character_set.hpp>

#ifndef CPPX_NO_CHARSET_ASSERTION_PLEASE
#   include <cppx-core/text/unicode/assert-utf8-execution-character-set.hpp>
#endif
//static_assert(
//    not cppx::check_the_execution_character_set
//        or cppx::utf8::is_the_execution_character_set(),
//    "The execution character set must be UTF-8 (e.g. MSVC option \"/utf-8\")."
//    );
