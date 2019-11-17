#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <gtest/gtest.h>

#include <cppx-core-language/meta-macro/macro-apply.hpp>
#include <cppx-core-language/meta-macro/macro-repeat.hpp>

namespace gtest = testing;

#ifndef CPPX_NO_DOLLARS_PLEASE
#   define $expect              EXPECT_TRUE
#   define $expect_eq           EXPECT_EQ
#   define $require             ASSERT_TRUE
#   define $require_eq          ASSERT_EQ
#   define $test_case           TEST
#endif
