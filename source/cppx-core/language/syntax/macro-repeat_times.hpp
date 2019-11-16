#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/language/system/size-types.hpp>     // cppx::Index

#ifndef CPPX_NO_DOLLARS_PLEASE
#   define $repeat_times    CPPX_REPEAT_TIMES   ///< \dollarname{repeat_times}
#endif

// An ordinary counting loop avoids sillywarnings about unused loop variable, and
// if needed also allows access to the iteration count and limit.
//
#define CPPX_REPEAT_TIMES( n ) \
    for( cppx::Index _i = 0, _i_beyond = n; _i < _i_beyond; ++_i )
