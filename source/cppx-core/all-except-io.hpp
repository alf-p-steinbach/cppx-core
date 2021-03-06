﻿#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <cppx-core-language/assert-cpp/is-c++17-or-later.hpp>
#ifndef CPPX_NO_CHARSET_ASSERTION_PLEASE
#   include <cppx-core-language/assert-cpp/has-utf8-execution-character-set.hpp>
#endif

#include <cppx-core/all-ascii.hpp>
#include <cppx-core/all-calc.hpp>
#include <cppx-core/collections/all.hpp>
#include <cppx-core/failure-handling/all.hpp>
#include <cppx-core/iterators/all.hpp>
#include <cppx-core/meta-template/all.hpp>
#include <cppx-core/meta-type/all.hpp>
#include <cppx-core/parameters/all.hpp>
#include <cppx-core/text/all.hpp>

#include <cppx-core-language/all.hpp>

#include <cpp/all-except-io.hpp>            // Not the i/o headers!
