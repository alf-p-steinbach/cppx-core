#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <_/test-framework.hpp>
#include <cppx-core/text/unicode/utf8-Generator.hpp>

#include <cppx-core/collections/dynamic-size-checking.hpp>      // cppx::(array_size_of, length_of)
#include <cppx-core/collections/Span_util.hpp>                  // cppx::all_but_last_of
#include <cppx-core-language/bit-level/all.hpp>                 // cppx::Byte
#include <cppx-core-language/syntax/declarations.hpp>           // $use_std

#include <iterator>         // std::(begin, end)

$use_cppx( P_, Byte, all_but_last_of, array_size_of, length_of );
$use_std( begin, end, string );

#include <cppx-core/text/unicode/assert-utf8-execution-character-set.hpp>   //!
$begin_test_suite( cppx_core, text, unicode, HEADER, utf8_Generator );

    //-------------------------------------------- utf8::Generator

    $test_case( Generator, EMPTY_STRING )
    {
        cppx::utf8::Generator generator;
        $expect_eq( generator.n_bad_chars(), 0 );
    }

    $test_case( Generator, LATIN1_TEXT )
    {
        auto const& ws  = L"blåbærsyltetøy";
        auto const& u8s =  "blåbærsyltetøy";

        cppx::utf8::Generator generator;
        string buffer( 80, '#' );
        const auto p_end = generator.utf8_from_codes(
            all_but_last_of( ws ), buffer.data()
            );
        buffer.resize( p_end - buffer.data() );
        $expect_eq( generator.n_bad_chars(), 0 );
        $expect_eq( length_of( buffer ), array_size_of( u8s ) - 1 );
        $expect_eq( buffer, u8s );
    }

    $test_case( Generator, NONBMP_TEXT )
    {
        // Clef symbol U+1D11E => surrogate pair {U+D834, U+DD1E}.
        auto const& u8s =  "A 𝄞 clef!";
        auto const& ws  = u"A 𝄞 clef!";     // With a surrogate pair.

        cppx::utf8::Generator generator;
        string buffer( 80, '#' );
        const auto p_end = generator.utf8_from_codes(
            all_but_last_of( ws ), buffer.data()
            );
        buffer.resize( p_end - buffer.data() );
        $expect_eq( generator.n_bad_chars(), 0 );
        //auto& r = buffer;
        $expect_eq( buffer, u8s
            //, ""
            //<< +Byte( r[2] ) << '|' << +Byte( u8s[2] ) << ", "
            //<< +Byte( r[3] ) << '|' << +Byte( u8s[3] ) << ", "
            //<< +Byte( r[4] ) << '|' << +Byte( u8s[4] ) << ", "
            //<< +Byte( r[5] ) << '|' << +Byte( u8s[5] ) << "."
            );
    }

    $test_case( Generator, INVALID_AHA )
    {
        // "H" = "high" value of surrogate pair = "first unit" of pair
        auto const& aHa = u"@\xD800@";
        auto const& u8s =  "@\x7F@";
 
        cppx::utf8::Generator generator;
        string buffer( 80, '#' );
        const auto p_end = generator.utf8_from_codes(
            all_but_last_of( aHa ), buffer.data()
            );
        buffer.resize( p_end - buffer.data() );
        $expect_eq( generator.n_bad_chars(), 1 );
        $expect_eq( length_of( buffer ), 3 );
        $expect_eq( buffer, u8s );
     }

    $test_case( Generator, INVALID_AHHA )
    {
        // "H" = "high" value of surrogate pair = "first unit" of pair
        auto const& aHHa    = u"@\xD800\xD800@";
        auto const& u8s     =  "@\x7F\x7F@";
 
        cppx::utf8::Generator generator;
        string buffer( 80, '#' );
        const auto p_end = generator.utf8_from_codes(
            all_but_last_of( aHHa ), buffer.data()
            );
        buffer.resize( p_end - buffer.data() );
        $expect_eq( generator.n_bad_chars(), 2 );
        $expect_eq( length_of( buffer ), 4 );
        $expect_eq( buffer, u8s );
     }

    $test_case( Generator, INVALID_ALA )
    {
        // "L" = "low" value of surrogate pair = "last unit" of pair
        auto const& aLa = u"@\xDC00@";
        auto const& u8s =  "@\x7F@";
 
        $require_eq( array_size_of( aLa ), 4 );
        cppx::utf8::Generator generator;
        string buffer( 80, '#' );
        const auto p_end = generator.utf8_from_codes(
            all_but_last_of( aLa ), buffer.data()
            );
        buffer.resize( p_end - buffer.data() );
        $expect_eq( generator.n_bad_chars(), 1 );
        $expect_eq( length_of( buffer ), 3 );
        $expect_eq( buffer, u8s );
     }

    $test_case( Generator, INVALID_ALLA )
    {
        // "L" = "low" value of surrogate pair = "last unit" of pair
        auto const& aLLa = u"@\xDC00\xDC00@";
        auto const& u8s =  "@\x7F\x7F@";
 
        cppx::utf8::Generator generator;
        string buffer( 80, '#' );
        const auto p_end = generator.utf8_from_codes(
            all_but_last_of( aLLa ), buffer.data()
            );
        buffer.resize( p_end - buffer.data() );
        $expect_eq( generator.n_bad_chars(), 2 );
        $expect_eq( length_of( buffer ), 4 );
        $expect_eq( buffer, u8s );
     }
    
    $test_case( Generator, INVALID_ALHA )
    {
        // "H" = "high" value of surrogate pair = "first unit" of pair
        // "L" = "low" value of surrogate pair = "last unit" of pair
        auto const& aLHa    = u"@\xDC00\xD800@";
        auto const& u8s     =  "@\x7F\x7F@";
 
        cppx::utf8::Generator generator;
        string buffer( 80, '#' );
        const auto p_end = generator.utf8_from_codes(
            all_but_last_of( aLHa ), buffer.data()
            );
        buffer.resize( p_end - buffer.data() );
        $expect_eq( generator.n_bad_chars(), 2 );
        $expect_eq( length_of( buffer ), 4 );
        $expect_eq( buffer, u8s );
     }

    $test_case( Generator, VALID_AHLA )
    {
        // "H" = "high" value of surrogate pair = "first unit" of pair
        // "L" = "low" value of surrogate pair = "last unit" of pair
        auto const& aLHa    = u"@\xD800\xDC00@";
        auto const& u8s     =  "@???what?@";
 
        cppx::utf8::Generator generator;
        string buffer( 80, '#' );
        const auto p_end = generator.utf8_from_codes(
            all_but_last_of( aLHa ), buffer.data()
            );
        buffer.resize( p_end - buffer.data() );
        $expect_eq( generator.n_bad_chars(), 0 );
        $expect( length_of( buffer ) >= 3 );
        //macro-expect_eq( buffer, u8s );
        (void) u8s;
     }

$end_test_suite( 5 );
