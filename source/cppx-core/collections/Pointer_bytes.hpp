#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/collections/Value_bytes_.hpp>           // cppx::Value_bytes_
#include <cppx-core/language/syntax/macro-use.hpp>          // CPPX_USE_STD
#include <cppx-core/language/syntax/type-builders.hpp>      // cppx::(Func_, P_)
#include <cppx-core/text/to-hex-string.hpp>                 // cppx::{hex functionality}

#include <algorithm>        // std::max
#include <string>           // std::string

namespace cppx {
    CPPX_USE_STD( max, string );

    constexpr int   data_pointer_size   = sizeof( void* );
    constexpr int   code_pointer_size   = sizeof( void(*)() );
    constexpr int   max_pointer_size    = max( data_pointer_size, code_pointer_size );

    // Provides a big endian sequence of bytes of a specified pointer value.
    class Pointer_bytes:
        public Value_bytes_<max_pointer_size>
    {
        bool m_is_data_pointer;

    public:
        using Base = Value_bytes_<max_pointer_size>;

        auto is_data_pointer() const
            -> bool
        { return m_is_data_pointer; }

        auto is_code_pointer() const
            -> bool
        { return not m_is_data_pointer; }

        friend auto compare( const Pointer_bytes& a, const Pointer_bytes& b )
            -> int
        {
            if( const int r = a.is_data_pointer() - b.is_data_pointer() ) {
                return r;
            } else {
                return compare_bytes_of( a, b );
            }
        }

        Pointer_bytes( const P_<const void> pd ):
            Base( pd ),
            m_is_data_pointer( true )
        {}

        template< class Result, class... Args >
        Pointer_bytes( const P_<Func_<Result, Args...>> pf ):
            Base( pf ),
            m_is_data_pointer( false )
        {}
    };

    struct Function_pointer_to_hex_in
    {
        static auto the_function(
            const P_<char>          buffer,
            const Pointer_bytes&    bytes,
            const P_<const char>    hex_digits  = hex_digits_uppercase
            ) -> int
        {
            return int( byte_span_to_hex_in( buffer, CPPX_ITEMS_OF( bytes ), hex_digits ) );
        }

        static constexpr auto its_buffer_size( const int n_bytes )
            -> Size
        { return buffer_size_for( byte_span_to_hex_in, n_bytes ); }
    };

    // buffer, bytes, {optional} hex_digits
    constexpr auto pointer_to_hex_in = Call_operator_for_<Function_pointer_to_hex_in>();

    inline auto hex_from_pointer_bytes(
        const Pointer_bytes&    bytes,
        const P_<const char>    hex_digits  = hex_digits_uppercase
        ) -> string
    {
        const auto result_length = int( buffer_size_for( pointer_to_hex_in, bytes.size() ) );
        string result( result_length, '\0' );
        pointer_to_hex_in( result.data(), bytes, hex_digits );
        return result;
    }

    inline auto to_hex(
        const Pointer_bytes&    bytes,
        const P_<const char>    hex_digits  = hex_digits_uppercase
        ) -> string
    {  return hex_from_pointer_bytes( bytes, hex_digits );  }

    inline auto spec_prefix_of( const Pointer_bytes& bytes, const bool use_uppercase = false )
        -> P_<const char>
    {
        static const P_<const char> prefixes[2][2] =
        {
            {"&o=", "&O="}, {"&f=", "&F="}
        };

        return prefixes[bytes.is_code_pointer()][use_uppercase];
    }

    inline auto spec_of( const Pointer_bytes& bytes, const bool use_uppercase = false )
        -> string
    {
        const P_<const char> hex_digits = (
            use_uppercase? hex_digits_uppercase : hex_digits_lowercase
            );

        return spec_prefix_of( bytes, use_uppercase ) + to_hex( bytes, hex_digits );
    }

    inline auto as_address( const P_<const void> pd )
        -> Pointer_bytes
    { return Pointer_bytes( pd ); }

    template< class Result, class... Args >
    inline auto as_address( const P_<Func_<Result, Args...>> pf )
        -> Pointer_bytes
    { return Pointer_bytes( pf ); }

}  // namespace cppx
