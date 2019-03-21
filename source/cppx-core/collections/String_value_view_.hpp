#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/language/syntax/macro-use.hpp>              // CPPX_USE_STD
#include <cppx-core/language/syntax/type-assemblers.hpp>        // cppx:P_
#include <cppx-core/language/types/signed-size-types.hpp>       // cppx::Size
#include <cppx-core/collections/dynamic-size-checking.hpp>      // cppx::length_of

#include <string>               // std::basic_string
#include <string_view>          // std::basic_string_view

namespace cppx
{
    CPPX_USE_STD( basic_string, basic_string_view );

    template< class Char >
    class String_value_view_
    {
        P_<const Char>      m_p_start;
        Size                m_length;

    public:
        auto is_empty() const
            -> bool
        { return m_length == 0; }

        auto length() const
            -> Size
        { return m_length; }

        auto temporary_access() const
            -> basic_string_view<Char>
        { return basic_string_view<Char>( m_p_start, m_length ); }

        String_value_view_():
            m_p_start( nullptr ),
            m_length( 0 )
        {}

        String_value_view_( const P_<const Char> s ):
            m_p_start( s ),
            m_length( length_of( s ) )
        {}

        String_value_view_( const basic_string<Char>& s ):
            m_p_start( s.data() ),
            m_length( s.length() )
        {}
    };

    template< class Char >
    inline auto is_empty( const String_value_view_<Char>& svv )
        -> bool
    { return svv.is_empty(); }

    using String_value_view     = String_value_view_<char>;
    using WString_value_view    = String_value_view_<wchar_t>;

}  // namespace cppx
