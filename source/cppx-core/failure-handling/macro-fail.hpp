#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <cppx-core/failure-handling/fail_with_location.hpp>
#include <cppx-core/failure-handling/macro-source_location.hpp>

#ifndef CPPX_NO_DOLLARS_PLEASE
#   define $fail    CPPX_FAIL
#   define $fail_   CPPX_FAIL_
#endif

#define CPPX_FAIL( ... ) \
    CPPX_FAIL_( std::runtime_error, __VA_ARGS__ )

#define CPPX_FAIL_( X, ... ) \
    ::cppx::fail_with_location_<X>( CPPX_SOURCE_LOCATION, std::string( __VA_ARGS__ ) )
