#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/core-language/syntax/macro_use.hpp>
#include <cppx-core/meta-template/Enable_if_.hpp>               // cppx::Enable_if_
#include <cppx-core/meta-type/type-traits.hpp>                  // cppx::is_unsigned_
#include <cppx-core/collections/size-checking.hpp>              // cppx::array_size_of

#include <c/limits.hpp>     // INT_MAX
#include <c/stdint.hpp>     // ::(uintXX_t)
#include <c/stdlib.hpp>     // ::(div_t, div)

namespace cppx
{
    // Using explicit `using` declarations instead of `inline` namespace to avoid ambiguity
    // elsewhere for the nested namespace name `impl`.
    namespace math
    {
        namespace impl
        {
            inline auto log2_8( const uint8_t x ) noexcept
                -> int
            {
                static constexpr int logs[] =
                {
                    INT_MAX, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3
                };
                static_assert( array_size_of( logs ) == 16 );

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
        }

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

        template<
            class Unsigned,
            class = Enable_if_<is_unsigned_<Unsigned>>
            >
        inline auto log2( const Unsigned x ) noexcept
            -> int
        { return impl::log2( x ); }

    }  // namespace math

    CPPX_USE_FROM_NAMESPACE( math,
        is_negative, div, mod, log2
        );

}  // namespace cppx
