#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <_/test-framework.hpp>
#include <cppx-core/text/unicode/To_bytes.hpp>

#include <cppx-core/collections/size-checking.hpp>                  // cppx::(array_size_of, length_of)
#include <cppx-core/collections/Span_.hpp>                          // cppx::all_but_last_of
#include <cppx-core/core-language/syntax/macro_use.hpp>             // $use_std
#include <cppx-core/core-language/bit-level/_all_.hpp>              // cppx::Byte

#include <iterator>         // std::(begin, end)

$use_cppx( P_, Byte, all_but_last_of, array_size_of, length_of );
$use_std( begin, end, string );

#include <cppx-core/text/unicode/assert-utf8-execution-character-set.hpp>   //!
$begin_test_suite( cppx_core, text, unicode, HEADER, To_bytes );

    //-------------------------------------------- To_bytes

    $test_case( To_bytes, EMPTY_STRING )
    {
        cppx::To_bytes converter;
        $expect_eq( converter.n_bad_chars(), 0 );
    }

    $test_case( To_bytes, LATIN1_TEXT )
    {
        auto const& ws  = L"blåbærsyltetøy";
        auto const& u8s =  "blåbærsyltetøy";

        cppx::To_bytes converter;
        string buffer( 80, '#' );
        const auto p_end = converter.utf8_from_codes(
            all_but_last_of( ws ), buffer.data()
            );
        buffer.resize( p_end - buffer.data() );
        $expect_eq( converter.n_bad_chars(), 0 );
        $expect_eq( length_of( buffer ), array_size_of( u8s ) - 1 );
        $expect_eq( buffer, u8s );
    }

    $test_case( To_bytes, NONBMP_TEXT )
    {
        // Clef symbol U+1D11E => surrogate pair {U+D834, U+DD1E}.
        auto const& u8s =  "A 𝄞 clef!";
        auto const& ws  = u"A 𝄞 clef!";     // With a surrogate pair.

        cppx::To_bytes converter;
        string buffer( 80, '#' );
        const auto p_end = converter.utf8_from_codes(
            all_but_last_of( ws ), buffer.data()
            );
        buffer.resize( p_end - buffer.data() );
        $expect_eq( converter.n_bad_chars(), 0 );
        //auto& r = buffer;
        $expect_eq( buffer, u8s
            //, ""
            //<< +Byte( r[2] ) << '|' << +Byte( u8s[2] ) << ", "
            //<< +Byte( r[3] ) << '|' << +Byte( u8s[3] ) << ", "
            //<< +Byte( r[4] ) << '|' << +Byte( u8s[4] ) << ", "
            //<< +Byte( r[5] ) << '|' << +Byte( u8s[5] ) << "."
            );
    }

    $test_case( To_bytes, INVALID_AHA )
    {
        // "H" = "high" value of surrogate pair = "first unit" of pair
        auto const& aHa = u"@\xD800@";
        auto const& u8s =  "@\x7F@";
 
        cppx::To_bytes converter;
        string buffer( 80, '#' );
        const auto p_end = converter.utf8_from_codes(
            all_but_last_of( aHa ), buffer.data()
            );
        buffer.resize( p_end - buffer.data() );
        $expect_eq( converter.n_bad_chars(), 1 );
        $expect_eq( length_of( buffer ), 3 );
        $expect_eq( buffer, u8s );
     }

    $test_case( To_bytes, INVALID_AHHA )
    {
        // "H" = "high" value of surrogate pair = "first unit" of pair
        auto const& aHHa    = u"@\xD800\xD800@";
        auto const& u8s     =  "@\x7F\x7F@";
 
        cppx::To_bytes converter;
        string buffer( 80, '#' );
        const auto p_end = converter.utf8_from_codes(
            all_but_last_of( aHHa ), buffer.data()
            );
        buffer.resize( p_end - buffer.data() );
        $expect_eq( converter.n_bad_chars(), 2 );
        $expect_eq( length_of( buffer ), 4 );
        $expect_eq( buffer, u8s );
     }

    $test_case( To_bytes, INVALID_ALA )
    {
        // "L" = "low" value of surrogate pair = "last unit" of pair
        auto const& aLa = u"@\xDC00@";
        auto const& u8s =  "@\x7F@";
 
        $require_eq( array_size_of( aLa ), 4 );
        cppx::To_bytes converter;
        string buffer( 80, '#' );
        const auto p_end = converter.utf8_from_codes(
            all_but_last_of( aLa ), buffer.data()
            );
        buffer.resize( p_end - buffer.data() );
        $expect_eq( converter.n_bad_chars(), 1 );
        $expect_eq( length_of( buffer ), 3 );
        $expect_eq( buffer, u8s );
     }

    $test_case( To_bytes, INVALID_ALLA )
    {
        // "L" = "low" value of surrogate pair = "last unit" of pair
        auto const& aLLa = u"@\xDC00\xDC00@";
        auto const& u8s =  "@\x7F\x7F@";
 
        cppx::To_bytes converter;
        string buffer( 80, '#' );
        const auto p_end = converter.utf8_from_codes(
            all_but_last_of( aLLa ), buffer.data()
            );
        buffer.resize( p_end - buffer.data() );
        $expect_eq( converter.n_bad_chars(), 2 );
        $expect_eq( length_of( buffer ), 4 );
        $expect_eq( buffer, u8s );
     }
    
    $test_case( To_bytes, INVALID_ALHA )
    {
        // "H" = "high" value of surrogate pair = "first unit" of pair
        // "L" = "low" value of surrogate pair = "last unit" of pair
        auto const& aLHa    = u"@\xDC00\xD800@";
        auto const& u8s     =  "@\x7F\x7F@";
 
        cppx::To_bytes converter;
        string buffer( 80, '#' );
        const auto p_end = converter.utf8_from_codes(
            all_but_last_of( aLHa ), buffer.data()
            );
        buffer.resize( p_end - buffer.data() );
        $expect_eq( converter.n_bad_chars(), 2 );
        $expect_eq( length_of( buffer ), 4 );
        $expect_eq( buffer, u8s );
     }

    $test_case( To_bytes, VALID_AHLA )
    {
        // "H" = "high" value of surrogate pair = "first unit" of pair
        // "L" = "low" value of surrogate pair = "last unit" of pair
        auto const& aLHa    = u"@\xD800\xDC00@";
        auto const& u8s     =  "@???what?@";
 
        cppx::To_bytes converter;
        string buffer( 80, '#' );
        const auto p_end = converter.utf8_from_codes(
            all_but_last_of( aLHa ), buffer.data()
            );
        buffer.resize( p_end - buffer.data() );
        $expect_eq( converter.n_bad_chars(), 0 );
        $expect( length_of( buffer ) >= 3 );
        //macro_expect_eq( buffer, u8s );
        (void) u8s;
     }

$end_test_suite( 5 );
