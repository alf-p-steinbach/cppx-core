#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <cppx-core/collections/Span_.hpp>                          // cppx::Span_
#include <cppx-core/collections/syntax/macro_items.hpp>             // CPPX_ITEMS
#include <cppx-core/core-language/syntax/macro_use.hpp>             // CPPX_USE_STD
#include <cppx-core/core-language/bit-level/byte-types.hpp>         // cppx::Byte
#include <cppx-core/core-language/signed-sizes.hpp>                 // cppx::Size
#include <cppx-core/meta-type/type-builders.hpp>                    // cppx::(P_)
#include <cppx-core/text/ascii/ascii-character-names.hpp>           // cppx::ascii::*
#include <cppx-core/text/pointers-from-string_view.hpp>             // cppx::(p_first_of, p_beyond_of)
#include <cppx-core/text/unicode/utf16-surrogate-pairs.hpp>         // cppx::utf16::*

#include <c/assert.hpp>         // assert
#include <iterator>             // std::(next, iterator_traits)
#include <string>               // std::string
#include <utility>              // std::(exchange, move)

namespace cppx
{
    CPPX_USE_STD( basic_string, basic_string_view, iterator_traits, exchange, move, next, string );


    namespace impl
    {
        template< class Out_iterator >
        auto output_utf8( const uint32_t code, const Out_iterator destination )
            -> Out_iterator
        {
            using Out_code = typename iterator_traits<Out_iterator>::value_type;

            Out_iterator out = destination;
            static_assert( ascii::last_char == 0x7F );
            if( code <= 0x7F )
            {
                *out = static_cast<Out_code>( code );  ++out;
            }
            else if( code <= 0x7FF )
            {
                // high bits = 0b11111 << 6
                *out = static_cast<Out_code>( 0b11000000 | (code >> 6) );  ++out;
                *out = static_cast<Out_code>( 0b10000000 | (code & 0x3F) );  ++out;
            }
            else if( code <= 0xFFFF )
            {
                // high bits = 0b1111 << 12
                *out = static_cast<Out_code>( 0b11100000 | (code >> 12) );  ++out;
                *out = static_cast<Out_code>( 0b10000000 | ((code >> 6) & 0x3F) );  ++out;
                *out = static_cast<Out_code>( 0b10000000 | (code & 0x3F) );  ++out;
            }
            else // code <= 0x10FFFF
            {
                // high bits = 0b111 << 18
                *out = static_cast<Out_code>( 0b11110000 | (code >> 18) );  ++out;
                *out = static_cast<Out_code>( 0b10000000 | ((code >> 12) & 0x3F) );  ++out;
                *out = static_cast<Out_code>( 0b10000000 | ((code >> 6) & 0x3F) );  ++out;
                *out = static_cast<Out_code>( 0b10000000 | (code & 0x3F) );  ++out;
            }
            return out;
        }
    }  // namespace impl

    class To_bytes
    {
        uint32_t    m_surrogate_1   = 0;
        Size        m_n_bad_chars   = 0;

    public:
        auto n_bad_chars() const noexcept -> Size { return m_n_bad_chars; }

        template< class Out_iterator >
        auto utf8_from_code( const uint32_t code, const Out_iterator destination )
            -> Out_iterator
        {
            Out_iterator it = destination;
            if( m_surrogate_1 != 0 )
            {
                const bool ok = utf16::range_of_pair_value_2.contains( code );
                if( ok )
                {
                    const uint32_t first_value      = exchange( m_surrogate_1, 0 );
                    const uint32_t second_value     = code;
                    const uint32_t full_code        = utf16::code_from_pair( first_value, second_value );
                    return impl::output_utf8( full_code, it );
                }
                else
                {
                    m_surrogate_1 = 0;
                    ++m_n_bad_chars;
                    it = impl::output_utf8( ascii::bad_char, it );  // For the `m_surrogate_1`.
                    // Fall through.
                }
            }

            if( utf16::range_of_pair_value_1.contains( code ) )
            {
                m_surrogate_1 = code;
                return it;
            }
            else if( code > 0x10FFFF or utf16::range_of_pair_value_2.contains( code ) )
            {
                ++m_n_bad_chars;
                return impl::output_utf8( ascii::bad_char, it );        // For the `code`.
            }
            return impl::output_utf8( code, it );
        }

        template< class In_iterator, class Out_iterator >
        auto utf8_from_codes(
            const Span_<In_iterator>        range,
            const Out_iterator              destination
            ) -> Out_iterator
        {
            Out_iterator current = destination;
            for( const uint32_t code : range )
            {
                current = utf8_from_code( code, current );
            }
            return current;
        }

        template< class In_iterator, class Out_iterator >
        auto utf8_from_codes(
            const In_iterator       first,
            const In_iterator       beyond,
            const Out_iterator      destination
            ) -> Out_iterator
        { return utf8_from_codes( Span_( first, beyond ), destination ); }
    };
}  // namespace cppx
