#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <cppx-core/failure-handling/hopefully_and_fail.hpp>
#include <cppx-core/failure-handling/macro-source_location.hpp>

#ifndef CPPX_NO_DOLLARS
#   define $fail    CPPX_FAIL
#   define $fail_   CPPX_FAIL_
#endif

#define CPPX_FAIL( ... ) \
    CPPX_FAIL_( std::runtime_error, __VA_ARGS__ )

#define CPPX_FAIL_( X, ... ) \
    cppx::fail<X>( std::string( __VA_ARGS__ ), CPPX_SOURCE_LOCATION )
