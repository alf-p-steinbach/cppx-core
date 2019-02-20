#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <_/test-framework.hpp>
#include <cppx-core/text/unicode/utf8-iteration.hpp>

#include <cppx-core/language/types/byte-types.hpp>              // cppx::Byte
#include <cppx-core/language/types/signed-size-types.hpp>       // cppx::Size
#include <cppx-core/syntax/macro-use.hpp>                       // $use_cppx
#include <cppx-core/syntax/type-assemblers.hpp>                 // cppx::(P_, Raw_array_of_)
#include <cppx-core/text/unicode/utf8-Generator.hpp>            // cppx::utf8::Generator
#include <cppx-core/text/unicode/utf8-n_bytes_for.hpp>          // cppx::utf8::n_bytes_for

#include <c/assert.hpp>     // assert
#include <c/string.hpp>     // strlen
#include <string>           // std::string
#include <string_view>      // std::string_view
#include <vector>           // std::vector
#include <iterator>         // std::(begin, end)

$use_nested_ns_name( utf8, cppx );
$use_cppx( Byte, utf8::n_bytes_for, P_, Raw_array_of_, Size );

#include <cppx-core/text/unicode/assert-utf8-execution-character-set.hpp>   //!
$begin_test_suite( cppx_core, text, unicode, HEADER, utf8_iteration );

    //-------------------------------------------- classifiers
    // https://en.wikipedia.org/wiki/UTF-8#Codepage_layout

    $test_case( is_single_byte, ALL )
    {
        for( int i = 0; i <= 0xFF; ++i )
        {
            const auto ch = Byte( i );
            $require_eq(
                cppx::utf8::is_single_byte( ch ),  0x00 <= ch && ch <= 0x7F
                , "Value " << +ch
                );
        }
    }

    $test_case( is_continuation_byte, ALL )
    {
        for( int i = 0; i <= 0xFF; ++i )
        {
            const auto ch = Byte( i );
            $require_eq(
                cppx::utf8::is_continuation_byte( ch ), 0x80 <= ch and ch <= 0xBF
                , "Value " << +ch
                );
        }
    }

    $test_case( is_lead_byte, ALL )
    {
        for( int i = 0; i <= 0xFF; ++i )
        {
            const auto ch = Byte( i );
            $require_eq(
                cppx::utf8::is_lead_byte( ch ), 0xC0 <= ch and ch <= 0xFF
                , "Value " << +ch
                );
        }
    }

    $test_case( is_valid_lead_byte, ALL )
    {
        for( int i = 0; i <= 0xFF; ++i )
        {
            const auto ch = Byte( i );
            $require_eq(
                cppx::utf8::is_valid_lead_byte( ch ), 0xC2 <= ch and ch <= 0xF4
                , "Value " << +ch
                );
        }
    }


    //-------------------------------------------- move

    template< Size n >
    void generate_from(
        const Raw_array_of_<n, wchar_t>&    data,
        std::string&                        u8,
        std::vector<P_<const char>>&        group_pointers
        )
    {
            utf8::Generator generator;
            u8 = std::string( utf8::n_bytes_for( data ), '#' );
            P_<char> p = u8.data();
            for( const wchar_t wch : data )
            {
                group_pointers.push_back( p );
                if( wch == L'\0' )
                {
                    break;
                }
                p = generator.utf8_from_code( wch, p );
            }
    }

    $test_case( move_to_next, NORWEGIAN_TEXT )
    {
        const auto& s   =  "Blåbærsyltetøy!";
        const auto& ws  = L"Blåbærsyltetøy!";

        std::string                     u8;
        std::vector<P_<const char>>     group_pointers;
        generate_from( ws, u8, group_pointers );
        $require_eq( u8, s );

        int i = 0;
        assert( u8[u8.length()] == 0 );     // C++11 and later.
        for(
            P_<char const> p = group_pointers[0], beyond = group_pointers.back();
            p < beyond;
            cppx::utf8::move_to_next( p )
            )
        {
            $require_eq( p, group_pointers[i] );
            ++i;
        }
    }

    $test_case( move_to_next, NORWEGIAN_TEXT_AND_STOP )
    {
        const auto& s   =  "Blåbærsyltetøy!";
        const auto& ws  = L"Blåbærsyltetøy!";

        std::string                     u8;
        std::vector<P_<const char>>     group_pointers;
        generate_from( ws, u8, group_pointers );
        $require_eq( u8, s );

        assert( u8[u8.length()] == 0 );     // C++11 and later.
        int i = 0;
        for(
            P_<char const> p = group_pointers[0], beyond = group_pointers.back();
            p < beyond;
            cppx::utf8::move_to_next( p, beyond )
            )
        {
            $require_eq( p, group_pointers[i] );
            ++i;
        }
    }

    $test_case( move_to_next, STOPPING_AT_EOT )
    {
        const auto& malformed   = "Oh!\xF0\0*****";     // F0 lead byte indicates a 4 byte group.

        $use_std( begin, end );

        for(
            auto p = begin( malformed ), beyond = p + strlen( malformed );
            p != beyond;
            cppx::utf8::move_to_next( p, beyond )
            )
        {
            $require( p < beyond, "Didn't stop at end of malformed" );
        }
    }

    $test_case( move_to_prev, NORWEGIAN_TEXT )
    {
        const auto& s   =  "Blåbærsyltetøy!";
        const auto& ws  = L"Blåbærsyltetøy!";

        std::string                     u8;
        std::vector<P_<const char>>     group_pointers;
        generate_from( ws, u8, group_pointers );
        $require_eq( u8, s );

        assert( u8[u8.length()] == 0 );     // C++11 and later.
        int i = group_pointers.size() - 1;
        for(
            P_<char const> p = group_pointers.back(), first = group_pointers[0];
            true;
            cppx::utf8::move_to_prev( p )
            )
        {
            $require_eq( p, group_pointers[i] );
            if( p == first )
            {
                break;
            }
            --i;
        }
    }

$end_test_suite( 5 );
