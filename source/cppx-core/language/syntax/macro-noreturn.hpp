#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
/// \file
/// \brief `void $noreturn foo();` tells the compiler that `foo()` is not returning.

#ifndef CPPX_NO_DOLLARS_PLEASE
#   define $noreturn    CPPX_NORETURN           ///< \dollarname{noreturn}
#endif

// Silly-warning suppression:
#if defined( _MSC_VER )
#   pragma warning( disable: 4646 ) // 'noreturn' function has non-void return type.
#endif

#ifdef CPPX_FIX_NORETURN_PLEASE
#   undef CPPX_NORETURN
#   if defined( _MSC_VER )
#       define CPPX_NORETURN        __declspec( noreturn )
#   elif defined( __GNUC__ )
#       define CPPX_NORETURN        __attribute__(( noreturn ))
#   endif
#endif

#ifndef CPPX_NORETURN
/// \brief `void $noreturn foo();` tells the compiler that `foo()` is not returning.
///
/// For older versions of Visual C++ and g++ that don't support the C++11
/// `[[noreturn]]` attribute, you can define the macro symbol `CPPX_FIX_NORETURN_PLEASE`,
/// preferably in the compiler invocation. That was the original purpose of this macro.
/// For newer compilers it's mainly just a readability thing, fewer distracting brackets.
#   define CPPX_NORETURN            [[noreturn]]
#endif
