#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <gtest/gtest.h>

#include <cppx-core/meta-macro/macro_apply.hpp>
#include <cppx-core/meta-macro/macro_repeat.hpp>

namespace gtest = testing;

#ifndef CPPX_NO_DOLLARS
#   define $expect              EXPECT_TRUE
#   define $expect_eq           EXPECT_EQ
#   define $require             ASSERT_TRUE
#   define $require_eq          ASSERT_EQ
#   define $test_case           TEST
#endif
