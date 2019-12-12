#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <cppx-core/collections/is_empty.hpp>                   // cppx::is_empty
#include <cppx-core-language/syntax/types/type-builders.hpp>    // cppx::(P_)

#include <string_view>          // std::string_view

namespace cppx
{
    CPPX_USE_STD( basic_string_view );

    template< class Char >
    inline auto p_first_of( const basic_string_view<Char>& view ) noexcept
        -> P_<const Char>
    { return view.data(); }

    template< class Char >
    inline auto p_beyond_of( const basic_string_view<Char>& view ) noexcept
        -> P_<const Char>
    { return (view.data() == nullptr? nullptr : p_first_of( view ) + view.size()); }

}  // namespace cppx
