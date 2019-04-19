#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <cppx-core/language/syntax/type-assemblers.hpp>
/// \file
/// \brief `$define_tag(NAME)` defines `NAME` as a ~unique pointer type in namespace `tag`.

#ifndef CPPX_NO_DOLLARS_PLEASE
#   define $define_tag  CPPX_DEFINE_TAG             ///< \dollarname{define_tag}
#endif

/// \hideinitializer
/// \brief `$define_tag(NAME)` defines `NAME` as a ~unique pointer type in namespace `tag`.
///
/// Designed to support header-only modules: the same tag can be defined multiple
/// times in the same `tag` namespace. Preferably use this macro in the global namespace.
#define CPPX_DEFINE_TAG( name )                         \
    namespace tag                                       \
    {                                                   \
        using name = cppx::P_<struct name ## _tag>;     \
    }                                                   \
    static_assert( tag::name() == nullptr, "- support for semicolon - " )
