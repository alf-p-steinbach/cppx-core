// Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
// Intentionally no `#pragma once`.
//
// Removes calls to `dbginfo` when NDEBUG is defined. The `dbginfo` function must be
// supplied by client code. 

#include <cppx-core/core-language/syntax/macro_use.hpp>     // CPPX_USE_STD
#include <cppx-core/meta-type/type-builders.hpp>

#include <string_view>

#ifndef CPPX_NO_DOLLARS
#   undef $dbginfo
#   define $dbginfo CPPX_DBGINFO
#endif

#undef CPPX_DBGINFO
#ifdef NDEBUG
#   define CPPX_DBGINFO( s )        []{}()
#else
#   define CPPX_DBGINFO( ... )      ::cppx::dbginfo( __VA_ARGS__ )
#endif

namespace cppx
{
    CPPX_USE_STD( string_view );
    extern void dbginfo( const string_view& );
}
