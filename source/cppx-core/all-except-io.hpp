#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
static_assert( __cplusplus >= 201703L,
    "Requires C++17 or later. For MSVC use e.g. `/std:c++17 /Zc:__cplusplus /utf-8`."
    // https://blogs.msdn.microsoft.com/vcblog/2018/04/09/msvc-now-correctly-reports-__cplusplus/
    );
#ifndef CPPX_NO_CHARSET_ASSERTION_PLEASE
#   include <cppx-core/text/unicode/assert-utf8-execution-character-set.hpp>
#endif

// Intentionally omitted: `meta-macro` and `testing`.

#include <cppx-core/collections/_all_.hpp>
#include <cppx-core/failure-handling/_all_.hpp>
#include <cppx-core/iterators/_all_.hpp>
#include <cppx-core/language/_all_.hpp>
#include <cppx-core/meta-template/_all_.hpp>
#include <cppx-core/meta-type/_all_.hpp>
#include <cppx-core/misc/macro-define_tag.hpp>
#include <cppx-core/stdlib-includes/basic-general.hpp>      // Not the i/o headers!
#include <cppx-core/text/_all_.hpp>
