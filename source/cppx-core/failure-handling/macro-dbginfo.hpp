// Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
// Intentionally no `#pragma once`.
//
// Removes calls to `dbginfo` when NDEBUG is defined. The `dbginfo` function must be
// supplied by client code. 

#include <cppx-core/collections/String_value_view_.hpp>     // cppx::String_value_view

#include <string_view>

#ifndef CPPX_NO_DOLLARS_PLEASE
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
    extern void dbginfo( const String_value_view& );
}
