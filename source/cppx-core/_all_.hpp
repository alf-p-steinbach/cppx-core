#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
static_assert( __cplusplus >= 201703L,
    "Requires C++17 or later. For MSVC use e.g. `/std:c++17 /Zc:__cplusplus /utf-8`."
    // https://blogs.msdn.microsoft.com/vcblog/2018/04/09/msvc-now-correctly-reports-__cplusplus/
    );
#ifndef CPPX_NO_CHARSET_ASSERTION_PLEASE
#   include <cppx-core/text/unicode/assert-utf8-execution-character-set.hpp>
#endif

#include <cppx-core/all-except-io.hpp>
#include <cppx-core/stdlib-includes/_all_.hpp>
