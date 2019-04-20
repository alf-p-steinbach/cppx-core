#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
/// \file
/// \brief `$with` binds the specified declarator to `auto&& _` in the following braces block.


#ifndef CPPX_NO_DOLLARS_PLEASE
#   define $with        CPPX_WITH               ///< \dollarname{with}
#   define $with_const  CPPX_WITH_CONST         ///< \dollarname{with_const}
#endif

#ifdef _MSC_VER
#   pragma warning( disable: 4127 )     // Sillywarning "conditional expression is constant".
#endif

/// \brief Binds the specified declarator to `auto&& _` in the following braces block.
///
/// `$with` can be used to make clear that an object is used for constructor + destructor
/// execution (RAII), or that it's used just to hold a temporary result in order to access
/// parts of it using the `_` name.
///
/// RAII examples:  
/// `$with( Lock( mutex ) ) access_resource();`  
/// `$with( Const_<Lock>( mutex ) ) access_resource();`

#define CPPX_WITH( ... ) \
    if ( auto&& _ [[maybe_unused]] = __VA_ARGS__; true )

/// \brief Binds the specified declarator to `const auto& _` in the following braces block.
///
/// For example:  
/// `$with_const( Lock( mutex ) ) access_resource();`
#define CPPX_WITH_CONST( ... ) \
    if( const auto& _ [[maybe_unused]] = __VA_ARGS__; true )
