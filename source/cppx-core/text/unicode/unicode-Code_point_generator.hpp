#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/collections/Span_util.hpp>                      // cppx::Span_
#include <cppx-core/failure-handling/macro-fail.hpp>                // CPPX_FAIL, std::exception
#include <cppx-core-language/syntax/declarations.hpp>               // CPPX_USE_STD
#include <cppx-core-language/system-dependent/size-types.hpp>       // cppx::Size
#include <cppx-core-language/tmp/Enable_if_.hpp>                    // cppx::Enable_if_
#include <cppx-core/parameters/In_out_ref_.hpp>                     // cppx::In_out_ref_, std::ref
#include <cppx-core/text/unicode/utf8-iteration.hpp>                // cppx::utf8::*

#include <cppx-core-language/text/ascii-character-names.hpp>        // cppx::ascii::bad_char

#include <iterator>             // std::(distance, next)
#include <functional>           // std::invoke

namespace cppx::unicode
{
    CPPX_USE_STD( distance, invalid_argument, invoke, ref, runtime_error, next );

    class Code_point_generator
    {
        int     m_n_bad_groups              = 0;
        int     m_n_noncanonical_groups     = 0;
        int     m_incomplete_code_point     = 0;
        int     m_n_completion_bytes        = 0;

    public:
        auto n_bad_groups() const noexcept          -> Size { return m_n_bad_groups; }
        auto n_noncanonical_groups() const noexcept -> Size { return m_n_noncanonical_groups; }

        class Incomplete_group_exception:
            public runtime_error
        {
        public:
            using runtime_error::runtime_error;
        };

        template< class In_iterator >
        auto code_point_from_bytes( In_out_ref_<In_iterator> it_ref, const In_iterator beyond )
            -> uint32_t
        {
            auto& it = it_ref.get();
            hopefully( it != beyond )
                or CPPX_FAIL_( invalid_argument, "Called with an empty byte sequence `it == beyond`" );

            const Byte byte_value = *it;  ++it;
            if( utf8::is_single_byte( byte_value ) )
            {
                return byte_value;
            }

            if( not utf8::is_lead_byte( byte_value ) )
            {
                ++m_n_bad_groups;
                return ascii::bad_char;
            }

            const int n_bytes = utf8::group_size_for_lead_byte( byte_value );
            if( n_bytes > 4 )   // More than Unicode's 21 bits per code point.
            {
                while( it != beyond and utf8::is_continuation_byte( *it ) )
                {
                    ++it;
                }
                ++m_n_bad_groups;
                return ascii::bad_char;
            }
            m_n_noncanonical_groups += int( not utf8::is_valid_lead_byte( byte_value ) );

            const int n_first_value_bits = (8 - (n_bytes + 1));
            const uint32_t first_value_bits_mask = ((1 << n_first_value_bits) - 1);

            uint32_t code_point = (byte_value & first_value_bits_mask);   // i == 0
            for( int i = 1; i < n_bytes; ++i )
            {
                if( it == beyond )
                {
                    m_incomplete_code_point = code_point;
                    m_n_completion_bytes = n_bytes - (i - 1);
                    CPPX_FAIL_( Incomplete_group_exception, "Incomplete group at end of buffer" );
                }

                const Byte continuation_byte = *it;
                if( utf8::is_continuation_byte( continuation_byte ) )
                {
                    ++it;
                    code_point = (code_point << 6) | (continuation_byte & 0x3F);
                }
                else
                {
                    ++m_n_bad_groups;
                    return ascii::bad_char;
                }
            }
            return code_point;
        }
    };
}  // namespace cppx::unicode
