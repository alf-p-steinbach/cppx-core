#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

// Mostly this is a concession to the idiosyncracies of Visual C++, which still as of its 2017 version
// is unable to count __VA_ARGS__ as N arguments, and instead counts it as 1. Mostly. But as someone
// remarked, one extra level of indirection is the solution to any computer science problem.
//

#ifndef CPPX_NO_DOLLARS
#   define $invoke_macro    CPPX_INVOKE_MACRO
#   define $invoke_macro_b  CPPX_INVOKE_MACRO_B
#endif

#define CPPX_INVOKE_MACRO( m, arglist ) \
    m arglist

#define CPPX_INVOKE_MACRO_B( m, arglist ) \
    m arglist
