#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <c/limits.hpp>     // INT_MAX
#include <c/stdint.hpp>     // uint8_t

#include <type_traits>      // std::is_unsigned_v

namespace cppx
{
    /// @cond DOXY_SHOW_IMPL_DETAILS
    namespace impl
    {
        constexpr inline auto log2_8( const uint8_t x ) noexcept
            -> int
        {
            constexpr int logs[] =
            {
                -1, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3
            };
            //static_assert( array_size_of( logs ) == 16 );

            return (x & 0xF0? 4 + logs[x >> 4] : logs[x]);
        }

        constexpr inline auto log2_16( const uint16_t x ) noexcept
            -> int
        { return (x & 0xFF00? 8 + log2_8( uint8_t( x >> 8 ) ) : log2_8( uint8_t( x ))); }

        constexpr inline auto log2_32( const uint32_t x ) noexcept
            -> int
        { return (x & 0xFFFF0000? 16 + log2_16( uint16_t( x >> 16 ) ) : log2_16( uint16_t( x ) )); }

        constexpr inline auto log2_64( const uint64_t x ) noexcept
            -> int
        { return (x & 0xFFFFFFFF00000000? 32 + log2_32( uint32_t( x >> 32 ) ) : log2_32( uint32_t( x ))); }

        constexpr inline auto log2( const uint8_t x ) noexcept    -> int  { return log2_8( x ); }
        constexpr inline auto log2( const uint16_t x ) noexcept   -> int  { return log2_16( x ); }
        constexpr inline auto log2( const uint32_t x ) noexcept   -> int  { return log2_32( x ); }
        constexpr inline auto log2( const uint64_t x ) noexcept   -> int  { return log2_64( x ); }
    }  // namespace impl
    /// @endcond

    template< class Unsigned >
    constexpr inline auto ilog2( const Unsigned x ) noexcept
        -> int
    {
        static_assert( std::is_unsigned_v<Unsigned> );
        return impl::log2( x );
    }
}  // namespace cppx
