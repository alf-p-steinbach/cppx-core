#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/text/unicode/unicode-Code_point_generator.hpp>  // cppx::unicode::Code_point_generator
#include <cppx-core/text/unicode/utf16-surrogate-pairs.hpp>         // cppx::utf16::*

#include <iterator>             // std::(distance, next)
#include <functional>           // std::invoke

namespace cppx::utf16
{
    CPPX_USE_STD( distance, invoke, ref, next );

    class Generator:
        public unicode::Code_point_generator
    {
    public:
        template<
            class Out_iterator,
            class = Enable_if_<(magnitude_bits_per_<Item_for_iterator_<Out_iterator>> >= 16)>
            >
        auto utf16_from_byte( const Byte value, const Out_iterator destination )
            -> Out_iterator
        {
            CPPX_FAIL( "Not implemented yet" );
        }

        template<
            class In_iterator,
            class Out_iterator,
            class = Enable_if_<(magnitude_bits_per_<Item_for_iterator_<Out_iterator>> >= 16)>
            >
        auto utf16_from_bytes(
            const Span_<In_iterator>        bytes_range,
            const Out_iterator              destination
            ) -> Out_iterator
        {
            using Out_value = Item_for_iterator_<Out_iterator>;

            Out_iterator current = destination;
            const In_iterator beyond_bytes = bytes_range.beyond();
            for( auto it = bytes_range.first(); it != beyond_bytes; )
            {
                const uint32_t code_point = code_point_from_bytes( in_out_ref( it ), beyond_bytes );
                current = utf16::from_code_point( code_point, current );
            }
            return current;
        }

        template<
            class In_iterator,
            class Out_iterator,
            class = Enable_if_<(magnitude_bits_per_<Item_for_iterator_<Out_iterator>> >= 16)>
            >
        auto utf16_from_bytes(
            const In_iterator       first,
            const In_iterator       beyond,
            const Out_iterator      destination
            ) -> Out_iterator
        { return utf16_from_bytes( Span_( first, beyond ), destination ); }
    };
}  // namespace cppx::utf16
