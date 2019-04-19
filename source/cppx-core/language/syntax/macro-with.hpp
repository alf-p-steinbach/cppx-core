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
/// For example:  
/// `$with( Lock( mutex ) ) access_resource();`  
/// `$with( cppx::Const_<Lock>( mutex ) ) access_resource();`

#define CPPX_WITH( ... ) \
    if ( auto&& _ = __VA_ARGS__; true or !!&_ )     // The !!&_ avoids warning about unused.

/// \brief Binds the specified declarator to `const auto&& _` in the following braces block.
///
/// For example:  
/// `$with_const( Lock( mutex ) ) access_resource();`
#define CPPX_WITH_CONST( ... ) \
    if( const auto& _ = __VA_ARGS__; true or !!&_ )
