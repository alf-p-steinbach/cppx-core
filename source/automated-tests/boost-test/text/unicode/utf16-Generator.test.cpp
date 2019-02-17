#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <_/test-framework.hpp>
#include <cppx-core/text/unicode/utf16-Generator.hpp>

#include <cppx-core/collections/size-checking.hpp>                  // cppx::(array_size_of, length_of)
#include <cppx-core/collections/Span_.hpp>                          // cppx::text_span_of_literal
#include <cppx-core/core-language/syntax/macro_use.hpp>             // $use_std
#include <cppx-core/core-language/bit-level/_all_.hpp>              // cppx::Byte
#include <cppx-core/meta-type/type-builders.hpp>                    // cppx::Raw_array_

#include <iterator>         // std::(begin, end)

$use_cppx( P_, Byte, text_span_of_literal, array_size_of, length_of, Raw_array_ );
$use_std( begin, end, string, u16string );

#include <cppx-core/text/unicode/assert-utf8-execution-character-set.hpp>   //!
$begin_test_suite( cppx_core, text, unicode, HEADER, utf16_Generator );

    //-------------------------------------------- utf16::Generator

    $test_case( utf16_Generator, EMPTY_STRING )
    {
        cppx::utf16::Generator generator;
        $expect_eq( generator.n_bad_groups(), 0 );
        $expect_eq( generator.n_noncanonical_groups(), 0 );
    }

    $test_case( utf16_Generator, LATIN1_TEXT )
    {
        auto const& u8s =   "blåbærsyltetøy";
        auto const& u16s  = u"blåbærsyltetøy";

        cppx::utf16::Generator generator;
        u16string buffer( 80, u'#' );
        const auto p_end = generator.utf16_from_bytes(
            text_span_of_literal( u8s ), buffer.data()
            );
        buffer.resize( p_end - buffer.data() );
        $expect_eq( generator.n_bad_groups(), 0 );
        $expect_eq( generator.n_noncanonical_groups(), 0 );
        $expect_eq( length_of( buffer ), array_size_of( u16s ) - 1 );
        $expect_eq( buffer, u16s );
    }

    $test_case( utf16_Generator, NONBMP_TEXT )
    {
        // Clef symbol U+1D11E => surrogate pair {U+D834, U+DD1E}.
        auto const& u8s     =  "A 𝄞 clef!";
        auto const& u16s    = u"A 𝄞 clef!";     // With a surrogate pair.

        cppx::utf16::Generator generator;
        u16string buffer( 80, u'#' );
        const auto p_end = generator.utf16_from_bytes(
            text_span_of_literal( u8s ), buffer.data()
            );
        buffer.resize( p_end - buffer.data() );
        $expect_eq( generator.n_bad_groups(), 0 );
        $expect_eq( generator.n_noncanonical_groups(), 0 );
        $expect_eq( length_of( buffer ), array_size_of( u16s ) - 1 );
        $expect_eq( buffer, u16s );
    }

    $test_case( utf16_Generator, INVALID_LATIN1_TEXT )
    {
        Raw_array_<char>    u8s     =  "blåbærsyltetøy";
        auto const&         u16s    = u"bl@\x7F" u"bærsyltetøy";

        $expect_eq( array_size_of( u16s ) -  1, 15 );
        u8s[2] = '@';
        cppx::utf16::Generator generator;
        u16string buffer( 80, u'#' );
        const auto p_end = generator.utf16_from_bytes(
            text_span_of_literal( u8s ), buffer.data()
            );
        buffer.resize( p_end - buffer.data() );
        $expect_eq( generator.n_bad_groups(), 1 );
        $expect_eq( generator.n_noncanonical_groups(), 0 );
        $expect_eq( length_of( buffer ), array_size_of( u16s ) - 1 );
        $expect_eq( buffer, u16s );
    }

$end_test_suite( 5 );
