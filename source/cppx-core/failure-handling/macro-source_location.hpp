#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <cppx-core/failure-handling/Source_location.hpp>

#ifndef CPPX_NO_DOLLARS_PLEASE
#   define $source_location CPPX_SOURCE_LOCATION
#endif

#define CPPX_SOURCE_LOCATION \
    ::cppx::Source_location( __FILE__, __LINE__, {}, __func__ )
