#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
//
// Simple type names for C string pointers, e.g. to simplify top level `const`. 

#include <cppx-core/language/types/type-producers.hpp>          // cppx::(P_, Const_, Unconst_)

namespace cppx
{
    // Enable_if_<is_a_cpp03_char_type_<Unconst_<Char>>>
    template< class Char >  using C_str_            = P_<Const_<Char>>;
    template< class Char >  using C_mutable_str_    = P_<Unconst_<Char>>;

    using C_str             = C_str_<char>;
    using C_wstr            = C_str_<wchar_t>;
    using C_mutable_str     = C_mutable_str_<char>;
    using C_mutable_wstr    = C_mutable_str_<wchar_t>;

} // namespace cppx
