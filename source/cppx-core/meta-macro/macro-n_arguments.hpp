#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
/// \file
///
/// The CPPX_N_ARGUMENTS macro evaluates to the number of arguments that are passed to
/// it. It must be called with at least one argument, and at most 63 arguments. You can define
/// `CPPX_NO_DOLLARS_PLEASE` to suppress the definition of the `$n_arguments` alias.

#include <cppx-core/meta-macro/macro-invoke_macro.hpp>

#ifndef CPPX_NO_DOLLARS_PLEASE
#   define $n_arguments     CPPX_N_ARGUMENTS    ///< \brief Real name: `$n_arguments` (the `$` removed by DOxygen).
#endif

/// \brief Evaluates to the number of arguments that are passed to it.
/// \hideinitializer
///
/// Must be called with at least one argument, and at most 63 arguments.
///
/// Based on original code by Laurent Deniau in a posting titled “__VA_NARG__”, 17
/// January 2006 [in Usenet group “comp.std.c”](
/// https://groups.google.com/forum/?fromgroups=#!topic/comp.std.c/d-6Mj5Lko_s).
///
/// In a response Roland Illig nooted that “using `PP_NARG()` without arguments would violate
/// 6.10.3p4 of ISO C99.”, and this is so also for `CPPX_N_ARGUMENTS` in C++17; see §19.3/4.

#define CPPX_N_ARGUMENTS( ... )                         \
    CPPX_INVOKE_MACRO(                                  \
        CPPX_ARGUMENT_64,                               \
        (                                               \
            __VA_ARGS__,                                \
                                    63, 62, 61, 60,     \
            59, 58, 57, 56, 55, 54, 53, 52, 51, 50,     \
            49, 48, 47, 46, 45, 44, 43, 42, 41, 40,     \
            39, 38, 37, 36, 35, 34, 33, 32, 31, 30,     \
            29, 28, 27, 26, 25, 24, 23, 22, 21, 20,     \
            19, 18, 17, 16, 15, 14, 13, 12, 11, 10,     \
             9,  8,  7,  6,  5,  4,  3,  2,  1,  0      \
        )                                               \
    )

/// @cond DOXY_SHOW_IMPL_DETAILS
#define CPPX_ARGUMENT_64( \
     a1,  a2,  a3,  a4,  a5,  a6,  a7,  a8,  a9, a10,  \
    a11, a12, a13, a14, a15, a16, a17, a18, a19, a20,  \
    a21, a22, a23, a24, a25, a26, a27, a28, a29, a30,  \
    a31, a32, a33, a34, a35, a36, a37, a38, a39, a40,  \
    a41, a42, a43, a44, a45, a46, a47, a48, a49, a50,  \
    a51, a52, a53, a54, a55, a56, a57, a58, a59, a60,  \
    a61, a62, a63, a64, ... ) \
    a64
/// @endcond
