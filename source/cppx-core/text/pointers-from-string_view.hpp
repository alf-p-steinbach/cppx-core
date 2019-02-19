#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <cppx-core/collections/is_empty.hpp>               // cppx::is_empty
#include <cppx-core/language/type-builders.hpp>             // cppx::(P_, Raw_array_of_)
#include <cppx-core/text/C_str_.hpp>                        // cppx::C_str_

#include <string_view>          // std::string_view

namespace cppx
{
    CPPX_USE_STD( basic_string_view );

    template< class Char>
    constexpr Raw_array_of_<1, const Char> empty_c_string = {};

    template< class Char >
    inline auto p_first_of( const basic_string_view<Char>& view ) noexcept
        -> C_str_<Char>
    { return (is_empty( view )? empty_c_string<Char> : view.data()); }

    template< class Char >
    inline auto p_beyond_of( const basic_string_view<Char>& view ) noexcept
        -> C_str_<Char>
    { return p_first_of( view ) + view.size(); }

}  // namespace cppx
