#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/meta-macro/macro-apply_with_fixed_arg.hpp>

#ifndef CPPX_NO_DOLLARS_PLEASE
#   define $use_from_namespace          CPPX_USE_FROM_NAMESPACE
#   define $use_cppx                    CPPX_USE_CPPX
#   define $use_std                     CPPX_USE_STD
#   define $use_namespace_name_in       CPPX_USE_NAMESPACE_NAME_IN
#   define $use_namespace_names_in      CPPX_USE_NAMESPACE_NAMES_IN
#   define $use_cppx_namespace_names    CPPX_USE_CPPX_NAMESPACE_NAMES
#   define $use_std_namespace_names     CPPX_USE_STD_NAMESPACE_NAMES
#endif

#define CPPX_USE_FROM_NAMESPACE( ns, ... ) \
    CPPX_APPLY_WITH_FIXED_ARG( CPPX_GENERATE_USING_DECLARATION_FOR, ns, __VA_ARGS__ )

#define CPPX_GENERATE_USING_DECLARATION_FOR( ns, name ) \
    using ns::name;

#define CPPX_USE_CPPX( ... ) \
    CPPX_USE_FROM_NAMESPACE( cppx, __VA_ARGS__ )

#define CPPX_USE_STD( ... ) \
    CPPX_USE_FROM_NAMESPACE( std, __VA_ARGS__ )

#define CPPX_USE_NAMESPACE_NAME_IN( parent_ns, nested_ns ) \
    namespace nested_ns = parent_ns::nested_ns

#define CPPX_USE_NAMESPACE_NAMES_IN( parent_ns, ... ) \
    CPPX_APPLY_WITH_FIXED_ARG( CPPX_GENERATE_NAMESPACE_NAME_USAGE, parent_ns, __VA_ARGS__ )

#define CPPX_GENERATE_NAMESPACE_NAME_USAGE( parent_ns, nested_ns ) \
    namespace nested_ns = parent_ns::nested_ns;

#define CPPX_USE_CPPX_NAMESPACE_NAMES( ... ) \
    CPPX_USE_NAMESPACE_NAMES_IN( cppx, __VA_ARGS__ )

#define CPPX_USE_STD_NAMESPACE_NAMES( ... ) \
    CPPX_USE_NAMESPACE_NAMES_IN( std, __VA_ARGS__ )
