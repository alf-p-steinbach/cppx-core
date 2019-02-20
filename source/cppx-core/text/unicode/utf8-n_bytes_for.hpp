#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/text/unicode/utf8-Generator.hpp>
#include <cppx-core/iterators/Count_iterator_.hpp>

namespace cppx::utf8
{
    CPPX_USE_STD( basic_string, basic_string_view, iterator_traits, move, next, string );

    /// @cond DOXY_SHOW_IMPL_DETAILS
    namespace impl
    {
        using Bytes_count_iterator = Count_iterator_<char>;

        // This overload is an optimization and can be removed with no ill effects
        // except execution time.
        template< class Value >
        auto output_utf8( const uint32_t code, const Bytes_count_iterator initial_count )
            -> Bytes_count_iterator
        {
            Bytes_count_iterator counter = initial_count;
            if( code <= 0x7F )          {  ++counter; }
            else if( code <= 0x7FF )    {  counter += 2; }
            else if( code <= 0xFFFF )   {  counter += 3; }
            else                        {  counter += 4; }

            return counter;
        }
    }  // namespace impl
    /// @endcond

    template< class Char >
    inline auto n_bytes_for( const basic_string_view<Char>& sv ) noexcept
        -> Size
    {
        impl::Bytes_count_iterator it;
        it = Generator().utf8_from_codes( CPPX_ITEMS( sv ), it );
        return it.count();
    }

    // Optimization.
    inline auto n_bytes_for( const basic_string_view<char>& sv ) noexcept
        -> Size
    { return sv.size(); }

    // Callability.
    template< class Char >
    inline auto n_bytes_for( const P_<Char> s ) noexcept
        -> Size
    { return n_bytes_for( basic_string_view<Char>( s ) ); }

    template< class Char >
    inline auto n_bytes_for( const basic_string<Char>& s ) noexcept
        -> Size
    { return n_bytes_for( basic_string_view<Char>( s ) ); }
}  // namespace cppx::utf8
