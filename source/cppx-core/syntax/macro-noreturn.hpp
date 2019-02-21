#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#ifndef CPPX_NO_DOLLARS_PLEASE
#   define $noreturn    CPPX_NORETURN
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
#   define CPPX_NORETURN            [[noreturn]]
#endif
