#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/collections/Span_util.hpp>                              // cppx::Span_
#include <cppx-core-language/syntax/flow-control/exception-throwing.hpp>    // CPPX_FAIL
#include <cppx-core-language/syntax/declarations.hpp>                       // CPPX_USE_STD
#include <cppx-core-language/types/system-dependent/size-types.hpp>         // cppx::Size
#include <cppx-core-language/tmp/Enable_if_.hpp>                            // cppx::Enable_if_
#include <cppx-core/parameters/In_out_ref_.hpp>                             // cppx::In_out_ref_, std::ref
#include <cppx-core/text/unicode/utf8-iteration.hpp>                        // cppx::utf8::*
#include <cppx-core/text/unicode/utf16-surrogate-pairs.hpp>                 // cppx::utf16::*

#include <cppx-core-language/text/ascii-character-names.hpp>                // cppx::ascii::bad_char

#include <iterator>             // std::(distance, next)
#include <functional>           // std::invoke

namespace cppx::utf32
{
    CPPX_USE_STD( distance, invoke, ref, next );

    class Generator
    {
        int     m_n_bad_groups              = 0;
        int     m_n_noncanonical_groups     = 0;

    public:
        auto n_bad_groups() const noexcept          -> Size { return m_n_bad_groups; }
        auto n_noncanonical_groups() const noexcept -> Size { return m_n_noncanonical_groups; }

        template< class In_iterator >
        auto code_point_from_bytes( In_out_ref_<In_iterator> it_ref, const In_iterator beyond )
            -> uint32_t
        {
            auto& it = it_ref.get();
            hopefully( it != beyond )
                or CPPX_FAIL( "Called with an empty byte sequence `it == beyond`" );

            const Byte byte_value = *it;  ++it;
            if( utf8::is_single_byte( byte_value ) )    { return byte_value; }
            if( not utf8::is_lead_byte( byte_value ) )  { return ascii::bad_char; }

            const int n_bytes = utf8::group_size_for_lead_byte( byte_value );
            if( n_bytes > 4 )   // More than Unicode's 21 bits per code point.
            {
                while( it != beyond and utf8::is_continuation_byte( *it ) )
                {
                    ++it;
                }
                return ascii::bad_char;
            }
            m_n_noncanonical_groups += int( not utf8::is_valid_lead_byte( byte_value ) );

            const int n_first_bits = (8 - (n_bytes + 1));
            const uint32_t first_bits_mask = ((1 << n_first_bits) - 1);

            uint32_t code_point = (byte_value & first_bits_mask);   // i == 0
            for( int i = 1; i < n_bytes; ++i )
            {
                if( it != beyond )
                {
                    const Byte continuation_byte = *it;
                    if( utf8::is_continuation_byte( continuation_byte ) )
                    {
                        ++it;
                        code_point = (code_point << 6) | (continuation_byte & 0x3F);
                        continue;
                    }
                }
                ++m_n_bad_groups;
                return ascii::bad_char;
            }
            return code_point;
        }

        template<
            class In_iterator,
            class Out_iterator,
            class = Enable_if_<(magnitude_bits_per_<Item_for_iterator_<Out_iterator>> >= 21)>
            >
        auto utf32_from_bytes(
            const Span_<In_iterator>        bytes_range,
            const Out_iterator              destination
            ) -> Out_iterator
        {
            using Out_value = Item_for_iterator_<Out_iterator>;

            Out_iterator current = destination;
            const In_iterator beyond_bytes = bytes_range.beyond();
            for( auto it = bytes_range.first(); it != beyond_bytes; )
            {
                const uint32_t code_point = code_point_from_bytes( it, beyond_bytes );
                *current = static_cast<Out_value>( code_point );
                ++current;
            }
            return current;
        }

        template<
            class In_iterator,
            class Out_iterator,
            class = Enable_if_<(magnitude_bits_per_<Item_for_iterator_<Out_iterator>> >= 21)>
            >
        auto utf32_from_bytes(
            const In_iterator       first,
            const In_iterator       beyond,
            const Out_iterator      destination
            ) -> Out_iterator
        { return utf32_from_bytes( Span_( first, beyond ), destination ); }
    };
}  // namespace cppx::utf32
