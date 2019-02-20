#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <_/test-framework.hpp>
#include <cppx-core/text/unicode/utf8-from.hpp>

#include <cppx-core/language/types/byte-types.hpp>              // cppx::Byte
#include <cppx-core/syntax/macro-use.hpp>                       // $use_cppx
#include <cppx-core/syntax/type-assemblers.hpp>                 // cppx::P_

#include <string>       // std::string
#include <string_view>  // std::string_view

$use_cppx( P_, Byte );

#include <cppx-core/text/unicode/assert-utf8-execution-character-set.hpp>   //!
$begin_test_suite( cppx_core, text, unicode, HEADER, utf8_from );

    //-------------------------------------------- utf8::from

    $test_case( utf8_from, EMPTY_STRING )
    {
	    $expect_eq( cppx::utf8::from( "" ), "" );
        $expect_eq( cppx::utf8::from( std::string() ), "" );
        $expect_eq( cppx::utf8::from( std::string_view() ), "" );
    }

    $test_case( utf8_from, WIDE_EMPTY_STRING )
    {
	    $expect_eq( cppx::utf8::from( L"" ), "" );
        $expect_eq( cppx::utf8::from( std::wstring() ), "" );
        $expect_eq( cppx::utf8::from( std::wstring_view() ), "" );
    }

    $test_case( utf8_from, KNOWN_TEXT )
    {
        auto const& u8s = "blåbærsyltetøy";
	    $expect_eq( cppx::utf8::from( u8s ), u8s );
	    $expect_eq( cppx::utf8::from( reinterpret_cast<P_<const Byte>>( u8s ) ), u8s );
    }

    $test_case( utf8_from, WIDE_KNOWN_TEXT )
    {
        auto const& u8s = "blåbærsyltetøy";
        auto const& ws  = L"blåbærsyltetøy";
	    $expect_eq( cppx::utf8::from( ws ), u8s );
        $expect_eq( cppx::utf8::from( std::wstring( ws ) ), u8s );
        $expect_eq( cppx::utf8::from( std::wstring_view( ws ) ), u8s );
    }

    $test_case( utf8_from, UTF16_KNOWN_TEXT )
    {
        auto const& u8s     = "A \u1D11E clef!";        // "A 𝄞 clef!";
        auto const& u16s    = u"A \u1D11E clef!";       // With a surrogate pair.
	    $expect_eq( cppx::utf8::from( u16s ), u8s );
        $expect_eq( cppx::utf8::from( std::u16string( u16s ) ), u8s );
        $expect_eq( cppx::utf8::from( std::u16string_view( u16s ) ), u8s );
    }

$end_test_suite( 5 );
