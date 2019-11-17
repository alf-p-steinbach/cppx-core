#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <cppx-core/collections/Range_.hpp>                     // cppx::Range_
#include <cppx-core-language/system/Byte.hpp>                   // cppx::Byte
#include <cppx-core-language/bit-level/bits_per_.hpp>           // cppx::magnitude_bits_per_
#include <cppx-core-language/tmp/Enable_if_.hpp>                // cppx::Enable_if_
#include <cppx-core/meta-type/type-traits.hpp>                  // cppx::Item_for_iterator_

#include <c/assert.hpp>         // assert
#include <c/stdint.hpp>         // uint32_t

namespace cppx::utf16
{
    constexpr uint32_t  first_beyond    = 1uL << 16;            // 0x10000
    constexpr unsigned  max_value       = first_beyond - 1;     //  0xFFFF

    // UTF-16 surrogate pair value ranges:
    constexpr Range_<unsigned>  range_of_pair_value_1( 0xD800, 0xDBFF );
    constexpr Range_<unsigned>  range_of_pair_value_2( 0xDC00, 0xDFFF );

    inline constexpr auto code_from_pair( const unsigned v1, const unsigned v2 ) noexcept
        -> uint32_t
    {
        //assert( range_of_pair_value_1.contains( v1 ) );
        //assert( range_of_pair_value_2.contains( v2 ) );
        return first_beyond + (
            ((v1 - range_of_pair_value_1.lower()) << 10) |
            (v2 - range_of_pair_value_2.lower())
            );
    }

    inline constexpr auto pair_value_1_from( const uint32_t code )
        -> unsigned
    {
        // assert( code > max_value )
        return ((code - first_beyond) >> 10) + range_of_pair_value_1.lower();
    }

    inline constexpr auto pair_value_2_from( const uint32_t code )
        -> unsigned
    {
        // assert( code > max_value )
        return (code & 0x3FFu) + range_of_pair_value_2.lower();
    }

    template<
        class Out_iterator,
        class = Enable_if_<(magnitude_bits_per_<Item_for_iterator_<Out_iterator>> >= 16)>
        >
    auto from_code_point( const uint32_t code_point, const Out_iterator destination )
        -> Out_iterator
    {
        using Out_value = Item_for_iterator_<Out_iterator>;
        if( code_point < max_value )
        {
            *destination = static_cast<Out_value>( code_point );
            return next( destination );
        }

        Out_iterator it = destination;
        *it = static_cast<Out_value>( pair_value_1_from( code_point ) );  ++it;
        *it = static_cast<Out_value>( pair_value_2_from( code_point ) );  ++it;
        return it;
    }

}  // namespace cppx::utf16
