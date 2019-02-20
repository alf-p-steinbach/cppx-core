#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

// For example
// $with( Lock( mutex ) ) access_resource();
// $with_const( Lock( mutex ) ) access_resource();
// $with( cppx::Const_<Lock>( mutex ) ) access_resource();

#ifndef CPPX_NO_DOLLARS
#   define $with        CPPX_WITH
#   define $with_const  CPPX_WITH_CONST
#endif

#ifdef _MSC_VER
#   pragma warning( disable: 4127 )     // Sillywarning "conditional expression is constant".
#endif

#define CPPX_WITH( ... ) \
    if ( auto&& _ = __VA_ARGS__; true or !!&_ )     // The !!&_ avoids warning about unused.

#define CPPX_WITH_CONST( ... ) \
    if( const auto& _ = __VA_ARGS__; true or !!&_ )
