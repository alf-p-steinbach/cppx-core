#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/meta-macro/macro-n_arguments.hpp>
#include <cppx-core/meta-macro/macro-invoke_macro.hpp>
#include <cppx-core/meta-macro/macro-joined.hpp>

#ifndef CPPX_NO_DOLLARS_PLEASE
#   define $repeat      CPPX_REPEAT
#endif

#define CPPX_REPEAT( n_times, m ) \
    CPPX_REPEAT_EXPANSION_HELPER_( m, n_times )

#define CPPX_REPEAT_EXPANSION_HELPER_( m, n_times ) \
    CPPX_INVOKE_MACRO( CPPX_JOINED( CPPX_REPEAT_, n_times ), ( m ) )

#define CPPX_REPEAT_63( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_62( m )

#define CPPX_REPEAT_62( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_61( m )

#define CPPX_REPEAT_61( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_60( m )

#define CPPX_REPEAT_60( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_59( m )

#define CPPX_REPEAT_59( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_58( m )

#define CPPX_REPEAT_58( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_57( m )

#define CPPX_REPEAT_57( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_56( m )

#define CPPX_REPEAT_56( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_55( m )

#define CPPX_REPEAT_55( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_54( m )

#define CPPX_REPEAT_54( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_53( m )

#define CPPX_REPEAT_53( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_52( m )

#define CPPX_REPEAT_52( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_51( m )

#define CPPX_REPEAT_51( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_50( m )

#define CPPX_REPEAT_50( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_49( m )

#define CPPX_REPEAT_49( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_48( m )

#define CPPX_REPEAT_48( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_47( m )

#define CPPX_REPEAT_47( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_46( m )

#define CPPX_REPEAT_46( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_45( m )

#define CPPX_REPEAT_45( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_44( m )

#define CPPX_REPEAT_44( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_43( m )

#define CPPX_REPEAT_43( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_42( m )

#define CPPX_REPEAT_42( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_41( m )

#define CPPX_REPEAT_41( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_40( m )

#define CPPX_REPEAT_40( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_39( m )

#define CPPX_REPEAT_39( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_38( m )

#define CPPX_REPEAT_38( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_37( m )

#define CPPX_REPEAT_37( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_36( m )

#define CPPX_REPEAT_36( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_35( m )

#define CPPX_REPEAT_35( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_34( m )

#define CPPX_REPEAT_34( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_33( m )

#define CPPX_REPEAT_33( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_32( m )

#define CPPX_REPEAT_32( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_31( m )

#define CPPX_REPEAT_31( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_30( m )

#define CPPX_REPEAT_30( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_29( m )

#define CPPX_REPEAT_29( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_28( m )

#define CPPX_REPEAT_28( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_27( m )

#define CPPX_REPEAT_27( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_26( m )

#define CPPX_REPEAT_26( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_25( m )

#define CPPX_REPEAT_25( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_24( m )

#define CPPX_REPEAT_24( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_23( m )

#define CPPX_REPEAT_23( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_22( m )

#define CPPX_REPEAT_22( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_21( m )

#define CPPX_REPEAT_21( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_20( m )

#define CPPX_REPEAT_20( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_19( m )

#define CPPX_REPEAT_19( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_18( m )

#define CPPX_REPEAT_18( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_17( m )

#define CPPX_REPEAT_17( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_16( m )

#define CPPX_REPEAT_16( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_15( m )

#define CPPX_REPEAT_15( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_14( m )

#define CPPX_REPEAT_14( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_13( m )

#define CPPX_REPEAT_13( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_12( m )

#define CPPX_REPEAT_12( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_11( m )

#define CPPX_REPEAT_11( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_10( m )

#define CPPX_REPEAT_10( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_9( m )

#define CPPX_REPEAT_9( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_8( m )

#define CPPX_REPEAT_8( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_7( m )

#define CPPX_REPEAT_7( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_6( m )

#define CPPX_REPEAT_6( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_5( m )

#define CPPX_REPEAT_5( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_4( m )

#define CPPX_REPEAT_4( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_3( m )

#define CPPX_REPEAT_3( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_2( m )

#define CPPX_REPEAT_2( m ) \
    CPPX_INVOKE_MACRO_B( m, () ) \
    CPPX_REPEAT_1( m )

#define CPPX_REPEAT_1( m ) \
    CPPX_INVOKE_MACRO_B( m, () )
