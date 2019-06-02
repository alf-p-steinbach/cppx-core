#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/collections/Value_bytes_.hpp>           // cppx::Value_bytes_
#include <cppx-core/language/syntax/macro-use.hpp>          // CPPX_USE_STD
#include <cppx-core/language/syntax/type-assemblers.hpp>    // cppx::(Func_, P_)

#include <algorithm>        // std::max

namespace cppx {
    CPPX_USE_STD( max );

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
                return Base::compare( a, b );
            }
        }

        explicit Pointer_bytes( const P_<const void> pd ):
            Base( Common_init_tag(), pd ),
            m_is_data_pointer( true )
        {}

        template< class Result, class... Args >
        explicit Pointer_bytes( const P_<Func_<Result, Args...>> pf ):
            Base( Common_init_tag(), pf ),
            m_is_data_pointer( false )
        {}
    };

}  // namespace cppx
