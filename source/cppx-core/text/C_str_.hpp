﻿#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
//
// Simple type names for C string pointers, e.g. to simplify top level `const`. 

#include <cppx-core/meta-template/enable_if_.hpp>               // cppx::Enable_if_
#include <cppx-core/meta-type/type-traits.hpp>                  // cppx::is_cpp03_char_type_
#include <cppx-core/language/types/type-production.hpp>         // cppx::(P_, Unconst_)

namespace cppx
{
    /// @cond DOXY_SHOW_IMPL_DETAILS
    namespace impl
    {
        template<
            class Char,
            class = Enable_if_<is_a_cpp03_char_type_<Unconst_<Char>>>
            >
        using C_str_ = P_<Char>;
    }  // namespace impl
    /// @endcond

    template< class Char >  using C_str_            = impl::C_str_<Const_<Char>>;
    template< class Char >  using C_mutable_str_    = impl::C_str_<Unconst_<Char>>;

    using C_str             = C_str_<char>;
    using C_wstr            = C_str_<wchar_t>;
    using C_mutable_str     = C_mutable_str_<char>;
    using C_mutable_wstr    = C_mutable_str_<wchar_t>;

} // namespace cppx
