#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
//
// UTF-8 code point iteration.
// For the classifiers see <url: https://en.wikipedia.org/wiki/UTF-8#Codepage_layout>.

#include <cppx-core/collections/is_empty.hpp>                   // cppx::is_empty
#include <cppx-core/collections/Range_.hpp>                     // cppx::up_to
#include <cppx-core/failure-handling/macro-fail.hpp>            // cppx::(hopefully, fail) CPPX_FAIL
#include <cppx-core/language/syntax/type-assemblers.hpp>        // cppx::(P_)
#include <cppx-core/language/types/byte-types.hpp>              // cppx::Byte
#include <cppx-core/language/types/signed-size-types.hpp>       // cppx::Size
#include <cppx-core/language/types/Truth.hpp>                   // cppx::Truth
#include <cppx-core/text/pointers-from-string_view.hpp>         // cppx::(p_first_of, p_beyond_of)

#include <string_view>          // std::(string_view )

namespace cppx::utf8
{
    CPPX_USE_STD( string_view );

    inline auto is_single_byte( const char ch )
        -> Truth
    { return (Byte( ch ) & 0x80) == 0x00; }

    inline auto is_valid_single_byte( const char ch )
        -> Truth
    { return is_single_byte( ch ); }

    inline auto is_continuation_byte( const char ch )
        -> Truth
    {
        // The general scheme is that bit pattern 0b10xxxxxx denotes a continuation byte,
        // providing 6 bits to the result value.
        return (Byte( ch ) & 0xC0) == 0x80;
    }

    inline auto is_valid_continuation_byte( const char ch )
        -> Truth
    { return is_continuation_byte( ch ); }

    inline auto is_lead_byte( const char ch )
        -> Truth
    {
        // The general scheme is that bit pattern 0b11xxxxxx denotes a lead byte.
        // The number of leading 1's equals the total number of bytes in this group.
        return (Byte( ch ) & 0xC0) == 0xC0;
    }

    inline auto is_valid_lead_byte( const char ch )
        -> Truth
    {
        // The general scheme is that bit pattern 0b11xxxxxx denotes a lead byte, but
        // some code points are ruled out because those encodings are not permitted.
        // E.g. 0b1100'000x would start an invalid encoding of a single ASCII character.
        return (0xC2 <= Byte( ch ) and Byte( ch ) <= 0xF4);
    }

    // Intentionally does no validity checking.
    inline auto group_size_for_lead_byte( const char lead_byte )
        -> int
    {
        int n_bytes = 0;
        for( auto bits = Byte( lead_byte ), mask = Byte( 0x80 ); (bits & mask) != 0; mask >>= 1 )
        {
            ++n_bytes;
        }
        return n_bytes;
    }

    // Move to the next Unicode code point, not necessarily the next character!
    inline void move_to_next( P_<const char>& p )
    {
        do{ ++p; } while( is_continuation_byte( *p ) );
    }

    inline void move_to_next( P_<const char>& p, const P_<const char> p_beyond )
    {
        // assert( p != nullptr )
        // assert( p != p_beyond )
        do{ ++p; } while( p != p_beyond and is_continuation_byte( *p ) );
    }

    // Move to the previous Unicode code point, not necessarily the previous character!
    inline void move_to_prev( P_<const char>& p )
    {
        do{ --p; } while( is_continuation_byte( *p ) );
    }

    inline auto move_to_prev( P_<const char>& p, const P_<const char> p_first )
        -> Truth
    {
        // assert( p != nullptr )
        // assert( p != p_first )
        do{ --p; } while( p != p_first and is_continuation_byte( *p ) );

        return not( p == p_first and is_continuation_byte( *p ) );
    }

    inline void advance( P_<const char>& p, const Size distance )
    {
        if( distance >= 0 )
        {
            for( auto _ : up_to( distance ) ) { (void)_; move_to_next( p ); }
        }
        else
        {
            for( auto _ : up_to( -distance ) ) { (void)_; move_to_prev( p ); }
        }
    }

    inline auto advance( P_<const char>& p, const Size distance, const string_view& range )
        -> Truth
    {
        if( distance >= 0 )
        {
            const auto p_beyond = p_beyond_of( range );
            for( auto _ : up_to( distance ) ) { (void)_; move_to_next( p, p_beyond ); }
        }
        else
        {
            const auto p_first = p_first_of( range );
            for( auto _ : up_to( -distance ) )
            {
                (void)_;
                if( not move_to_prev( p, p_first ) )
                {
                    return false;
                }
            }
        }
        return true;
    }

    inline auto next( P_<const char> p )
        -> P_<const char>
    {
        move_to_next( p );
        return p;
    }

    inline auto next( P_<const char> p, const P_<const char> p_beyond )
        -> P_<const char>
    {
        move_to_next( p, p_beyond );
        return p;
    }

    inline auto prev(  P_<const char> p )
        -> P_<const char>
    {
        move_to_prev( p );
        return p;
    }

    inline auto to_prev_code_point( P_<const char> p, const P_<const char> p_first )
        -> P_<const char>
    {
        move_to_prev( p, p_first );
        return p;
    }

    inline auto n_code_points_in( const string_view& view )
        -> Size
    {
        if( is_empty( view ) )
        {
            return 0;
        }

        Size n = 0;
        for(    auto p = p_first_of( view ), beyond = p_beyond_of( view );
                p != beyond;
                move_to_next( p, beyond ) )
        { ++n; }
        return n;
    }

}  // namespace cppx::utf8
