#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
/// \file
/// \brief Macros for generating more concise and clear `using` statements, primarily
/// `$use_cppx` and
/// `$use_std`, but also more generally
/// `$use_from_namespace`,
/// `$use_nsname_in`,
/// `$use_cppx_nsname`,
/// `$use_std_nsname`,
/// `$use_nsnames_in`,
/// `$use_cppx_nsnames` and
/// `$use_std_nsnames`.


#include <cppx-core/meta-macro/macro-apply_with_fixed_arg.hpp>

#ifndef CPPX_NO_DOLLARS_PLEASE
#   define $use_from_namespace          CPPX_USE_FROM_NAMESPACE         ///< \dollarname{use_from_namespace}
#   define $use_cppx                    CPPX_USE_CPPX                   ///< \dollarname{use_cppx}
#   define $use_std                     CPPX_USE_STD                    ///< \dollarname{use_std}
#   define $use_nsname_from             CPPX_USE_NSNAME_FROM            ///< \dollarname{use_nsname_from}
#   define $use_cppx_nsname             CPPX_USE_CPPX_NSNAME            ///< \dollarname{use_cppx_nsname}
#   define $use_std_nsname              CPPX_USE_STD_NSNAME             ///< \dollarname{use_std_nsname}
#   define $use_nsnames_from            CPPX_USE_NSNAMES_FROM           ///< \dollarname{use_nsnames_from}
#   define $use_cppx_nsnames            CPPX_USE_CPPX_NSNAMES           ///< \dollarname{use_cppx_nsnames}
#   define $use_std_nsnames             CPPX_USE_STD_NSNAMES            ///< \dollarname{use_std_nsnames}

// Old names for compatibility.
#   define $use_nsname_in               CPPX_USE_NSNAME_FROM
#   define $use_nsnames_in              CPPX_USE_NSNAMES_FROM
#endif

// Old names for compatibility.
#define CPPX_USE_NSNAME_IN              CPPX_USE_NSNAME_FROM
#define CPPX_USE_NSNAMES_IN             CPPX_USE_NSNAMES_FROM


/// \hideinitializer
/// \brief Use each specified item `ITEM` from namespace `NS` as if by `using NS::ITEM;`.
///
/// \param  ns      The namespace name.
/// \param  ...     A comma separated list of items to use unqualified.
#define CPPX_USE_FROM_NAMESPACE( ns, ... ) \
    CPPX_APPLY_WITH_FIXED_ARG( CPPX_GENERATE_USING_DECLARATION_FOR, ns, __VA_ARGS__ ) \
    static_assert( !!"Terminate this statement with a semicolon" )

/// @cond DOXY_SHOW_IMPL_DETAILS
#define CPPX_GENERATE_USING_DECLARATION_FOR( ns, name ) \
    using ns::name;
/// @endcond

/// \brief Use each specified item `ITEM` from namespace `cppx` as if by `using cppx::ITEM;`.
///
/// \param  ...     A comma separated list of items to use unqualified.
#define CPPX_USE_CPPX( ... ) \
    CPPX_USE_FROM_NAMESPACE( cppx, __VA_ARGS__ )

/// \brief Use each specified item `ITEM` from namespace `std` as if by `using std::ITEM;`.
///
/// \param  ...     A comma separated list of items to use unqualified.
#define CPPX_USE_STD( ... ) \
    CPPX_USE_FROM_NAMESPACE( std, __VA_ARGS__ )

/// \brief Use `NESTED_NS` as an alias for namespace `PARENT_NS::NESTED_NS`.
///
/// \param  parent_ns   The namespace containing the relevant nested namespace.
/// \param  nested_ns   The nested namespace.
#define CPPX_USE_NSNAME_FROM( parent_ns, nested_ns ) \
    namespace nested_ns = parent_ns::nested_ns

/// \brief Use `NESTED_NS` as an alias for namespace `cppx::NESTED_NS`.
///
/// \param  nested_ns   The nested namespace.
#define CPPX_USE_CPPX_NSNAME( nested_ns ) \
    CPPX_USE_NSNAME_FROM( cppx, nested_ns )

/// \brief Use `NESTED_NS` as an alias for namespace `std::NESTED_NS`.
///
/// \param  nested_ns   The nested namespace.
#define CPPX_USE_STD_NSNAME( nested_ns ) \
    CPPX_USE_NSNAME_FROM( std, nested_ns )

/// \hideinitializer
/// \brief Use each specified `NESTED_NS` as an alias for namespace `PARENT_NS::NESTED_NS`.
///
/// \param  parent_ns   The namespace containing the relevant nested namespace.
/// \param  ...         A comma separated list of names of nested namespaces.
#define CPPX_USE_NSNAMES_FROM( parent_ns, ... ) \
    CPPX_APPLY_WITH_FIXED_ARG( CPPX_GENERATE_NSNAME_USAGE, parent_ns, __VA_ARGS__ ) \
    static_assert( !!"Terminate this statement with a semicolon" )

/// @cond DOXY_SHOW_IMPL_DETAILS
#define CPPX_GENERATE_NSNAME_USAGE( parent_ns, nested_ns ) \
    namespace nested_ns = parent_ns::nested_ns;
/// @endcond

/// \brief Use each specified `NESTED_NS` as an alias for namespace `cppx::NESTED_NS`.
///
/// \param  ...         A comma separated list of names of nested namespaces.
#define CPPX_USE_CPPX_NSNAMES( ... ) \
    CPPX_USE_NSNAMES_FROM( cppx, __VA_ARGS__ )

/// \brief Use each specified `NESTED_NS` as an alias for namespace `std::NESTED_NS`.
///
/// \param  ...         A comma separated list of names of nested namespaces.
#define CPPX_USE_STD_NSNAMES( ... ) \
    CPPX_USE_NSNAMES_FROM( std, __VA_ARGS__ )
