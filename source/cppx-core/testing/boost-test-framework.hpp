#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
//
// In one translation unit, define BOOST_TEST_MODULE before including this.
// See the Boost Test documentation.

#ifdef CPPX_BOOST_TEST_AS_HEADER_ONLY_PLEASE
#   include <boost/test/included/unit_test.hpp>
#else
#   include <boost/test/unit_test.hpp>
#endif

#include <cppx-core/meta-macro/macro-apply.hpp>
#include <cppx-core/meta-macro/macro-repeat.hpp>

#ifndef CPPX_NO_DOLLARS_PLEASE
#   define $begin_test_suite    CPPX_BEGIN_TEST_SUITE
#   define $end_test_suite      CPPX_END_TEST_SUITE

#   define $test_case           CPPX_TEST_CASE

#   define $expect              CPPX_EXPECT
#   define $expect_eq           CPPX_EXPECT_EQ
#   define $require             CPPX_REQUIRE
#   define $require_eq          CPPX_REQUIRE_EQ
#endif

// Example:
//
// $begin_test_suite( cppx_core, text, ascii, ascii_util );
// 
//     $test_case( testcasename, specificsname )
//     {
// 	       BOOST_TEST( true );
//     }
// 
// $end_test_suite( 4 );      // End 4 test suite nesting levels.

#define CPPX_BEGIN_TEST_SUITE( ... ) \
    CPPX_APPLY( CPPX_GENERATE_TEST_SUITE_START_, __VA_ARGS__ ) \
    static_assert( true, "- just to support a semicolon after this -" )

#define CPPX_GENERATE_TEST_SUITE_START_( name ) \
    BOOST_AUTO_TEST_SUITE( name );

#define CPPX_END_TEST_SUITE( nesting_level ) \
    CPPX_REPEAT( nesting_level, CPPX_GENERATE_TEST_SUITE_END_ ) \
    static_assert( true, "- just to support a semicolon after this -" )

#define CPPX_GENERATE_TEST_SUITE_END_() \
    BOOST_AUTO_TEST_SUITE_END();

#define CPPX_TEST_CASE( testcasename, specificsname ) \
    BOOST_AUTO_TEST_CASE( testcasename##_##specificsname )

#define CPPX_EXPECT( ... ) \
    CPPX_EXPECT_EXPANSION_HELPER_( CPPX_N_ARGUMENTS( __VA_ARGS__ ), __VA_ARGS__ )

#define CPPX_EXPECT_EXPANSION_HELPER_( n_args, ... ) \
    CPPX_INVOKE_MACRO( CPPX_JOINED( CPPX_EXPECT_, n_args ), ( __VA_ARGS__ ) )

#define CPPX_EXPECT_1( condition ) \
    BOOST_CHECK( condition )

#define CPPX_EXPECT_2( condition, message_expr ) \
    BOOST_CHECK_MESSAGE( condition, message_expr )

#define CPPX_EXPECT_EQ( ... ) \
    CPPX_EXPECT_EQ_EXPANSION_HELPER_( CPPX_N_ARGUMENTS( __VA_ARGS__ ), __VA_ARGS__ )

#define CPPX_EXPECT_EQ_EXPANSION_HELPER_( n_args, ... ) \
    CPPX_INVOKE_MACRO( CPPX_JOINED( CPPX_EXPECT_EQ_, n_args ), ( __VA_ARGS__ ) )

#define CPPX_EXPECT_EQ_2( a, b ) \
    BOOST_CHECK_EQUAL( a, b )

#define CPPX_EXPECT_EQ_3( a, b, message_expr ) \
    BOOST_CHECK_MESSAGE( (a) == (b), message_expr )

#define CPPX_REQUIRE( ... ) \
    CPPX_REQUIRE_EXPANSION_HELPER_( CPPX_N_ARGUMENTS( __VA_ARGS__ ), __VA_ARGS__ )

#define CPPX_REQUIRE_EXPANSION_HELPER_( n_args, ... ) \
    CPPX_INVOKE_MACRO( CPPX_JOINED( CPPX_REQUIRE_, n_args ), ( __VA_ARGS__ ) )

#define CPPX_REQUIRE_1( condition ) \
    BOOST_REQUIRE( condition )

#define CPPX_REQUIRE_2( condition, message_expr ) \
    BOOST_REQUIRE_MESSAGE( condition, message_expr )

#define CPPX_REQUIRE_EQ( ... ) \
    CPPX_REQUIRE_EQ_EXPANSION_HELPER_( CPPX_N_ARGUMENTS( __VA_ARGS__ ), __VA_ARGS__ )

#define CPPX_REQUIRE_EQ_EXPANSION_HELPER_( n_args, ... ) \
    CPPX_INVOKE_MACRO( CPPX_JOINED( CPPX_REQUIRE_EQ_, n_args ), ( __VA_ARGS__ ) )

#define CPPX_REQUIRE_EQ_2( a, b ) \
    BOOST_REQUIRE_EQUAL( a, b )

#define CPPX_REQUIRE_EQ_3( a, b, message_expr ) \
    BOOST_REQUIRE_MESSAGE( (a) == (b), message_expr )
