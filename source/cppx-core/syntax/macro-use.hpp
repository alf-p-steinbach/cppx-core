#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/meta-macro/macro-apply_with_fixed_arg.hpp>

#ifndef CPPX_NO_DOLLARS
#   define $use_from_namespace          CPPX_USE_FROM_NAMESPACE
#   define $use_nested_ns_name          CPPX_USE_NESTED_NS_NAME
#   define $use_std                     CPPX_USE_STD
#   define $use_cppx                    CPPX_USE_CPPX
#endif

#define CPPX_GENERATE_USING_DECLARATION_IN( ns, name ) using ns::name;

#define CPPX_USE_FROM_NAMESPACE( ns, ... ) \
    CPPX_APPLY_WITH_FIXED_ARG( CPPX_GENERATE_USING_DECLARATION_IN, ns, __VA_ARGS__ ) \
    static_assert( true, "- just to support a semicolon after this -" )

#define CPPX_USE_NESTED_NS_NAME( nested_ns, parent_ns ) \
    namespace nested_ns = parent_ns::nested_ns

#define CPPX_USE_STD( ... ) \
    CPPX_USE_FROM_NAMESPACE( std, __VA_ARGS__ )

#define CPPX_USE_CPPX( ... ) \
    CPPX_USE_FROM_NAMESPACE( cppx, __VA_ARGS__ )
