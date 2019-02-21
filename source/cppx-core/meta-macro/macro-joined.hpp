#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#ifndef CPPX_NO_DOLLARS_PLEASE
#   define $joined      CPPX_JOINED
#endif

#define CPPX_JOINED( a, b ) \
    CPPX_JOINED_EXPANSION_HELPER( a, b )

#define CPPX_JOINED_EXPANSION_HELPER( a, b ) \
    a ## b
