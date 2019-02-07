#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <cppx-core/text/unicode/To_bytes.hpp>

namespace cppx
{
    CPPX_USE_STD( basic_string, basic_string_view, iterator_traits, move, next, string );

    namespace impl
    {
        // Iterator traits specialization for this class is at the end of this file.
        class Count_iterator
        {
            Size        m_count     = 0;

            struct Proxy
            {
                operator char () const { return {}; }
                void operator=( char ) {}
            };

        public:
            auto count() const noexcept -> Size { return m_count; }

            void operator+=( const int n ) noexcept { m_count += n; }

            auto operator*() const noexcept
                -> Proxy
            { return {}; }

            auto operator++() noexcept
                -> Count_iterator&
            {
                ++m_count;
                return *this;
            }
        };

        // This overload is an optimization and can be removed with no ill effects
        // except execution time.
        template< class Value >
        auto output_utf8( const uint32_t code, const Count_iterator initial_count )
            -> Count_iterator
        {
            Count_iterator counter = initial_count;
            if( code <= 0x7F )          {  ++counter; }
            else if( code <= 0x7FF )    {  counter += 2; }
            else if( code <= 0xFFFF )   {  counter += 3; }
            else                        {  counter += 4; }

            return counter;
        }

    }  // namespace impl

    template< class Char >
    inline auto n_utf8_bytes_for( const basic_string_view<Char>& sv ) noexcept
        -> Size
    {
        impl::Count_iterator it;
        it = To_bytes().utf8_from_codes( CPPX_ITEMS( sv ), it );
        return it.count();
    }

    // Optimization.
    inline auto n_utf8_bytes_for( const basic_string_view<char>& sv ) noexcept
        -> Size
    { return sv.size(); }

    // Callability.
    template< class Char >
    inline auto n_utf8_bytes_for( const P_<Char> s ) noexcept
        -> Size
    { return n_utf8_bytes_for( basic_string_view<Char>( s ) ); }

    template< class Char >
    inline auto n_utf8_bytes_for( const basic_string<Char>& s ) noexcept
        -> Size
    { return n_utf8_bytes_for( basic_string_view<Char>( s ) ); }
}  // namespace cppx

namespace std
{
    template<>
    struct iterator_traits<cppx::impl::Count_iterator>:
        iterator_traits<char*>
    {};
}  // namespace std
