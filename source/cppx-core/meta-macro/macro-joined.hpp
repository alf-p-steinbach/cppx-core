#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
/// \file
/// \brief `$joined` forms the `##` concatenation of the expansions of its arguments.

#ifndef CPPX_NO_DOLLARS_PLEASE
#   define $joined      CPPX_JOINED         ///< \dollarname{joined}
#endif

/// \brief Forms the `##` concatenation of the expansions of its arguments.
/// \hideinitializer
///
/// \param  a       A valid preprocessor token.
/// \param  b       Ditto.

#define CPPX_JOINED( a, b ) \
    CPPX_JOINED_EXPANSION_HELPER( a, b )

/// @cond DOXY_SHOW_IMPL_DETAILS
#define CPPX_JOINED_EXPANSION_HELPER( a, b ) \
    a ## b
/// @endcond
