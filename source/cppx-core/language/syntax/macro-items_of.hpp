#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
/// \file
/// \brief `$items_of` eases use of standard library functions, e.g.
/// `sort( $items_of( numbers ) )`.

#include <cppx-core/meta-macro/only_lvalue_ref_to.hpp>  // cppx::only_lvalue_ref_to

#include <iterator>         // std::(begin, end)

#ifndef CPPX_NO_DOLLARS_PLEASE
#   define  $items_of       CPPX_ITEMS_OF           ///< \dollarname{items_of}
#endif

/// \brief `$items_of(c)` effectively expands to `std::begin(c), std::end(c)`.
///
/// `$items_of` eases use of standard library functions in C++ versions before
/// C++20, e.g. `std::sort( $items_of( my_numbers ) )`.
///
/// There is a check that `c` is not an rvalue expression, where the expansion could
/// inadvertently duplicate a costly or impure function call. But still, be careful.
/// Don't call this macro with an lvalue expression that has side effects.

#define CPPX_ITEMS_OF( c ) \
    std::begin( cppx::only_lvalue_ref_to( c ) ), std::end( c )
