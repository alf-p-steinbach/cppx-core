#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <c/stdint.hpp>     // uint16_t, uint32_t, uint64_t
#include <bitset>           // std::bitset

namespace cppx
{
    inline namespace bitlevel
    {
        using std::bitset;

        template< int n >
        inline auto sum_of_bits( const bitset<n>& bits ) noexcept
            -> int
        { return bits.count(); }

        inline auto sum_of_bits( const uint16_t x ) noexcept
            -> int
        { return bitset<16>( x ).count(); }

        inline auto sum_of_bits( const uint32_t x ) noexcept
            -> int
        { return bitset<32>( x ).count(); }

        inline auto sum_of_bits( const uint64_t x ) noexcept
            -> int
        { return bitset<64>( x ).count(); }

#if 0  // Possible optimizations, probably not needed
#if defined( _MSC_VER )

        inline auto sum_of_bits( const uint16_t x ) noexcept
            -> int
        { return __popcnt16( x ); }

        inline auto sum_of_bits( const uint32_t x ) noexcept
            -> int
        { return __popcnt( x ); }

        inline auto sum_of_bits( const uint64_t x ) noexcept
            -> int
        { return __popcnt64( x ); }

#elif defined( __GNUC__ )

        namespace impl
        {
            template< class Unsigned >
            inline auto gcc_sum_of_bits(  const Unsigned x ) noexcept -> int;

            template<> inline auto gcc_sum_of_bits<unsigned>( const unsigned x ) noexcept
                -> int
            { return  __builtin_popcount( x ); }

            template<> inline auto gcc_sum_of_bits<unsigned long>( const unsigned long x ) noexcept
                -> int
            { return  __builtin_popcountl( x ); }

            template<> inline auto gcc_sum_of_bits<unsigned long long>( const unsigned long long x ) noexcept
                -> int
            { return  __builtin_popcountll( x ); }
        }  // namespace impl

        inline auto sum_of_bits( const uint16_t x ) noexcept
            -> int
        { return impl::gcc_sum_of_bits<uint32_t>( x ); }

        inline auto sum_of_bits( const uint32_t x ) noexcept
            -> int
        { return impl::gcc_sum_of_bits( x ); }

        inline auto sum_of_bits( const uint64_t x ) noexcept
            -> int
        { return impl::gcc_sum_of_bits( x ); }
#endif
#endif // 0

    }  // namespace bitlevel
}  // namespace cppx
