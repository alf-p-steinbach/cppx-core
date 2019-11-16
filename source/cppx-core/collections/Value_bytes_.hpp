#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/language/syntax/macro-use.hpp>              // CPPX_USE_STD
#include <cppx-core/language/syntax/type-builders.hpp>          // cppx::P_
#include <cppx-core/language/system/Byte.hpp>                   // cppx::Byte
#include <cppx-core/language/system/Endian.hpp>                 // cppx::(is_XXX_endian)
#include <cppx-core/language/tmp/Enable_if_.hpp>                // cppx::Enable_if_

#include <algorithm>        // std::(min, reverse)
#include <string.h>         // memcpy
#include <type_traits>      // std::is_trivially_copyable_v

namespace cppx {
    CPPX_USE_STD( is_trivially_copyable_v, min, reverse );

    // Provides a big endian sequence of bytes of a specified simple value.
    template< int capacity >
    class Value_bytes_
    {
        Byte    m_buffer[capacity];
        int     m_buffer_size;

    public:
        template< int na, int nb >
        static auto compare_bytes_of(
            const Value_bytes_<na>&     a,
            const Value_bytes_<nb>&     b
            ) -> int
        {
            const int common_size = min( a.size(), b.size() );
            if( const int r = memcmp( a.data(), b.data(), common_size ) ) {
                return r;
            } else {
                return a.size() - b.size();
            }
        }

        auto data() const   -> P_<const Byte>   { return &m_buffer[0]; }
        auto size() const   -> int              { return m_buffer_size; }

        auto begin() const  -> P_<const Byte>   { return data(); }
        auto end() const    -> P_<const Byte>   { return data() + size(); }

        template<
            class Value,
            class = Enable_if_<is_trivially_copyable_v<Value>>
            >
        Value_bytes_( const Value& value ):
            m_buffer_size( sizeof( value ) )
        {
            static_assert( sizeof( value ) <= capacity );
            static_assert( not system::is_mixed_endian );
            memcpy( &m_buffer[0], &value, m_buffer_size );
            if( system::is_little_endian ) {
                reverse( m_buffer, m_buffer + m_buffer_size );
            }
        }
    };

}  // namespace cppx
