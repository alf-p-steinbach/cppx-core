#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/language/syntax/macro-use.hpp>
//#include <cppx-core/language/tmp/basic-type-traits.hpp>         // cppx::is_unsigned_

#include <c/limits.hpp>     // INT_MAX
#include <c/stdint.hpp>     // ::(uintXX_t)
#include <c/stdlib.hpp>     // ::(div_t, div)
#include <type_traits>      // std::is_unsigned_v

namespace cppx
{
    // Using explicit `using` declarations instead of `inline` namespace to avoid ambiguity
    // elsewhere for the nested namespace name `impl`.
    namespace math
    {
        /// @cond DOXY_SHOW_IMPL_DETAILS
        namespace impl
        {
            inline auto log2_8( const uint8_t x ) noexcept
                -> int
            {
                static constexpr int logs[] =
                {
                    INT_MAX, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3
                };
                //static_assert( array_size_of( logs ) == 16 );

                return (x & 0xF0? 4 + logs[x >> 4] : logs[x]);
            }

            inline auto log2_16( const uint16_t x ) noexcept
                -> int
            { return (x & 0xFF00? 8 + log2_8( uint8_t( x >> 8 ) ) : log2_8( uint8_t( x ))); }

            inline auto log2_32( const uint32_t x ) noexcept
                -> int
            { return (x & 0xFFFF0000? 16 + log2_16( uint16_t( x >> 16 ) ) : log2_16( uint16_t( x ) )); }

            inline auto log2_64( const uint64_t x ) noexcept
                -> int
            { return (x & 0xFFFFFFFF00000000? 32 + log2_32( uint32_t( x >> 32 ) ) : log2_32( uint32_t( x ))); }

            inline auto log2( const uint8_t x ) noexcept    -> int  { return log2_8( x ); }
            inline auto log2( const uint16_t x ) noexcept   -> int  { return log2_16( x ); }
            inline auto log2( const uint32_t x ) noexcept   -> int  { return log2_32( x ); }
            inline auto log2( const uint64_t x ) noexcept   -> int  { return log2_64( x ); }
        }  // namespace impl
        /// @endcond

        inline auto is_negative( const int x ) noexcept
            -> bool
        { return (x < 0); }

        inline auto div( const int a, const int b ) noexcept
            -> int
        {
            const div_t r = ::div( a, b );
            return (r.quot < 0 and r.rem != 0? r.quot - 1 : r.quot);
        }

        inline auto mod( const int a, const int b ) noexcept
            -> int
        { return a - b*div( a, b ); }

        template< class Unsigned >
        inline auto log2( const Unsigned x ) noexcept
            -> int
        {
            static_assert( std::is_unsigned_v<Unsigned> );
            return impl::log2( x );
        }

    }  // namespace math

    CPPX_USE_FROM_NAMESPACE( math,
        is_negative, div, mod, log2
        );

}  // namespace cppx
