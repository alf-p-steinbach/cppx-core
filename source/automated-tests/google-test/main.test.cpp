#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <cppx-core/testing/google-test-framework.hpp>

#include <c/stdlib.hpp>         // system

auto main( int argc, char** argv )
    -> int
{
    #ifdef _WIN32
        system( "chcp 65001 >nul" );    // For UTF-8 output of test case names.
    #endif

    gtest::InitGoogleTest( &argc, argv );
    RUN_ALL_TESTS();
}
