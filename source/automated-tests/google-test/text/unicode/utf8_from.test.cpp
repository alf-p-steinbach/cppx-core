#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <cppx-core/core-language/types/byte-types.hpp>     // cppx::Byte
#include <cppx-core/core-language/$use_from_namespace.hpp>  // $use_cppx
#include <cppx-core/meta-type/type-builders.hpp>            // cppx::P_

#include <cppx-core/testing/google-test-framework.hpp>
#include <cppx-core/text/unicode/utf8_from.hpp>

#include <string>       // std::string
#include <string_view>  // std::string_view

$use_cppx( P_, Byte );

#include <cppx-core/text/unicode/assert-utf8-execution-character-set.hpp>   //!
namespace cppx_core::text::unicode::header_utf8_from 
{
    //-------------------------------------------- utf8_from

    $test_case( utf8_from, EMPTY_STRING )
    {
	    $expect_eq( cppx::utf8_from( "" ), "" );
        $expect_eq( cppx::utf8_from( std::string() ), "" );
        $expect_eq( cppx::utf8_from( std::string_view() ), "" );
    }

    $test_case( utf8_from, WIDE_EMPTY_STRING )
    {
	    $expect_eq( cppx::utf8_from( L"" ), "" );
        $expect_eq( cppx::utf8_from( std::wstring() ), "" );
        $expect_eq( cppx::utf8_from( std::wstring_view() ), "" );
    }

    $test_case( utf8_from, KNOWN_TEXT )
    {
        auto const& u8s = "blåbærsyltetøy";
	    $expect_eq( cppx::utf8_from( u8s ), u8s );
	    $expect_eq( cppx::utf8_from( reinterpret_cast<P_<const Byte>>( u8s ) ), u8s );
    }

    $test_case( utf8_from, WIDE_KNOWN_TEXT )
    {
        auto const& u8s = "blåbærsyltetøy";
        auto const& ws  = L"blåbærsyltetøy";
	    $expect_eq( cppx::utf8_from( ws ), u8s );
        $expect_eq( cppx::utf8_from( std::wstring( ws ) ), u8s );
        $expect_eq( cppx::utf8_from( std::wstring_view( ws ) ), u8s );
    }
}
