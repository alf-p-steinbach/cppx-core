#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <cppx-core/testing/google-test-framework.hpp>
#include <cppx-core/text/ascii/ascii-util.hpp>

#include <string>       // std::string
#include <string_view>  // std::string_view

namespace cppx_core::text::ascii::header_ascii_util 
{
    //-------------------------------------------- is_all_ascii

    $test_case( is_all_ascii, EMPTY_STRING )
    {
	    $expect( cppx::is_all_ascii( "" ) );
        $expect( cppx::is_all_ascii( std::string() ) );
        $expect( cppx::is_all_ascii( std::string_view() ) );
    }

    $test_case( is_all_ascii, KNOWN_TEXT )
    {
	    $expect( cppx::is_all_ascii( "foobar" ) );
	    $expect( not cppx::is_all_ascii( "blåbærsyltetøy" ) );
    }


    //-------------------------------------------- is_all_ascii_whitespace

    $test_case( is_all_ascii_whitespace, EMPTY_STRING )
    {
	    $expect( cppx::is_all_ascii_whitespace( "" ) );
        $expect( cppx::is_all_ascii_whitespace( std::string() ) );
        $expect( cppx::is_all_ascii_whitespace( std::string_view() ) );
    }

    $test_case( is_all_ascii_whitespace, WIDE_EMPTY_STRING )
    {
	    $expect( cppx::is_all_ascii_whitespace( L"" ) );
        $expect( cppx::is_all_ascii_whitespace( std::wstring() ) );
        $expect( cppx::is_all_ascii_whitespace( std::wstring_view() ) );
    }

    $test_case( is_all_ascii_whitespace, KNOWN_WHITESPACE_CHARS )
    {
	    $expect( cppx::is_all_ascii_whitespace( " \f\n\r\t\v" ) );
    }

    $test_case( is_all_ascii_whitespace, WIDE_KNOWN_WHITESPACE_CHARS )
    {
	    $expect( cppx::is_all_ascii_whitespace( L" \f\n\r\t\v" ) );
    }

    $test_case( is_all_ascii_whitespace, NOT_ALL_WHITESPACE )
    {
	    $expect( not cppx::is_all_ascii_whitespace( "x" ) );
    }

    $test_case( is_all_ascii_whitespace, WIDE_NOT_ALL_WHITESPACE )
    {
	    $expect( not cppx::is_all_ascii_whitespace( L"x" ) );
    }


    //-------------------------------------------- ascii_to_lowercase

    $test_case( ascii_to_lowercase, EMPTY_STRING )
    {
	    $expect_eq( cppx::ascii_to_lowercase( "" ), "" );
	    $expect_eq( cppx::ascii_to_lowercase( std::string() ), "" );
	    $expect_eq( cppx::ascii_to_lowercase( std::string_view() ), "" );
    }

    $test_case( ascii_to_lowercase, WIDE_EMPTY_STRING )
    {
	    $expect_eq( cppx::ascii_to_lowercase( L"" ), L"" );
	    $expect_eq( cppx::ascii_to_lowercase( std::wstring() ), L"" );
	    $expect_eq( cppx::ascii_to_lowercase( std::wstring_view() ), L"" );
    }
    
    $test_case( ascii_to_lowercase, KNOWN_RESULT )
    {
	    $expect_eq( cppx::ascii_to_lowercase( "FooBar-42" ), "foobar-42" );
	    $expect_eq( cppx::ascii_to_lowercase( std::string( "FooBar-42" ) ), "foobar-42" );
	    $expect_eq( cppx::ascii_to_lowercase( std::string_view( "FooBar-42" ) ), "foobar-42" );
    }

    $test_case( ascii_to_lowercase, WIDE_KNOWN_RESULT )
    {
	    $expect_eq( cppx::ascii_to_lowercase( L"FooBar-42" ), L"foobar-42" );
	    $expect_eq( cppx::ascii_to_lowercase( std::wstring( L"FooBar-42" ) ), L"foobar-42" );
	    $expect_eq( cppx::ascii_to_lowercase( std::wstring_view( L"FooBar-42" ) ), L"foobar-42" );
    }


    //-------------------------------------------- ascii_to_uppercase

    $test_case( ascii_to_uppercase, EMPTY_STRING )
    {
	    $expect_eq( cppx::ascii_to_uppercase( "" ), "" );
	    $expect_eq( cppx::ascii_to_uppercase( std::string() ), "" );
	    $expect_eq( cppx::ascii_to_uppercase( std::string_view() ), "" );
    }

    $test_case( ascii_to_uppercase, WIDE_EMPTY_STRING )
    {
	    $expect_eq( cppx::ascii_to_uppercase( L"" ), L"" );
	    $expect_eq( cppx::ascii_to_uppercase( std::wstring() ), L"" );
	    $expect_eq( cppx::ascii_to_uppercase( std::wstring_view() ), L"" );
    }
    
    $test_case( ascii_to_uppercase, KNOWN_RESULT )
    {
	    $expect_eq( cppx::ascii_to_uppercase( "FooBar-42" ), "FOOBAR-42" );
	    $expect_eq( cppx::ascii_to_uppercase( std::string( "FooBar-42" ) ), "FOOBAR-42" );
	    $expect_eq( cppx::ascii_to_uppercase( std::string_view( "FooBar-42" ) ), "FOOBAR-42" );
    }

    $test_case( ascii_to_uppercase, WIDE_KNOWN_RESULT )
    {
	    $expect_eq( cppx::ascii_to_uppercase( L"FooBar-42" ), L"FOOBAR-42" );
	    $expect_eq( cppx::ascii_to_uppercase( std::wstring( L"FooBar-42" ) ), L"FOOBAR-42" );
	    $expect_eq( cppx::ascii_to_uppercase( std::wstring_view( L"FooBar-42" ) ), L"FOOBAR-42" );
    }
}
