#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <_/test-framework.hpp>
#include <cppx-core/text/unicode/utf8-n_bytes_for.hpp>

#include <string>       // std::string
#include <string_view>  // std::string_view

#include <cppx-core/text/unicode/assert-utf8-execution-character-set.hpp>   //!
$begin_test_suite( cppx_core, text, unicode, HEADER, utf8_n_bytes_for );

    //-------------------------------------------- utf8::n_bytes_for

    $test_case( utf8_n_bytes_for, EMPTY_STRING )
    {
	    $expect_eq( cppx::utf8::n_bytes_for( "" ), 0 );
        $expect_eq( cppx::utf8::n_bytes_for( std::string() ), 0 );
        $expect_eq( cppx::utf8::n_bytes_for( std::string_view() ), 0 );
    }

    $test_case( utf8_n_bytes_for, WIDE_EMPTY_STRING )
    {
	    $expect_eq( cppx::utf8::n_bytes_for( L"" ), 0 );
        $expect_eq( cppx::utf8::n_bytes_for( std::wstring() ), 0 );
        $expect_eq( cppx::utf8::n_bytes_for( std::wstring_view() ), 0 );
    }

    $test_case( utf8_n_bytes_for, KNOWN_TEXT )
    {
        int const n = sizeof( u8"blåbærsyltetøy" ) - 1;
	    $expect_eq( cppx::utf8::n_bytes_for( "blåbærsyltetøy" ), n );
        $expect_eq( cppx::utf8::n_bytes_for( std::string( "blåbærsyltetøy" ) ), n );
        $expect_eq( cppx::utf8::n_bytes_for( std::string_view( "blåbærsyltetøy" ) ), n );
    }

    $test_case( utf8_n_bytes_for, WIDE_KNOWN_TEXT )
    {
        int const n = sizeof( u8"blåbærsyltetøy" ) - 1;
	    $expect_eq( cppx::utf8::n_bytes_for( L"blåbærsyltetøy" ), n );
        $expect_eq( cppx::utf8::n_bytes_for( std::wstring( L"blåbærsyltetøy" ) ), n );
        $expect_eq( cppx::utf8::n_bytes_for( std::wstring_view( L"blåbærsyltetøy" ) ), n );
    }

$end_test_suite( 5 );
