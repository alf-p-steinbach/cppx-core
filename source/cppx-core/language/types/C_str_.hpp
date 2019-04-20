#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
//
// Simple type names for C string pointers, e.g. to simplify top level `const`. 

#include <cppx-core/language/types/type-makers.hpp>         // cppx::(P_, Const_, Unconst_)

namespace cppx
{
    // Enable_if_<is_a_cpp03_char_type_<Unconst_<Char>>>
    template< class Char >  using C_str_            = P_<Const_<Char>>;
    template< class Char >  using Mutable_c_str_    = P_<Unconst_<Char>>;

    using C_str                 = C_str_<char>;
    using Wide_c_str            = C_str_<wchar_t>;
    using Mutable_c_str         = Mutable_c_str_<char>;
    using Mutable_wide_c_str    = Mutable_c_str_<wchar_t>;

} // namespace cppx
