#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <cppx-core/language/type-builders.hpp>

#ifndef CPPX_NO_DOLLARS
#   define $define_tag  CPPX_DEFINE_TAG
#endif

// Designed to support header-only modules: the same tag can be defined multiple
// times in the same tag namespace. Preferably use this macro in the global namespace.
#define CPPX_DEFINE_TAG( name )                         \
    namespace tag                                       \
    {                                                   \
        using cppx::P_;                                 \
        using name = P_<struct name ## _tag>;           \
    }                                                   \
    static_assert( tag::name() == nullptr, "- support for semicolon - " )
