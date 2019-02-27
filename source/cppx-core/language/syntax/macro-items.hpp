#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/language/syntax/lvalue_ref_to.hpp>          // cppx::lvalue_ref_to

#include <iterator>         // std::(begin, end)

#ifndef CPPX_NO_DOLLARS_PLEASE
#   define  $items CPPX_ITEMS
#endif

// Careful, don't call with lvalue expression that has side effects.

#define CPPX_ITEMS( c ) \
    std::begin( cppx::lvalue_ref_to( c ) ), std::end( c )
