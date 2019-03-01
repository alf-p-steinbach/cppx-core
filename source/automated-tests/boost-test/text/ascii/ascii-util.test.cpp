#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <_/test-framework.hpp>
#include <cppx-core/text/ascii/ascii-util.hpp>

#include <string>       // std::string
#include <string_view>  // std::string_view

$begin_test_suite( cppx_core, text, ascii, HEADER, ascii_util );

    //-------------------------------------------- ascii_contains_all_of

    $test_case( ascii_contains_all_of, EMPTY_STRING )
    {
        $expect( cppx::ascii::contains_all_of( "" ) );
        $expect( cppx::ascii::contains_all_of( std::string() ) );
        $expect( cppx::ascii::contains_all_of( std::string_view() ) );
    }

    $test_case( ascii_contains_all_of, KNOWN_TEXT )
    {
        $expect( cppx::ascii::contains_all_of( "foobar" ) );
        $expect( not cppx::ascii::contains_all_of( "blåbærsyltetøy" ) );
    }


    //-------------------------------------------- ascii_is_all_whitespace

    $test_case( ascii_is_all_whitespace, EMPTY_STRING )
    {
        $expect( cppx::ascii::is_all_whitespace( "" ) );
        $expect( cppx::ascii::is_all_whitespace( std::string() ) );
        $expect( cppx::ascii::is_all_whitespace( std::string_view() ) );
    }

    $test_case( ascii_is_all_whitespace, WIDE_EMPTY_STRING )
    {
        $expect( cppx::ascii::is_all_whitespace( L"" ) );
        $expect( cppx::ascii::is_all_whitespace( std::wstring() ) );
        $expect( cppx::ascii::is_all_whitespace( std::wstring_view() ) );
    }

    $test_case( ascii_is_all_whitespace, KNOWN_WHITESPACE_CHARS )
    {
        $expect( cppx::ascii::is_all_whitespace( " \f\n\r\t\v" ) );
    }

    $test_case( ascii_is_all_whitespace, WIDE_KNOWN_WHITESPACE_CHARS )
    {
        $expect( cppx::ascii::is_all_whitespace( L" \f\n\r\t\v" ) );
    }

    $test_case( ascii_is_all_whitespace, NOT_ALL_WHITESPACE )
    {
        $expect( not cppx::ascii::is_all_whitespace( "x" ) );
    }

    $test_case( ascii_is_all_whitespace, WIDE_NOT_ALL_WHITESPACE )
    {
        $expect( not cppx::ascii::is_all_whitespace( L"x" ) );
    }


    //-------------------------------------------- ascii_to_lowercase

    $test_case( ascii_to_lowercase, EMPTY_STRING )
    {
        $expect_eq( cppx::ascii::to_lowercase( "" ), "" );
        $expect_eq( cppx::ascii::to_lowercase( std::string() ), "" );
        $expect_eq( cppx::ascii::to_lowercase( std::string_view() ), "" );
    }

    $test_case( ascii_to_lowercase, WIDE_EMPTY_STRING )
    {
        $expect_eq( cppx::ascii::to_lowercase( L"" ), L"" );
        $expect_eq( cppx::ascii::to_lowercase( std::wstring() ), L"" );
        $expect_eq( cppx::ascii::to_lowercase( std::wstring_view() ), L"" );
    }
    
    $test_case( ascii_to_lowercase, KNOWN_RESULT )
    {
        $expect_eq( cppx::ascii::to_lowercase( "FooBar-42" ), "foobar-42" );
        $expect_eq( cppx::ascii::to_lowercase( std::string( "FooBar-42" ) ), "foobar-42" );
        $expect_eq( cppx::ascii::to_lowercase( std::string_view( "FooBar-42" ) ), "foobar-42" );
    }

    $test_case( ascii_to_lowercase, WIDE_KNOWN_RESULT )
    {
        $expect_eq( cppx::ascii::to_lowercase( L"FooBar-42" ), L"foobar-42" );
        $expect_eq( cppx::ascii::to_lowercase( std::wstring( L"FooBar-42" ) ), L"foobar-42" );
        $expect_eq( cppx::ascii::to_lowercase( std::wstring_view( L"FooBar-42" ) ), L"foobar-42" );
    }


    //-------------------------------------------- ascii_to_uppercase

    $test_case( ascii_to_uppercase, EMPTY_STRING )
    {
        $expect_eq( cppx::ascii::to_uppercase( "" ), "" );
        $expect_eq( cppx::ascii::to_uppercase( std::string() ), "" );
        $expect_eq( cppx::ascii::to_uppercase( std::string_view() ), "" );
    }

    $test_case( ascii_to_uppercase, WIDE_EMPTY_STRING )
    {
        $expect_eq( cppx::ascii::to_uppercase( L"" ), L"" );
        $expect_eq( cppx::ascii::to_uppercase( std::wstring() ), L"" );
        $expect_eq( cppx::ascii::to_uppercase( std::wstring_view() ), L"" );
    }
    
    $test_case( ascii_to_uppercase, KNOWN_RESULT )
    {
        $expect_eq( cppx::ascii::to_uppercase( "FooBar-42" ), "FOOBAR-42" );
        $expect_eq( cppx::ascii::to_uppercase( std::string( "FooBar-42" ) ), "FOOBAR-42" );
        $expect_eq( cppx::ascii::to_uppercase( std::string_view( "FooBar-42" ) ), "FOOBAR-42" );
    }

    $test_case( ascii_to_uppercase, WIDE_KNOWN_RESULT )
    {
        $expect_eq( cppx::ascii::to_uppercase( L"FooBar-42" ), L"FOOBAR-42" );
        $expect_eq( cppx::ascii::to_uppercase( std::wstring( L"FooBar-42" ) ), std::wstring( L"FOOBAR-42" ) );
        $expect_eq( cppx::ascii::to_uppercase( std::wstring_view( L"FooBar-42" ) ), L"FOOBAR-42" );
    }

$end_test_suite( 5 );
