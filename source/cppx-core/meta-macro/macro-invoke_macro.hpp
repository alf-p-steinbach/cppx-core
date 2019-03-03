#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
/// \file
/// Mostly this is a concession to the idiosyncracies of Visual C++, which still as of its 2017 version
/// is unable to count `__VA_ARGS__` as *n* arguments, and instead counts it as 1. Mostly. But as David
/// Wheeler remarked, one extra level of indirection is the solution to any computer science problem.

#ifndef CPPX_NO_DOLLARS_PLEASE
#   define $invoke_macro    CPPX_INVOKE_MACRO       ///< \dollarname{invoke_macro}
#   define $invoke_macro_b  CPPX_INVOKE_MACRO_B     ///< \dollarname{invoke_macro_b}
#endif

/// \brief Invokes the specified macro with the specified arguments list.
/// \hideinitializer
/// \param m        The name of a macro to invoke.
/// \param arglist  A parenthesized list of arguments. Can be empty.

#define CPPX_INVOKE_MACRO( m, arglist ) \
    m arglist

/// \brief Invokes the specified macro with the specified arguments list.
/// \hideinitializer
/// \param m        The name of a macro to invoke.
/// \param arglist  A parenthesized list of arguments. Can be empty.
///
/// The only difference between `CPPX_INVOKE_MACRO` and `CPPX_INVOKE_MACRO_B` is that they're
/// *different* macros. One may have to use both in order to guarantee macro expansion in
/// certain (not very well defined) situations. E.g. see <cppx-core/meta-macro/macro-apply.hpp>.

#define CPPX_INVOKE_MACRO_B( m, arglist ) \
    m arglist
